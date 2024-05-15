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

void VisualizeHits(string path, string fileName, int eventNumber = 0) {

  const char* eventTitle;
  if (fileName == "2.8MeVelectron50") eventTitle = "electron 2.8 MeV";
  else if (fileName == "2.8MeVgamma50") eventTitle = "gamma 2.8 MeV";
  else if (fileName == "1.78MeVpositron50") eventTitle = "single positron 1.78 MeV";
  else if (fileName == "1.78MeVpositron50") eventTitle = "two positrons 0.76 MeV each";
  
  gStyle->SetOptStat(0);
  
  double fiberPitch = 15.; // mm
  double particleGunX = 75.; // mm
  double particleGunY = 75.; // mm
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

  double minX = -800.;
  double maxX = 800.;
  
  double minY = -800.;
  double maxY = 800.;
    
  double minZ = -800.;
  double maxZ = 800.;

  int nbinsX = (maxX - minX) / fiberPitch;
  int nbinsY = (maxY - minY) / fiberPitch;

  // Create a 3D histogram
  // TH3F *histogramXYZ = new TH3F("histogramXYZ", "", 50, -400, 400, 50, -600, 200, 100, -600, 350);
  TH3F *histogramXYZ = new TH3F("histogramXYZ", "", 266, -1000, 1000, 266, -1000, 1000, 500, -1000, 1000);
  
  // Create a 2D histograms
  TH2F *histogramXY = new TH2F("histogramXY", "", nbinsX, minX, maxX, nbinsY, minY, maxY); // for electron zoom
  TH2F *histogramXZ = new TH2F("histogramXZ", "", nbinsX, minX, maxX, nbinsX, minZ, maxZ);
  TH2F *histogramYZ = new TH2F("histogramYZ", "", nbinsY, minY, maxY, nbinsY, minZ, maxZ);

  // Loop over entries and fill the histogram
  for (int i = 0; i < entries; i++) {
    tree->GetEntry(i);

    if (eventData.event == eventNumber) {
      
      histogramXY->Fill(eventData.hitx, eventData.hity);
      histogramXZ->Fill(eventData.hitx, eventData.hitz);
      histogramYZ->Fill(eventData.hity, eventData.hitz);
      histogramXYZ->Fill(eventData.hitx, eventData.hity, eventData.hitz);

    }

  }

  /////////////////////////// Visualization

  // plot xyz
  
  // // Create a canvas
  // TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);
  
  // // Set axis titles
  // histogramXYZ->GetXaxis()->SetTitle("x (mm)");
  // histogramXYZ->GetYaxis()->SetTitle("y (mm)");
  // histogramXYZ->GetZaxis()->SetTitle("z (mm)");

  // TGaxis::SetMaxDigits(3);

  // gPad->SetGridy();
  // gPad->SetFrameLineColor(kGray+3);
  // gPad->SetFrameLineWidth(1);

  // histogramXYZ->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  // histogramXYZ->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // // histogramXYZ->GetXaxis()->SetLabelSize(0.05);
  // histogramXYZ->GetXaxis()->SetLabelFont(42);
  // histogramXYZ->GetXaxis()->SetTitleOffset(1.9);
  // histogramXYZ->GetXaxis()->CenterTitle(1);
  // histogramXYZ->GetXaxis()->SetTickLength(0.02);
  // histogramXYZ->GetXaxis()->SetTitleSize(0.04);
  // histogramXYZ->GetXaxis()->SetTitleFont(42);
  // histogramXYZ->GetXaxis()->SetNdivisions(2);
  
  // histogramXYZ->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // // histogramXYZ->GetYaxis()->SetLabelSize(0.05);
  // histogramXYZ->GetYaxis()->SetLabelFont(42);
  // histogramXYZ->GetYaxis()->SetTitleOffset(1.9);
  // histogramXYZ->GetYaxis()->CenterTitle(1);
  // histogramXYZ->GetYaxis()->SetTickLength(0.02);
  // histogramXYZ->GetYaxis()->SetTitleSize(0.04);
  // histogramXYZ->GetYaxis()->SetTitleFont(42);
  
  // histogramXYZ->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // histogramXYZ->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // // histogramXYZ->GetZaxis()->SetLabelSize(0.05);
  // histogramXYZ->GetZaxis()->SetLabelFont(42);
  // histogramXYZ->GetZaxis()->SetTitleOffset(1.1);
  // histogramXYZ->GetZaxis()->CenterTitle(1);
  // histogramXYZ->GetZaxis()->SetTickLength(0.02);
  // histogramXYZ->GetZaxis()->SetTitleSize(0.04);
  // histogramXYZ->GetZaxis()->SetTitleFont(42);

  // histogramXYZ->GetXaxis()->SetNdivisions(7);
  // histogramXYZ->GetYaxis()->SetNdivisions(7);
  // histogramXYZ->GetZaxis()->SetNdivisions(7);

  // histogramXYZ->Draw("lego2z");

  // plot XY 
  
  TCanvas *c2 = new TCanvas("c2", "c2",0,72,1368,1368);

  gPad->SetLogz();

  gStyle->SetPalette(kSunset);
  // TColor::InvertPalette();

  // Set axis titles
  // histogramXY->SetTitle(eventTitle);
  histogramXY->GetXaxis()->SetTitle("x (mm)");
  histogramXY->GetYaxis()->SetTitle("y (mm)");
  histogramXY->GetZaxis()->SetTitle("");
  // histogramXY->GetZaxis()->SetTitle("Hits on fibres");

  TGaxis::SetMaxDigits(10);

  // gPad->SetGridy();
  // gPad->SetGridx();
  gPad->SetFrameLineColor(kGray+3);
  gPad->SetFrameLineWidth(1);

  histogramXY->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  histogramXY->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  histogramXY->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  histogramXY->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetXaxis()->SetLabelFont(42);
  histogramXY->GetXaxis()->SetTitleOffset(1.2);
  histogramXY->GetXaxis()->CenterTitle(1);
  histogramXY->GetXaxis()->SetTickLength(0.01);
  histogramXY->GetXaxis()->SetTitleSize(0.03);
  histogramXY->GetXaxis()->SetLabelSize(histogramXY->GetXaxis()->GetTitleSize());
  histogramXY->GetXaxis()->SetTitleFont(42);
  
  histogramXY->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetYaxis()->SetLabelFont(42);
  histogramXY->GetYaxis()->SetTitleOffset(1.7);
  histogramXY->GetYaxis()->CenterTitle(1);
  histogramXY->GetYaxis()->SetTickLength(histogramXY->GetXaxis()->GetTickLength());
  histogramXY->GetYaxis()->SetTitleSize(histogramXY->GetXaxis()->GetTitleSize());
  histogramXY->GetYaxis()->SetLabelSize(histogramXY->GetXaxis()->GetLabelSize());
  histogramXY->GetYaxis()->SetTitleFont(42);
  
  histogramXY->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  histogramXY->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  histogramXY->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  histogramXY->GetZaxis()->SetLabelFont(42);
  histogramXY->GetZaxis()->SetTitleOffset(1.4);
  histogramXY->GetZaxis()->CenterTitle(1);
  histogramXY->GetZaxis()->SetTickLength(histogramXY->GetXaxis()->GetTickLength());
  histogramXY->GetZaxis()->SetTitleSize(histogramXY->GetXaxis()->GetTitleSize());
  histogramXY->GetZaxis()->SetLabelSize(histogramXY->GetXaxis()->GetLabelSize());
  histogramXY->GetZaxis()->SetTitleFont(42);
  
  histogramXY->GetXaxis()->SetNdivisions(10);
  histogramXY->GetYaxis()->SetNdivisions(10);

  histogramXY->GetZaxis()->SetRangeUser(1,3.5e3);

  // TPaletteAxis *palette = new TPaletteAxis(870,-800,810,800,histogramXY);
  // histogramXY->GetListOfFunctions()->Add(palette,"br");

  histogramXY->Draw("colz");

  TLine *line = new TLine(minX, particleGunY, maxX, particleGunY);
  line->SetLineStyle(7);
  line->SetLineWidth(2);
  line->SetLineColor(kGray+1);
  line->Draw("SAME");
  
  TLine *line2 = new TLine(particleGunX, minY, particleGunX, maxY);
  line2->SetLineStyle(line->GetLineStyle());
  line2->SetLineWidth(line->GetLineWidth());
  line2->SetLineColor(line->GetLineColor());
  line2->Draw("SAME");

  TPaveText *pt = new TPaveText(-155.93,-550,155,-495);
  pt->AddText("Hits on fibres");
  pt->SetTextSize(histogramXY->GetXaxis()->GetTitleSize());
  pt->SetTextFont(histogramXY->GetXaxis()->GetTitleFont());
  pt->SetTextColor(histogramXY->GetXaxis()->GetTitleColor());
  pt->SetFillColor(0);
  pt->Draw("SAME");

  auto palette2 = new TPaletteAxis(-600,-625,600,-565,histogramXY);
  histogramXY->GetListOfFunctions()->Add(palette2);
  palette2->Draw("same");
   
  TString OutputRootFile_XY = "plots/Visu_event_XY_" + fileName + "_event" + to_string(eventNumber) + ".png";
  c2->SaveAs(OutputRootFile_XY);
  
  // // plot XZ 
  
  // TCanvas *c3 = new TCanvas("c3", "c3",0,72,1368,1368);

  // gPad->SetLogz();

  // // Set axis titles
  // histogramXZ->GetXaxis()->SetTitle("x (mm)");
  // histogramXZ->GetYaxis()->SetTitle("z (mm)");
  // histogramXZ->GetZaxis()->SetTitle("Amount of light collected (a.u.)");

  // TGaxis::SetMaxDigits(5);

  // gPad->SetGridy();
  // gPad->SetGridx();
  // gPad->SetFrameLineColor(kGray+3);
  // gPad->SetFrameLineWidth(1);

  // histogramXZ->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // histogramXZ->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  // histogramXZ->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // histogramXZ->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // histogramXZ->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // histogramXZ->GetXaxis()->SetLabelFont(42);
  // histogramXZ->GetXaxis()->SetTitleOffset(1.2);
  // histogramXZ->GetXaxis()->CenterTitle(1);
  // histogramXZ->GetXaxis()->SetTickLength(0.02);
  // histogramXZ->GetXaxis()->SetTitleSize(0.03);
  // histogramXZ->GetXaxis()->SetLabelSize(histogramXZ->GetXaxis()->GetTitleSize()-0.01);
  // histogramXZ->GetXaxis()->SetTitleFont(42);
  
  // histogramXZ->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // histogramXZ->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // histogramXZ->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // histogramXZ->GetYaxis()->SetLabelFont(42);
  // histogramXZ->GetYaxis()->SetTitleOffset(1.7);
  // histogramXZ->GetYaxis()->CenterTitle(1);
  // histogramXZ->GetYaxis()->SetTickLength(0.02);
  // histogramXZ->GetYaxis()->SetTitleSize(0.03);
  // histogramXZ->GetYaxis()->SetLabelSize(histogramXZ->GetXaxis()->GetLabelSize());
  // histogramXZ->GetYaxis()->SetTitleFont(42);
  
  // histogramXZ->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // histogramXZ->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // histogramXZ->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // histogramXZ->GetZaxis()->SetLabelFont(42);
  // histogramXZ->GetZaxis()->SetTitleOffset(1.4);
  // histogramXZ->GetZaxis()->CenterTitle(1);
  // histogramXZ->GetZaxis()->SetTickLength(0.02);
  // histogramXZ->GetZaxis()->SetTitleSize(0.019);
  // histogramXZ->GetZaxis()->SetLabelSize(0.015);
  // histogramXZ->GetZaxis()->SetTitleFont(42);
  
  // histogramXZ->GetXaxis()->SetNdivisions(20);
  // histogramXZ->GetYaxis()->SetNdivisions(20);

  // // histogramXZ->Draw("surf2z");
  // histogramXZ->Draw("colz");

  // TEllipse elgen_XZ(particleGunX,particleGunZ,20.,20.);
  // elgen_XZ.SetLineColor(kCyan);
  // elgen_XZ.SetFillColorAlpha(kBlack,0);
  // elgen_XZ.SetLineWidth(4);
  // elgen_XZ.SetLineStyle(1);
  // elgen_XZ.Draw("SAME");

  // TString OutputRootFile_XZ = "plots/Visu_event_XZ_" + fileName + "_event" + to_string(eventNumber) + ".png";
  // c3->SaveAs(OutputRootFile_XZ);

}
