void PlotEnergyDistance_all() {

  string path = "histograms/";

  //////////////////// High energy positron
  
  string fileName = "1.821positron75";

  string fileEnergy = path + "Distance_energy_" + fileName + ".root";
  const char * cfileEnergyHigh = fileEnergy.c_str();
  TFile *fEnergyHigh = new TFile(cfileEnergyHigh);
  TH1F* h_distance_energy_High =(TH1F*)fEnergyHigh->Get("h1_distance_energy");
  
  string fileEnergyCum = path + "Distance_energyCum_" + fileName + ".root";
  const char * cfileEnergyCumHigh = fileEnergyCum.c_str();
  TFile *fEnergyCumHigh = new TFile(cfileEnergyCumHigh);
  TH1F* h_distance_energyCum_High =(TH1F*)fEnergyCumHigh->Get("h1_distance_energy_cumulative");

  //////////////////// Low energy positron
  
  fileName = "0.547MeVpositron100";

  fileEnergy = path + "Distance_energy_" + fileName + ".root";
  const char * cfileEnergyLow = fileEnergy.c_str();
  TFile *fEnergyLow = new TFile(cfileEnergyLow);
  TH1F* h_distance_energy_Low =(TH1F*)fEnergyLow->Get("h1_distance_energy");
  
  fileEnergyCum = path + "Distance_energyCum_" + fileName + ".root";
  const char * cfileEnergyCumLow = fileEnergyCum.c_str();
  TFile *fEnergyCumLow = new TFile(cfileEnergyCumLow);
  TH1F* h_distance_energyCum_Low =(TH1F*)fEnergyCumLow->Get("h1_distance_energy_cumulative");

  //////////////////// gamma

  fileName = "1.274MeVgamma100";

  fileEnergy = path + "Distance_energy_" + fileName + ".root";
  const char * cfileEnergyGamma = fileEnergy.c_str();
  TFile *fEnergyGamma = new TFile(cfileEnergyGamma);
  TH1F* h_distance_energy_Gamma =(TH1F*)fEnergyGamma->Get("h1_distance_energy");
  
  fileEnergyCum = path + "Distance_energyCum_" + fileName + ".root";
  const char * cfileEnergyCumGamma = fileEnergyCum.c_str();
  TFile *fEnergyCumGamma = new TFile(cfileEnergyCumGamma);
  TH1F* h_distance_energyCum_Gamma =(TH1F*)fEnergyCumGamma->Get("h1_distance_energy_cumulative");

  /////////////////////////////
  
  double maxX = 1250.;

  cout << "Warning! Manual normalization to the number of simulated events!" << endl;
  int scaleFactorHigh = 75;
  int scaleFactorLow = 100;
  int scaleFactorGamma = 100;
    
  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);

  gStyle->SetOptStat(0);

  // Set axis titles
  h_distance_energy_High->GetYaxis()->SetTitle("Amount of light collected (a.u.)");
  h_distance_energy_High->GetXaxis()->SetTitle("Distance to vertex (mm)");

  TGaxis::SetMaxDigits(5);

  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  h_distance_energy_High->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  h_distance_energy_High->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetXaxis()->SetLabelFont(42);
  h_distance_energy_High->GetXaxis()->SetTitleOffset(1.2);
  h_distance_energy_High->GetXaxis()->CenterTitle(1);
  h_distance_energy_High->GetXaxis()->SetTickLength(0.02);
  h_distance_energy_High->GetXaxis()->SetTitleSize(0.03);
  h_distance_energy_High->GetXaxis()->SetLabelSize(h_distance_energy_High->GetXaxis()->GetTitleSize()-0.01);
  h_distance_energy_High->GetXaxis()->SetTitleFont(42);
    
  h_distance_energy_High->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  h_distance_energy_High->GetYaxis()->SetLabelFont(42);
  h_distance_energy_High->GetYaxis()->SetTitleOffset(1.2);
  h_distance_energy_High->GetYaxis()->CenterTitle(1);
  h_distance_energy_High->GetYaxis()->SetTickLength(0.02);
  h_distance_energy_High->GetYaxis()->SetTitleSize(0.03);
  h_distance_energy_High->GetYaxis()->SetLabelSize(h_distance_energy_High->GetYaxis()->GetTitleSize()-0.01);
  h_distance_energy_High->GetYaxis()->SetTitleFont(42);
    
  h_distance_energy_High->Scale(1./scaleFactorHigh);
  h_distance_energy_Low->Scale(1./scaleFactorLow);
  h_distance_energy_Gamma->Scale(1./scaleFactorGamma);

  h_distance_energy_High->GetYaxis()->SetRangeUser(3,14e3); 
  h_distance_energy_High->GetXaxis()->SetRangeUser(0,maxX); 

  h_distance_energy_High->SetLineColor(kViolet-1);
  h_distance_energy_High->SetFillColorAlpha(h_distance_energy_High->GetLineColor(),0.1);
  h_distance_energy_High->SetLineWidth(2);
  h_distance_energy_High->SetLineStyle(1);
  h_distance_energy_High->SetMarkerStyle(50);
  h_distance_energy_High->SetMarkerSize(4);
  h_distance_energy_High->SetMarkerColor(h_distance_energy_High->GetLineColor());
  h_distance_energy_High->Draw("HIST");

  h_distance_energy_Low->SetLineColor(46);
  h_distance_energy_Low->SetFillColorAlpha(h_distance_energy_Low->GetLineColor(),0.1);
  h_distance_energy_Low->SetLineWidth(2);
  h_distance_energy_Low->SetLineStyle(h_distance_energy_High->GetLineStyle());
  h_distance_energy_Low->SetMarkerStyle(h_distance_energy_High->GetMarkerStyle());
  h_distance_energy_Low->SetMarkerSize(h_distance_energy_High->GetMarkerSize());
  h_distance_energy_Low->SetMarkerColor(h_distance_energy_Low->GetLineColor());
  h_distance_energy_Low->Draw("HISTSAME");
  
  h_distance_energy_Gamma->SetLineColor(30);
  h_distance_energy_Gamma->SetFillColorAlpha(h_distance_energy_Gamma->GetLineColor(),0.1);
  h_distance_energy_Gamma->SetLineWidth(h_distance_energy_High->GetLineWidth());
  h_distance_energy_Gamma->SetLineStyle(h_distance_energy_High->GetLineStyle());
  h_distance_energy_Gamma->SetMarkerStyle(h_distance_energy_High->GetMarkerStyle());
  h_distance_energy_Gamma->SetMarkerSize(h_distance_energy_High->GetMarkerSize());
  h_distance_energy_Gamma->SetMarkerColor(h_distance_energy_Gamma->GetLineColor());
  h_distance_energy_Gamma->Draw("SAMEHIST");

  TLegend *l1 = new TLegend(0.603953, 0.669917, 0.891654, 0.829707);
  // l1->SetNColumns(2);;
  l1->AddEntry(h_distance_energy_High, "e+ 1.821 MeV", "f");
  l1->AddEntry(h_distance_energy_Low, "e+ 0.547 MeV", "f");
  l1->AddEntry(h_distance_energy_Gamma, "#gamma  1.274 MeV", "f");

  l1->SetBorderSize(1);
  l1->SetLineColor(gPad->GetFrameLineColor());
  l1->SetFillColor(0);
  l1->SetTextColor(gPad->GetFrameLineColor());
  l1->SetTextSize(0.035);

  l1->Draw();
  
  c1->SaveAs("plots/Distance_energy_3EventType.pdf");
  
  TCanvas *c2 = new TCanvas("c2", "c2",0,72,1368,1368);

  gStyle->SetOptStat(0);

  // Set axis titles
  h_distance_energyCum_High->SetTitle("Cumulative");
  h_distance_energyCum_High->GetYaxis()->SetTitle("Amount of light collected (a.u.)");
  h_distance_energyCum_High->GetXaxis()->SetTitle("Distance to vertex (mm)");

  TGaxis::SetMaxDigits(5);

  // gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  h_distance_energyCum_High->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  h_distance_energyCum_High->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetXaxis()->SetLabelFont(42);
  h_distance_energyCum_High->GetXaxis()->SetTitleOffset(1.2);
  h_distance_energyCum_High->GetXaxis()->CenterTitle(1);
  h_distance_energyCum_High->GetXaxis()->SetTickLength(0.02);
  h_distance_energyCum_High->GetXaxis()->SetTitleSize(0.03);
  h_distance_energyCum_High->GetXaxis()->SetLabelSize(h_distance_energyCum_High->GetXaxis()->GetTitleSize()-0.01);
  h_distance_energyCum_High->GetXaxis()->SetTitleFont(42);
    
  h_distance_energyCum_High->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  h_distance_energyCum_High->GetYaxis()->SetLabelFont(42);
  h_distance_energyCum_High->GetYaxis()->SetTitleOffset(1.5);
  h_distance_energyCum_High->GetYaxis()->CenterTitle(1);
  h_distance_energyCum_High->GetYaxis()->SetTickLength(0.02);
  h_distance_energyCum_High->GetYaxis()->SetTitleSize(0.03);
  h_distance_energyCum_High->GetYaxis()->SetLabelSize(h_distance_energyCum_High->GetYaxis()->GetTitleSize()-0.01);
  h_distance_energyCum_High->GetYaxis()->SetTitleFont(42);
    
  h_distance_energyCum_High->Scale(1./scaleFactorHigh);
  h_distance_energyCum_Low->Scale(1./scaleFactorLow);
  h_distance_energyCum_Gamma->Scale(1./scaleFactorGamma);

  h_distance_energyCum_High->GetYaxis()->SetRangeUser(0.1,20e3);  
  h_distance_energyCum_High->GetXaxis()->SetRangeUser(0,maxX);

  h_distance_energyCum_High->SetLineColor(kViolet-1);
  h_distance_energyCum_High->SetLineWidth(2);
  h_distance_energyCum_High->SetLineStyle(1);
  h_distance_energyCum_High->SetMarkerStyle(50);
  h_distance_energyCum_High->SetMarkerSize(4);
  h_distance_energyCum_High->SetMarkerColor(h_distance_energyCum_High->GetLineColor());
  h_distance_energyCum_High->Draw("HIST");

  h_distance_energyCum_Low->SetLineColor(46);
  h_distance_energyCum_High->SetLineWidth(2);
  h_distance_energyCum_Low->SetLineWidth(2);
  h_distance_energyCum_Low->SetLineStyle(h_distance_energyCum_High->GetLineStyle());
  h_distance_energyCum_Low->SetMarkerStyle(h_distance_energyCum_High->GetMarkerStyle());
  h_distance_energyCum_Low->SetMarkerSize(h_distance_energyCum_High->GetMarkerSize());
  h_distance_energyCum_Low->SetMarkerColor(h_distance_energyCum_Low->GetLineColor());
  h_distance_energyCum_Low->Draw("HISTSAME");
  
  h_distance_energyCum_Gamma->SetLineColor(30);
  h_distance_energyCum_Gamma->SetLineWidth(h_distance_energyCum_High->GetLineWidth());
  h_distance_energyCum_Gamma->SetLineStyle(h_distance_energyCum_High->GetLineStyle());
  h_distance_energyCum_Gamma->SetMarkerStyle(h_distance_energyCum_High->GetMarkerStyle());
  h_distance_energyCum_Gamma->SetMarkerSize(h_distance_energyCum_High->GetMarkerSize());
  h_distance_energyCum_Gamma->SetMarkerColor(h_distance_energyCum_Gamma->GetLineColor());
  h_distance_energyCum_Gamma->Draw("SAMEHIST");

  TLegend *l2 = new TLegend(0.603953, 0.669917, 0.891654, 0.829707); // linear scale
  // l2->SetNColumns(2);;
  l2->AddEntry(h_distance_energyCum_High, "e+ 1.821 MeV", "f");
  l2->AddEntry(h_distance_energyCum_Low, "e+ 0.547 MeV", "f");
  l2->AddEntry(h_distance_energyCum_Gamma, "#gamma  1.274 MeV", "f");

  l2->SetBorderSize(1);
  l2->SetLineColor(gPad->GetFrameLineColor());
  l2->SetFillColor(0);
  l2->SetTextColor(gPad->GetFrameLineColor());
  l2->SetTextSize(0.035);

  l2->Draw();
  
  c2->SaveAs("plots/Distance_energyCum_3EventType.pdf");
  
}

