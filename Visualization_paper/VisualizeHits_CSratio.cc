#include <iostream>
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TEllipse.h"
#include "TH3F.h"
#include "TGaxis.h"
#include <set>
#include "TShape.h"
#include <iomanip>
#include <chrono>
#include <string>

struct EventData {
  int event;
  int fN;
  double fiberx, fibery, fiberz, hitx, hity, hitz, time;
};

void VisualizeHits_CSratio(string path, string fileName, int eventNumber = 0) {

  const char* eventTitle;
  if (fileName == "2.8MeVelectron50") eventTitle = "electron 2.8 MeV";
  else if (fileName == "2.8MeVgamma50") eventTitle = "gamma 2.8 MeV";
  else if (fileName == "1.78MeVpositron50") eventTitle = "single positron 1.78 MeV";
  else if (fileName == "0.38MeV2xpositron50") eventTitle = "two positrons 0.38 MeV each";
  
  gStyle->SetOptStat(0);

  cout << "remettre bon fiber pitch" << endl;
  double fiberPitch = 15.; // mm
  // double fiberPitch = 10.; // mm
  double particleGunX = 7.5; // mm
  double particleGunY = 7.5; // mm
  double particleGunZ = 0.; // mm
  
  double Light_Yield = 9000.; // PE/MeV

  string file = path + fileName + ".root";
  const char * cfile = file.c_str();

  // Open the input file
  TFile *inputFile = new TFile(cfile, "read");
  // TFile *inputFile = new TFile("Generated_events/positron_0MeV.root", "read");

  // Get the tree from the file
  TTree *tree = (TTree*)inputFile->Get("Hits");

  // Get the number of entries in the tree
  // Ensure that the tree is not empty
  int entries = tree ? tree->GetEntries() : 0;
  
  EventData eventData;

  // Set branch addresses for the tree
  tree->SetBranchAddress("Event_Number", &eventData.event);
  tree->SetBranchAddress("fibreX", &eventData.fiberx);
  tree->SetBranchAddress("fibreY", &eventData.fibery);
  tree->SetBranchAddress("fibreZ", &eventData.fiberz);
  tree->SetBranchAddress("fibreNumber", &eventData.fN);
  tree->SetBranchAddress("Hit_X", &eventData.hitx);
  tree->SetBranchAddress("Hit_Y", &eventData.hity);
  tree->SetBranchAddress("Hit_Z", &eventData.hitz);
  tree->SetBranchAddress("Time_ns", &eventData.time);

  double minX = -70.;
  double maxX = 70.;
  
  double minY = -70.;
  double maxY = 70.;
    
  double minZ = -70.;
  double maxZ = 70.;

  int nbinsX = (maxX - minX) / fiberPitch * 10.;
  int nbinsY = (maxY - minY) / fiberPitch * 10.;
  
  // Create a 2D histograms
  TH2F *histogramXY = new TH2F("histogramXY", "", nbinsX, minX, maxX, nbinsY, minY, maxY); // for electron zoom

  double f = sqrt(2.)/2.;
  double X_value = 0.;
  double Y_value = 0.;
  double Z_value = 0.;

  // Loop over entries and fill the histogram
  for (int i = 0; i < entries; i++) {
    tree->GetEntry(i);

    if (eventData.event == eventNumber) {

      X_value = eventData.hitx/10.-particleGunX; // conversion in cm - re-centering the particle gun
      Y_value = eventData.hity/10.-particleGunY; // conversion in cm - re-centering the particle gun
      Z_value = eventData.hitz/10.-particleGunZ; // conversion in cm - re-centering the particle gun

      // // rotation or flipping or event if necessary, for display for paper
      // if (fileName == "2.8MeVgamma50") histogramXY->Fill(X_value, -Y_value);
      if (fileName == "0.38MeV2xpositron50") histogramXY->Fill(X_value*f-Y_value*f, X_value*f+Y_value*f);
      else histogramXY->Fill(X_value, Y_value);

    }

  }
  
  /////////////////////////// Visualization

  // plot XY 
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);
  c1->SetLeftMargin(0.1874085);
  c1->SetRightMargin(0.005856515);
  c1->SetTopMargin(0.009752438);
  c1->SetBottomMargin(0.1642911);

  if (fileName == "2.8MeVgamma50" || fileName == "0.38MeV2xpositron50")  {
    c1->SetLeftMargin(0.005856515);
    c1->SetRightMargin(0.1874085);
  }

  if (fileName == "2.8MeVgamma50" || fileName == "2.8MeVelectron50")  {
    c1->SetTopMargin(0.1642911);
    c1->SetBottomMargin(0.009752438);
  }

  // c1->SetFillColorAlpha(1,0.);

  gPad->SetLogz();

  // c1->SetGrayscale();
  gStyle->SetPalette(kSunset);

  // TColor::InvertPalette();

  // Set axis titles
  // histogramXY->SetTitle(eventTitle);
  histogramXY->GetXaxis()->SetTitle("x (cm)");
  histogramXY->GetYaxis()->SetTitle("y (cm)");
  histogramXY->GetZaxis()->SetTitle("");
  // histogramXY->GetZaxis()->SetTitle("Hits on fibres");

  TGaxis::SetMaxDigits(10);

  // gPad->SetGridy();
  // gPad->SetGridx();
  // gPad->SetFrameLineColor(kGray+3);
  gPad->SetFrameLineWidth(2);

  double titleSize = 0.07;

  histogramXY->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  histogramXY->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  histogramXY->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  histogramXY->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetXaxis()->SetLabelFont(42);
  histogramXY->GetXaxis()->SetTitleOffset(1.);
  histogramXY->GetXaxis()->CenterTitle(1);
  histogramXY->GetXaxis()->SetTickLength(0.02);
  if (fileName == "2.8MeVgamma50" || fileName == "2.8MeVelectron50")  {
    histogramXY->GetXaxis()->SetTitleSize(0.);
  }
  else {
    histogramXY->GetXaxis()->SetTitleSize(titleSize);
  }
  histogramXY->GetXaxis()->SetLabelSize(histogramXY->GetXaxis()->GetTitleSize());
  histogramXY->GetXaxis()->SetLabelSize(histogramXY->GetXaxis()->GetTitleSize());
  histogramXY->GetXaxis()->SetTitleFont(42);


  histogramXY->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetLabelFont(42);
  histogramXY->GetYaxis()->SetTitleOffset(1.);
  histogramXY->GetYaxis()->CenterTitle(1);
  histogramXY->GetYaxis()->SetTickLength(histogramXY->GetXaxis()->GetTickLength());
  if (fileName == "2.8MeVgamma50" || fileName == "0.38MeV2xpositron50")  {
    histogramXY->GetYaxis()->SetTitleSize(0.);
  }
  else {
    histogramXY->GetYaxis()->SetTitleSize(titleSize);
  }
  histogramXY->GetYaxis()->SetLabelSize(histogramXY->GetYaxis()->GetTitleSize());
  histogramXY->GetYaxis()->SetTitleFont(42);
  
  histogramXY->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  histogramXY->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  histogramXY->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetZaxis()->SetLabelFont(42);
  histogramXY->GetZaxis()->SetTitleOffset(0.1);
  histogramXY->GetZaxis()->CenterTitle(1);
  histogramXY->GetZaxis()->SetTickLength(histogramXY->GetXaxis()->GetTickLength());
  histogramXY->GetZaxis()->SetTitleSize(titleSize);
  histogramXY->GetZaxis()->SetLabelSize(titleSize-0.02);
  histogramXY->GetZaxis()->SetTitleFont(42);
  
  histogramXY->GetXaxis()->SetNdivisions(6);
  histogramXY->GetYaxis()->SetNdivisions(6);

  histogramXY->GetZaxis()->SetRangeUser(1,3.5e3);

  histogramXY->Draw("colz");
  if (fileName != "2.8MeVelectron50") histogramXY->Draw("col");

  gStyle->SetLineStyleString(11,"200 100");
  
  TLine *line = new TLine(minX, 0, maxX, 0);
  line->SetLineStyle(9);
  line->SetLineWidth(3);
  line->SetLineColor(kGray+1);
  line->Draw("SAME");
  
  TLine *line2 = new TLine(0, minY, 0, maxY);
  line2->SetLineStyle(line->GetLineStyle());
  line2->SetLineWidth(line->GetLineWidth());
  line2->SetLineColor(line->GetLineColor());
  line2->Draw("SAME");

  if (fileName == "2.8MeVelectron50") {
    TPaveText *pt = new TPaveText(-14.6,-39.3,14.9,-33.1);
    pt->AddText("Hits on fibres");
    pt->SetTextSize(titleSize-0.01);
    pt->SetTextFont(histogramXY->GetXaxis()->GetTitleFont());
    pt->SetTextColor(histogramXY->GetXaxis()->GetTitleColor());
    pt->SetFillColor(0);
    pt->Draw("SAME");
  }

  double x1_palette = -53.5;
  double y1_palette = -53.5;
  double x2_palette = 53.8;
  double y2_palette = -42.8;

  auto palette2 = new TPaletteAxis(x1_palette, y1_palette, x2_palette, y2_palette, histogramXY);
  histogramXY->GetListOfFunctions()->Add(palette2);

  // // draw contours of palette
  // double boxThickness = 0.3;
  // TBox *box = new TBox(x1_palette+boxThickness, y1_palette-boxThickness, x2_palette+boxThickness, y2_palette+boxThickness);
  // box->SetFillColorAlpha(1,0.);
  // box->SetLineColor(1);
  // box->SetLineWidth(1);
  // box->Draw("same");

  palette2->Draw("same");

  TString OutputPngFile_XY = "plots/Visu_event_XY_" + fileName + "_event" + to_string(eventNumber) + ".png";
  TString OutputPdfFile_XY = "plots/Visu_event_XY_" + fileName + "_event" + to_string(eventNumber) + ".pdf";
  c1->SaveAs(OutputPngFile_XY);
  c1->SaveAs(OutputPdfFile_XY);
  
}
