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
  TH2F *ratio = new TH2F("Ratio", "", nbinsX, minX, maxX, nbinsY, minY, maxY); // for electron zoom

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

  ratio = (TH2F*)Cerenkov->Clone("ratio");
  ratio->Divide(Scintillation);

  int binnum = 0;
  double nchit = 0.;
  double nc = 0.;
  double ratio_value = 0.;

  for(int k=0;k<ratio->GetNbinsX(); k++){
    for(int l=0;l<ratio->GetNbinsY(); l++){
      binnum = ratio->GetBin(k+1, l+1);
      nchit = Cerenkov->GetBinContent(binnum);
      nc = Scintillation->GetBinContent(binnum);
      ratio_value = nchit/nc;

      // if(nchit == 0 && nc != 0) heffprojStripY[j]->SetBinContent(binnum, 1e-6);  // small number instead of 0
      if(ratio_value == 0) ratio->SetBinContent(binnum, 1e-7);  // small number instead of 0

    }
  }

  // // tests visus

  // TCanvas *c1 = new TCanvas("c1", "c1",70,64,936,1016);
  // gStyle->SetOptStat(0);
  // c1->Range(-82.67568,-87.5443,94.02703,87.36709);
  // c1->SetFillColor(0);
  // c1->SetBorderMode(0);
  // c1->SetBorderSize(2);
  // c1->SetLogz();
  // c1->SetLeftMargin(0.07173447);
  // c1->SetRightMargin(0.1359743);
  // c1->SetFrameBorderMode(0);
  // c1->SetFrameBorderMode(0);

  // Cerenkov->SetTitle(eventTitle);
  // // c1->Divide(1,2);
  // // c1->cd(1);
  // gPad->SetLogz();

  // Cerenkov->GetZaxis()->SetRangeUser(1e-3,1);

  // Cerenkov->Draw("colz");
  // // Cerenkov->GetZaxis()->SetTitleOffset(10);
  // // Cerenkov->GetZaxis()->SetTitleSize(0.1);
  // // c1->cd(2);
  // // gPad->SetLogz();
  // // Scintillation->Draw("colz");
  // gStyle->SetPalette(kGreenPink);

  // TPaletteAxis *palette = new TPaletteAxis(72.27027,-70,80.21622,70,Cerenkov);
  // palette->SetLabelColor(1);
  // palette->SetLabelFont(42);
  // palette->SetLabelOffset(0.005);
  // palette->SetLabelSize(0.035);
  // palette->SetTitleOffset(1);
  // palette->SetTitleSize(0.035);

  /////////////////////////// Visualization

  // plot C/S

  // to comment: changed because worked on personal laptop and dimensions changed
  TCanvas *c1 = new TCanvas("c1", "c1",70,64,1081,1016);
  // to uncomment: changed because worked on personal laptop and dimensions changed
  // TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);
  /////////////////////////////////////////////////////

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

  // gPad->SetLogz();

  // c1->SetGrayscale();
  gStyle->SetPalette(kCandy);

  // TColor::InvertPalette();

  // Set axis titles
  // ratio->SetTitle(eventTitle);
  ratio->GetXaxis()->SetTitle("x (cm)");
  ratio->GetYaxis()->SetTitle("y (cm)");
  ratio->GetZaxis()->SetTitle("");
  // ratio->GetZaxis()->SetTitle("Hits on fibres");

  TGaxis::SetMaxDigits(10);

  // gPad->SetGridy();
  // gPad->SetGridx();
  // gPad->SetFrameLineColor(kGray+3);
  gPad->SetFrameLineWidth(2);

  double titleSize = 0.07;

  ratio->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  ratio->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());

  ratio->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  ratio->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  ratio->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  ratio->GetXaxis()->SetLabelFont(42);
  ratio->GetXaxis()->SetTitleOffset(1.);
  ratio->GetXaxis()->CenterTitle(1);
  ratio->GetXaxis()->SetTickLength(0.02);
  if (fileName == "2.8MeVgamma50" || fileName == "2.8MeVelectron50")  {
    ratio->GetXaxis()->SetTitleSize(0.);
  }
  else {
    ratio->GetXaxis()->SetTitleSize(titleSize);
  }
  ratio->GetXaxis()->SetLabelSize(ratio->GetXaxis()->GetTitleSize());
  ratio->GetXaxis()->SetLabelSize(ratio->GetXaxis()->GetTitleSize());
  ratio->GetXaxis()->SetTitleFont(42);

  ratio->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  ratio->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  ratio->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  ratio->GetYaxis()->SetLabelFont(42);
  ratio->GetYaxis()->SetTitleOffset(1.);
  ratio->GetYaxis()->CenterTitle(1);
  ratio->GetYaxis()->SetTickLength(ratio->GetXaxis()->GetTickLength());
  if (fileName == "2.8MeVgamma50" || fileName == "0.38MeV2xpositron50")  {
    ratio->GetYaxis()->SetTitleSize(0.);
  }
  else {
    ratio->GetYaxis()->SetTitleSize(titleSize);
  }
  ratio->GetYaxis()->SetLabelSize(ratio->GetYaxis()->GetTitleSize());
  ratio->GetYaxis()->SetTitleFont(42);

  ratio->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  ratio->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  ratio->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  ratio->GetZaxis()->SetLabelFont(42);
  ratio->GetZaxis()->SetTitleOffset(0.1);
  ratio->GetZaxis()->CenterTitle(1);
  ratio->GetZaxis()->SetTickLength(ratio->GetXaxis()->GetTickLength());
  ratio->GetZaxis()->SetTitleSize(titleSize);
  ratio->GetZaxis()->SetLabelSize(titleSize-0.02);
  ratio->GetZaxis()->SetTitleFont(42);

  ratio->GetXaxis()->SetNdivisions(6);
  ratio->GetYaxis()->SetNdivisions(6);

  ratio->GetZaxis()->SetRangeUser(1e-8,1);

  ratio->Draw("colz");
  if (fileName != "2.8MeVelectron50") ratio->Draw("col");

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
    pt->SetTextFont(ratio->GetXaxis()->GetTitleFont());
    pt->SetTextColor(ratio->GetXaxis()->GetTitleColor());
    pt->SetFillColor(0);
    pt->Draw("SAME");
  }

  double x1_palette = -53.5;
  double y1_palette = -53.5;
  double x2_palette = 53.8;
  double y2_palette = -42.8;

  auto palette2 = new TPaletteAxis(x1_palette, y1_palette, x2_palette, y2_palette, ratio);
  ratio->GetListOfFunctions()->Add(palette2);

  // // draw contours of palette
  // double boxThickness = 0.3;
  // TBox *box = new TBox(x1_palette+boxThickness, y1_palette-boxThickness, x2_palette+boxThickness, y2_palette+boxThickness);
  // box->SetFillColorAlpha(1,0.);
  // box->SetLineColor(1);
  // box->SetLineWidth(1);
  // box->Draw("same");

  palette2->Draw("same");

  // TString OutputPngFile_XY = "plots/Visu_event_CSratio_" + fileName + "_event" + to_string(eventNumber) + ".png";
  // // TString OutputPdfFile_XY = "plots/Visu_event_CSratio_" + fileName + "_event" + to_string(eventNumber) + ".pdf";
  // c1->SaveAs(OutputPngFile_XY);
  // // c1->SaveAs(OutputPdfFile_XY);

}
