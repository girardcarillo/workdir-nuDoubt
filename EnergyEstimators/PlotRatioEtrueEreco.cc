void MyCanvasStyle1D(TH1F *hist){

  // gPad->SetLogz();

  // TGaxis::SetMaxDigits(4);

  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hist->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hist->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hist->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hist->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetTitleOffset(1.2);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetXaxis()->SetTickLength(0.01);
  hist->GetXaxis()->SetTitleSize(0.03);
  hist->GetXaxis()->SetLabelSize(hist->GetXaxis()->GetTitleSize()-0.01);
  hist->GetXaxis()->SetTitleFont(42);
  
  hist->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetTitleOffset(1.7);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTickLength(0.01);
  hist->GetYaxis()->SetTitleSize(0.03);
  hist->GetYaxis()->SetLabelSize(hist->GetXaxis()->GetLabelSize());
  hist->GetYaxis()->SetTitleFont(42);
  
  hist->GetXaxis()->SetNdivisions(7);
  hist->GetYaxis()->SetNdivisions(12);
  
}

double FindMaximumHistogram(double a, double b, double c) {

  double max;
  
  if (a >= b) {
    if (a >= c) {
      max = a;
    }
    else {
      max = c;
    }
  }
  else {
    if (b >= c) {
      max = b;
    }
    else {
      max = c;
    }
  }
  
  return max;
}

void PlotRatioEtrueEreco(string energy_estimator, int threshold) {

  string file_energy_estimator;
  if (energy_estimator == "1") file_energy_estimator = "FirstEnergyEstimator";
  else if (energy_estimator == "2") file_energy_estimator = "SecondEnergyEstimator";
  else {
    cout << "Wrong energy estimator chosen" << endl;
    return;
  }
 
  string path = "histograms/";

  //////////////////// High energy positron
  
  string fileName = "1.821positron75";

  string fileEnergy = path + "Ratio_Etrue_Ereco_" + file_energy_estimator + "_threshold_" + to_string(threshold) + "_" + fileName + ".root";
  const char * cfileEnergyHigh = fileEnergy.c_str();
  TFile *fEnergyHigh = new TFile(cfileEnergyHigh);
  TH1F* h_Ratio_High =(TH1F*)fEnergyHigh->Get("hist1D");

  //////////////////// Low energy positron
  
  fileName = "0.547MeVpositron100";

  fileEnergy = fileEnergy = path + "Ratio_Etrue_Ereco_" + file_energy_estimator + "_threshold_" + to_string(threshold) + "_" + fileName + ".root";
  const char * cfileEnergyLow = fileEnergy.c_str();
  TFile *fEnergyLow = new TFile(cfileEnergyLow);
  TH1F* h_Ratio_Low =(TH1F*)fEnergyLow->Get("hist1D");

  //////////////////// gamma

  fileName = "1.274MeVgamma100";

  fileEnergy = fileEnergy = path + "Ratio_Etrue_Ereco_" + file_energy_estimator + "_threshold_" + to_string(threshold) + "_" + fileName + ".root";
  const char * cfileEnergyGamma = fileEnergy.c_str();
  TFile *fEnergyGamma = new TFile(cfileEnergyGamma);
  TH1F* h_Ratio_Gamma =(TH1F*)fEnergyGamma->Get("hist1D");

  /////////////////////////////

  double maxY = FindMaximumHistogram(h_Ratio_High->GetMaximum(), h_Ratio_Low->GetMaximum(), h_Ratio_Gamma->GetMaximum()); 
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);

  gStyle->SetOptStat(0);

  // Set axis titles
  string titlethreshold;
  if (energy_estimator == "1") titlethreshold = "R = " + to_string(threshold) + " mm";
  if (energy_estimator == "2") titlethreshold = "N = " + to_string(threshold) + " hits of highest energy";
  const char * cthreshold = titlethreshold.c_str();
  h_Ratio_High->SetTitle(cthreshold);
  h_Ratio_High->GetXaxis()->SetTitle("#frac{E_{reco}-E_{true}}{E_{true}}");
  h_Ratio_High->GetYaxis()->SetTitle("# counts");
  h_Ratio_High->GetYaxis()->SetRangeUser(0, maxY + 0.1*maxY);

  MyCanvasStyle1D(h_Ratio_High);
  
  h_Ratio_High->SetLineColor(kViolet-1);
  h_Ratio_High->SetFillColorAlpha(h_Ratio_High->GetLineColor(),0.2);
  h_Ratio_High->SetLineWidth(2);
  h_Ratio_High->SetLineStyle(1);
  h_Ratio_High->SetMarkerStyle(50);
  h_Ratio_High->SetMarkerSize(4);
  h_Ratio_High->SetMarkerColor(h_Ratio_High->GetLineColor());
  h_Ratio_High->Draw("HIST");

  h_Ratio_Low->SetLineColor(46);
  h_Ratio_Low->SetFillColorAlpha(h_Ratio_Low->GetLineColor(),0.2);
  h_Ratio_Low->SetLineWidth(2);
  h_Ratio_Low->SetLineStyle(h_Ratio_High->GetLineStyle());
  h_Ratio_Low->SetMarkerStyle(h_Ratio_High->GetMarkerStyle());
  h_Ratio_Low->SetMarkerSize(h_Ratio_High->GetMarkerSize());
  h_Ratio_Low->SetMarkerColor(h_Ratio_Low->GetLineColor());
  h_Ratio_Low->Draw("HISTSAME");
  
  h_Ratio_Gamma->SetLineColor(30);
  h_Ratio_Gamma->SetFillColorAlpha(h_Ratio_Gamma->GetLineColor(),0.2);
  h_Ratio_Gamma->SetLineWidth(h_Ratio_High->GetLineWidth());
  h_Ratio_Gamma->SetLineStyle(h_Ratio_High->GetLineStyle());
  h_Ratio_Gamma->SetMarkerStyle(h_Ratio_High->GetMarkerStyle());
  h_Ratio_Gamma->SetMarkerSize(h_Ratio_High->GetMarkerSize());
  h_Ratio_Gamma->SetMarkerColor(h_Ratio_Gamma->GetLineColor());
  h_Ratio_Gamma->Draw("SAMEHIST");

  TLegend *l1 = new TLegend(0.106149, 0.785446, 0.370425, 0.894224);
  // l1->SetNColumns(2);;
  l1->AddEntry(h_Ratio_High, "e+ 1.821 MeV", "f");
  l1->AddEntry(h_Ratio_Low, "e+ 0.547 MeV", "f");
  l1->AddEntry(h_Ratio_Gamma, "#gamma  1.274 MeV", "f");

  l1->SetBorderSize(1);
  l1->SetLineColor(gPad->GetFrameLineColor());
  l1->SetFillColor(0);
  l1->SetTextColor(gPad->GetFrameLineColor());
  l1->SetTextSize(0.03);

  l1->Draw();
  
  string OutputPdfFile = "plots/Ratio_Etrue_Ereco_" + file_energy_estimator + "_threshold_" + to_string(threshold) + "mm_3EventType.pdf";
  const char * cOutputPdfFile = OutputPdfFile.c_str();
  c1->SaveAs(cOutputPdfFile);

}

