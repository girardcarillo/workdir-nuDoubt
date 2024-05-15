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
  int photonType;
  double fiberx, fibery, fiberz, hitx, hity, hitz, time;
};

void DefineCSratio(string path, string fileName, int eventNumber = 0) {

  const char* eventTitle;
  if (fileName == "2.8MeVelectron50") eventTitle = "electron 2.8 MeV";
  else if (fileName == "2.8MeVgamma50") eventTitle = "gamma 2.8 MeV";
  else if (fileName == "1.78MeVpositron50") eventTitle = "single positron 1.78 MeV";
  else if (fileName == "0.38MeV2xpositron50") eventTitle = "two positrons 0.38 MeV each";
  
  gStyle->SetOptStat(0);

  double fiberPitch = 10.; // mm
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
  tree->SetBranchAddress("CreationID", &eventData.photonType);

  double minX = -70.;
  double maxX = 70.;
  
  double minY = -70.;
  double maxY = 70.;
    
  double minZ = -70.;
  double maxZ = 70.;

  int nbinsX = (maxX - minX) / fiberPitch * 10.;
  int nbinsY = (maxY - minY) / fiberPitch * 10.;
  
  // Create a 2D histograms
  TH2F *Cerenkov = new TH2F("Cerenkov", "", nbinsX, minX, maxX, nbinsY, minY, maxY); // for electron zoom
  TH2F *Scintillation = new TH2F("Scintillation", "", nbinsX, minX, maxX, nbinsY, minY, maxY); // for electron zoom

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

      // // // rotation or flipping or event if necessary, for display for paper
      // // if (fileName == "2.8MeVgamma50") histogramXY->Fill(X_value, -Y_value);
      // else histogramXY->Fill(X_value, Y_value);

      // define C/S ratio
      if (eventData.photonType == 1)
	Cerenkov->Fill(X_value, Y_value);
      else if (eventData.photonType == 2)
	Scintillation->Fill(X_value, Y_value);
      
    }

  }

  // Cerenkov->Divide(Scintillation);

  // tests visus

  TCanvas *c1 = new TCanvas("c1", "c1",5,77,936,1358);
  c1->Range(0,0,1,1);
  Cerenkov->SetTitle(eventTitle);
  c1->Divide(1,2);
  c1->cd(1);
  gPad->SetLogz();
  Cerenkov->GetZaxis()->SetRangeUser(1e-2,5e2);
  Cerenkov->Draw("colz");
  c1->cd(2);
  gPad->SetLogz();
  Scintillation->Draw("colz");
  
  /////////////////////////// Visualization

  // plot C/S
  
  // TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);
  // c1->SetLeftMargin(0.1874085);
  // c1->SetRightMargin(0.005856515);
  // c1->SetTopMargin(0.009752438);
  // c1->SetBottomMargin(0.1642911);

  // if (fileName == "2.8MeVgamma50" || fileName == "0.38MeV2xpositron50")  {
  //   c1->SetLeftMargin(0.005856515);
  //   c1->SetRightMargin(0.1874085);
  // }

  // if (fileName == "2.8MeVgamma50" || fileName == "2.8MeVelectron50")  {
  //   c1->SetTopMargin(0.1642911);
  //   c1->SetBottomMargin(0.009752438);
  // }

  // // c1->SetFillColorAlpha(1,0.);

  // gPad->SetLogz();

  // // c1->SetGrayscale();
  gStyle->SetPalette(kSunset);

  // // TColor::InvertPalette();

  // // Set axis titles
  // // Cerenkov->SetTitle(eventTitle);
  // Cerenkov->GetXaxis()->SetTitle("x (cm)");
  // Cerenkov->GetYaxis()->SetTitle("y (cm)");
  // Cerenkov->GetZaxis()->SetTitle("");
  // // Cerenkov->GetZaxis()->SetTitle("Hits on fibres");

  // TGaxis::SetMaxDigits(10);

  // // gPad->SetGridy();
  // // gPad->SetGridx();
  // // gPad->SetFrameLineColor(kGray+3);
  // gPad->SetFrameLineWidth(2);

  // double titleSize = 0.07;

  // Cerenkov->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // Cerenkov->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  // Cerenkov->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // Cerenkov->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // Cerenkov->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // Cerenkov->GetXaxis()->SetLabelFont(42);
  // Cerenkov->GetXaxis()->SetTitleOffset(1.);
  // Cerenkov->GetXaxis()->CenterTitle(1);
  // Cerenkov->GetXaxis()->SetTickLength(0.02);
  // if (fileName == "2.8MeVgamma50" || fileName == "2.8MeVelectron50")  {
  //   Cerenkov->GetXaxis()->SetTitleSize(0.);
  // }
  // else {
  //   Cerenkov->GetXaxis()->SetTitleSize(titleSize);
  // }
  // Cerenkov->GetXaxis()->SetLabelSize(Cerenkov->GetXaxis()->GetTitleSize());
  // Cerenkov->GetXaxis()->SetLabelSize(Cerenkov->GetXaxis()->GetTitleSize());
  // Cerenkov->GetXaxis()->SetTitleFont(42);


  // Cerenkov->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // Cerenkov->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // Cerenkov->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // Cerenkov->GetYaxis()->SetLabelFont(42);
  // Cerenkov->GetYaxis()->SetTitleOffset(1.);
  // Cerenkov->GetYaxis()->CenterTitle(1);
  // Cerenkov->GetYaxis()->SetTickLength(Cerenkov->GetXaxis()->GetTickLength());
  // if (fileName == "2.8MeVgamma50" || fileName == "0.38MeV2xpositron50")  {
  //   Cerenkov->GetYaxis()->SetTitleSize(0.);
  // }
  // else {
  //   Cerenkov->GetYaxis()->SetTitleSize(titleSize);
  // }
  // Cerenkov->GetYaxis()->SetLabelSize(Cerenkov->GetYaxis()->GetTitleSize());
  // Cerenkov->GetYaxis()->SetTitleFont(42);
  
  // Cerenkov->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // Cerenkov->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // Cerenkov->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // Cerenkov->GetZaxis()->SetLabelFont(42);
  // Cerenkov->GetZaxis()->SetTitleOffset(0.1);
  // Cerenkov->GetZaxis()->CenterTitle(1);
  // Cerenkov->GetZaxis()->SetTickLength(Cerenkov->GetXaxis()->GetTickLength());
  // Cerenkov->GetZaxis()->SetTitleSize(titleSize);
  // Cerenkov->GetZaxis()->SetLabelSize(titleSize-0.02);
  // Cerenkov->GetZaxis()->SetTitleFont(42);
  
  // Cerenkov->GetXaxis()->SetNdivisions(6);
  // Cerenkov->GetYaxis()->SetNdivisions(6);

  // Cerenkov->GetZaxis()->SetRangeUser(1,3.5e3);

  // Cerenkov->Draw("colz");
  // if (fileName != "2.8MeVelectron50") Cerenkov->Draw("col");

  // gStyle->SetLineStyleString(11,"200 100");
  
  // TLine *line = new TLine(minX, 0, maxX, 0);
  // line->SetLineStyle(9);
  // line->SetLineWidth(3);
  // line->SetLineColor(kGray+1);
  // line->Draw("SAME");
  
  // TLine *line2 = new TLine(0, minY, 0, maxY);
  // line2->SetLineStyle(line->GetLineStyle());
  // line2->SetLineWidth(line->GetLineWidth());
  // line2->SetLineColor(line->GetLineColor());
  // line2->Draw("SAME");

  // if (fileName == "2.8MeVelectron50") {
  //   TPaveText *pt = new TPaveText(-14.6,-39.3,14.9,-33.1);
  //   pt->AddText("Hits on fibres");
  //   pt->SetTextSize(titleSize-0.01);
  //   pt->SetTextFont(Cerenkov->GetXaxis()->GetTitleFont());
  //   pt->SetTextColor(Cerenkov->GetXaxis()->GetTitleColor());
  //   pt->SetFillColor(0);
  //   pt->Draw("SAME");
  // }

  // double x1_palette = -53.5;
  // double y1_palette = -53.5;
  // double x2_palette = 53.8;
  // double y2_palette = -42.8;

  // auto palette2 = new TPaletteAxis(x1_palette, y1_palette, x2_palette, y2_palette, Cerenkov);
  // Cerenkov->GetListOfFunctions()->Add(palette2);

  // // // draw contours of palette
  // // double boxThickness = 0.3;
  // // TBox *box = new TBox(x1_palette+boxThickness, y1_palette-boxThickness, x2_palette+boxThickness, y2_palette+boxThickness);
  // // box->SetFillColorAlpha(1,0.);
  // // box->SetLineColor(1);
  // // box->SetLineWidth(1);
  // // box->Draw("same");

  // palette2->Draw("same");

  TString OutputPngFile_XY = "plots/Visu_event_CSratio_" + fileName + "_event" + to_string(eventNumber) + ".png";
  // TString OutputPdfFile_XY = "plots/Visu_event_CSratio_" + fileName + "_event" + to_string(eventNumber) + ".pdf";
  c1->SaveAs(OutputPngFile_XY);
  // c1->SaveAs(OutputPdfFile_XY);
  
}
