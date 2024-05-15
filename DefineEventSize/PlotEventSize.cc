#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void PlotEventSize(){

  gStyle->SetOptStat(00000002210);
  
  // particleType, primaires et secondaires
  string path_to_files = "Results_Kitzia/max_distances_" ;

  string fNamePositronLow = path_to_files + "positron_low.txt";
  string fNamePositronHigh = path_to_files + "positron_high.txt";
  string fNameGamma = path_to_files + "gamma.txt";
  
  TGraph *grPositronLow = new TGraph(fNamePositronLow.c_str(), "%lg %lg", "");//or 
  TGraph *grPositronHigh = new TGraph(fNamePositronHigh.c_str(), "%lg %lg", "");//or 
  TGraph *grGamma = new TGraph(fNameGamma.c_str(), "%lg %lg", "");//or

  TH1* hPositronLow = new TH1I("hPositronLow", "", 20, 0.0, 400);
  TH1* hPositronHigh = new TH1I("hPositronHigh", "", 20, 0.0, 400);
  TH1* hGamma = new TH1I("hGamma", "", 20, 0.0, 400);

  for (int i = 0; i < grGamma->GetN(); i++) {
    hGamma->Fill(grGamma->GetPointY(i)/10.);
  }
  // hGamma->Scale(1./grGamma->GetN());
  
  for (int i = 0; i < grPositronLow->GetN(); i++) {
    hPositronLow->Fill(grPositronLow->GetPointY(i)/10.);
  }
  // hPositronLow->Scale(1./grPositronLow->GetN());

  for (int i = 0; i < grPositronHigh->GetN(); i++) {
    hPositronHigh->Fill(grPositronHigh->GetPointY(i)/10.);
  }
  // hPositronHigh->Scale(1./grPositronHigh->GetN());

  TCanvas *c1 = new TCanvas("c1","",2560,1368);
  c1->Divide(2,2);
  
  TGaxis::SetMaxDigits(7);

  TLegend *legend = new TLegend(0.677394, 0.725987, 0.896389, 0.895756);
  // legend->SetNColumns(2);
  legend->AddEntry(hPositronLow, "Positron 0.547 MeV", "l");
  legend->AddEntry(hPositronHigh, "Positron 1.821 MeV", "l");
  legend->AddEntry(hGamma, "Gamma 1.274 MeV", "l");
  
  legend->SetBorderSize(1);
  legend->SetLineColor(gPad->GetFrameLineColor());
  legend->SetFillColor(0);
  legend->SetTextColor(gPad->GetFrameLineColor());
  legend->SetTextSize(0.035);


  // TPad *c1_1 = new TPad("c1_1", "c1_1",0.01,0.01,0.3233333,0.99);
  // c1_1->Draw();
  // c1_1->cd();
  // c1_1->Range(-0.5460031,176.2357,1.204557,213.7683);
  // c1_1->SetFillColor(0);
  // c1_1->SetBorderMode(0);
  // c1_1->SetBorderSize(2);
  // c1_1->SetGridy();
  // c1_1->SetLeftMargin(0.1976528);
  // c1_1->SetRightMargin(0.002603431);

  // legend->Draw();

  c1->cd(1);

  // ----- general settings canvas
  
  // gPad->SetGridy();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hPositronLow->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hPositronLow->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hPositronLow->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hPositronLow->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hPositronLow->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hPositronLow->GetXaxis()->SetLabelSize(0.05);
  hPositronLow->GetXaxis()->SetLabelFont(42);
  // hPositronLow->GetXaxis()->SetTitleOffset(0.1);
  hPositronLow->GetXaxis()->CenterTitle(1);
  hPositronLow->GetXaxis()->SetTickLength(0.02);
  hPositronLow->GetXaxis()->SetTitleSize(0.05);
  hPositronLow->GetXaxis()->SetTitleFont(42);
  hPositronLow->GetXaxis()->SetNdivisions(7);
  
  hPositronLow->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hPositronLow->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hPositronLow->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hPositronLow->GetYaxis()->SetLabelSize(0.05);
  hPositronLow->GetYaxis()->SetLabelFont(42);
  hPositronLow->GetYaxis()->SetTitleOffset(1.5);
  hPositronLow->GetYaxis()->CenterTitle(1);
  hPositronLow->GetYaxis()->SetTickLength(0.02);
  hPositronLow->GetYaxis()->SetTitleSize(0.05);
  hPositronLow->GetYaxis()->SetTitleFont(42);
  hPositronLow->GetYaxis()->SetNdivisions(7);

  hPositronLow->GetXaxis()->SetTitle("Size of event (cm)");
  hPositronLow->GetXaxis()->SetRangeUser(0.,210.);
  hPositronLow->GetYaxis()->SetRangeUser(0.,42.);

  // -----------------------------

  hPositronLow->SetTitle("Positron 0.547 MeV");

  hPositronLow->SetLineColor(46);
  hPositronLow->SetLineWidth(2);
  hPositronLow->SetLineStyle(1);
  hPositronLow->SetMarkerStyle(50);
  hPositronLow->SetMarkerSize(4);
  hPositronLow->SetMarkerColor(hPositronLow->GetLineColor());
  hPositronLow->Draw("HIST");

  cout << "posit. 0.5 MeV " << hPositronLow->GetMean() << endl;
  // TLine *l1 = new TLine(hPositronLow->GetMean(),0,hPositronLow->GetMean(),42);
  // l1->Draw();
  
  c1->cd(2);

  // ----- general settings canvas
  
  // gPad->SetGridy();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hPositronHigh->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hPositronHigh->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hPositronHigh->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hPositronHigh->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hPositronHigh->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hPositronHigh->GetXaxis()->SetLabelSize(0.05);
  hPositronHigh->GetXaxis()->SetLabelFont(42);
  // hPositronHigh->GetXaxis()->SetTitleOffset(0.1);
  hPositronHigh->GetXaxis()->CenterTitle(1);
  hPositronHigh->GetXaxis()->SetTickLength(0.02);
  hPositronHigh->GetXaxis()->SetTitleSize(0.05);
  hPositronHigh->GetXaxis()->SetTitleFont(42);
  hPositronHigh->GetXaxis()->SetNdivisions(7);
  
  hPositronHigh->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hPositronHigh->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hPositronHigh->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hPositronHigh->GetYaxis()->SetLabelSize(0.05);
  hPositronHigh->GetYaxis()->SetLabelFont(42);
  hPositronHigh->GetYaxis()->SetTitleOffset(1.5);
  hPositronHigh->GetYaxis()->CenterTitle(1);
  hPositronHigh->GetYaxis()->SetTickLength(0.02);
  hPositronHigh->GetYaxis()->SetTitleSize(0.05);
  hPositronHigh->GetYaxis()->SetTitleFont(42);
  hPositronHigh->GetYaxis()->SetNdivisions(7);

  hPositronHigh->GetXaxis()->SetTitle("Size of event (cm)");
  hPositronHigh->GetXaxis()->SetRangeUser(0.,210.);
  hPositronHigh->GetYaxis()->SetRangeUser(0.,42.);

  // -----------------------------

  hPositronHigh->SetTitle("Positron 1.821 MeV");

  hPositronHigh->SetLineColor(kViolet-1);
  hPositronHigh->SetLineWidth(hPositronLow->GetLineWidth());
  hPositronHigh->SetLineStyle(hPositronLow->GetLineStyle());
  hPositronHigh->SetMarkerStyle(hPositronLow->GetMarkerStyle());
  hPositronHigh->SetMarkerSize(hPositronLow->GetMarkerSize());
  hPositronHigh->SetMarkerColor(hPositronHigh->GetLineColor());
  hPositronHigh->Draw("SAMEHIST");
  
  cout << "posit. 1.8 MeV " << hPositronHigh->GetMean() << endl; 

  c1->cd(3);

  // ----- general settings canvas
  
  // gPad->SetGridy();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hGamma->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hGamma->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hGamma->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hGamma->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hGamma->GetXaxis()->SetLabelSize(0.05);
  hGamma->GetXaxis()->SetLabelFont(42);
  // hGamma->GetXaxis()->SetTitleOffset(0.1);
  hGamma->GetXaxis()->CenterTitle(1);
  hGamma->GetXaxis()->SetTickLength(0.02);
  hGamma->GetXaxis()->SetTitleSize(0.05);
  hGamma->GetXaxis()->SetTitleFont(42);
  hGamma->GetXaxis()->SetNdivisions(7);
  
  hGamma->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetLabelSize(0.05);
  hGamma->GetYaxis()->SetLabelFont(42);
  hGamma->GetYaxis()->SetTitleOffset(1.5);
  hGamma->GetYaxis()->CenterTitle(1);
  hGamma->GetYaxis()->SetTickLength(0.02);
  hGamma->GetYaxis()->SetTitleSize(0.05);
  hGamma->GetYaxis()->SetTitleFont(42);
  hGamma->GetYaxis()->SetNdivisions(7);

  hGamma->GetXaxis()->SetTitle("Size of event (cm)");
  hGamma->GetXaxis()->SetRangeUser(0.,210.);
  hGamma->GetYaxis()->SetRangeUser(0.,42.);

  // -----------------------------
  
  hGamma->SetTitle("Gamma 1.274 MeV");

  hGamma->SetLineColor(30);
  hGamma->SetLineWidth(hPositronLow->GetLineWidth());
  hGamma->SetLineStyle(hPositronLow->GetLineStyle());
  hGamma->SetMarkerStyle(hPositronLow->GetMarkerStyle());
  hGamma->SetMarkerSize(hPositronLow->GetMarkerSize());
  hGamma->SetMarkerColor(hGamma->GetLineColor());
  hGamma->Draw("SAMEHIST");

  cout << "gamma " << hGamma->GetMean() << endl; 
  
  c1->SaveAs("EventSize.pdf");

  return 0;

}
