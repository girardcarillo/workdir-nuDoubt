void PlotLightRatio_hist(string threshold){

  string filePositronLow = "txtFiles/threshold_" + threshold + "mm/Energy_first_rest_0.547MeVpositron100.txt";
  const char *cfilePositronLow = filePositronLow.c_str();

  string filePositronHigh = "txtFiles/threshold_" + threshold + "mm/Energy_first_rest_1.821positron75.txt";
  const char *cfilePositronHigh = filePositronHigh.c_str();

  string fileGamma = "txtFiles/threshold_" + threshold + "mm/Energy_first_rest_1.274MeVgamma100.txt";
  const char *cfileGamma = fileGamma.c_str();

  TGraph *grPositronHigh = new TGraph(cfilePositronLow, "%lg %lg", "");
  TGraph *grPositronLow = new TGraph(cfilePositronHigh, "%lg %lg", "");
  TGraph *grGamma = new TGraph(cfileGamma, "%lg %lg", "");

  int nPointsPositronHigh = grPositronHigh->GetN(); // Get the number of points
  double *xPositronHigh = grPositronHigh->GetX();
  double *yPositronHigh = grPositronHigh->GetY();

  int nPointsPositronLow = grPositronLow->GetN(); // Get the number of points
  double *xPositronLow = grPositronLow->GetX();
  double *yPositronLow = grPositronLow->GetY();

  int nPointsGamma = grGamma->GetN(); // Get the number of points
  double *xGamma = grGamma->GetX();
  double *yGamma = grGamma->GetY();

  cout << "Number of points in grPositronHigh: " << nPointsPositronHigh << endl;
  cout << "Number of points in grPositronHigh: " << nPointsPositronLow << endl;
  cout << "Number of points in grPositronHigh: " << nPointsGamma << endl;
  
  // Define histogram bin edges
  const int nBins = 15; // Adjust the number of bins as needed
  double xmin = 0.;
  double xmax = 20.; // 4 10 20
  double binWidth = (xmax - xmin) / nBins;
  double binEdges[nBins + 1];
  for (int i = 0; i <= nBins; ++i) {
    binEdges[i] = xmin + i * binWidth;
  }

  auto hHigh = new TH1F("hHigh", "", nBins, binEdges);
  auto hLow = new TH1F("hLow", "", nBins, binEdges);
  auto hGamma = new TH1F("hGamma", "", nBins, binEdges);

  // Fill the histogram
  for (int i = 0; i < nPointsPositronHigh; ++i) {
    hHigh->Fill(yPositronHigh[i]);
  }

  // Fill the histogram
  for (int i = 0; i < nPointsPositronLow; ++i) {
    hLow->Fill(yPositronLow[i]);
  }

  // Fill the histogram
  for (int i = 0; i < nPointsGamma; ++i) {
    hGamma->Fill(yGamma[i]);
  }

  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);

  // gPad->SetLogy();

  gStyle->SetOptStat(0);
 
  TGaxis::SetMaxDigits(5);

  double maxY = 70.; // 90 90 70

  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hHigh->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hHigh->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hHigh->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hHigh->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hHigh->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hHigh->GetXaxis()->SetLabelFont(42);
  hHigh->GetXaxis()->SetTitleOffset(1.2);
  hHigh->GetXaxis()->CenterTitle(1);
  hHigh->GetXaxis()->SetTickLength(0.02);
  hHigh->GetXaxis()->SetTitleSize(0.03);
  hHigh->GetXaxis()->SetLabelSize(hHigh->GetXaxis()->GetTitleSize()-0.01);
  hHigh->GetXaxis()->SetTitleFont(42);
  
  hHigh->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hHigh->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hHigh->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hHigh->GetYaxis()->SetLabelFont(42);
  hHigh->GetYaxis()->SetTitleOffset(1.7);
  hHigh->GetYaxis()->CenterTitle(1);
  hHigh->GetYaxis()->SetTickLength(0.02);
  hHigh->GetYaxis()->SetTitleSize(0.03);
  hHigh->GetYaxis()->SetLabelSize(hHigh->GetXaxis()->GetLabelSize());
  hHigh->GetYaxis()->SetTitleFont(42);
  
  hHigh->GetXaxis()->SetNdivisions(10);
  hHigh->GetYaxis()->SetNdivisions(10);

  // hHigh->GetXaxis()->SetLimits(-1,3);
  // // hHigh->GetYaxis()->SetRangeUser(1e-3,stoi(threshold)/10.);
  hHigh->GetYaxis()->SetRangeUser(1e-3,maxY);

  hHigh->SetTitle("");
  hHigh->GetXaxis()->SetTitle("Ratio");
  
  hHigh->SetLineColor(kMagenta+2);
  hHigh->SetMarkerColor(hHigh->GetLineColor());
  hHigh->SetLineWidth(2);
  hHigh->SetMarkerStyle(8);
  
  hHigh->Draw();

  TString OutputFileHigh = "plots/Energy_ratio_High" + threshold + ".png";
  c1->SaveAs(OutputFileHigh);

  TCanvas *c2 = new TCanvas("c2", "c2",0,72,1368,1368);

  // gPad->SetLogy();

  gStyle->SetOptStat(0);
 
  TGaxis::SetMaxDigits(5);

  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hLow->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hLow->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hLow->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hLow->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hLow->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hLow->GetXaxis()->SetLabelFont(42);
  hLow->GetXaxis()->SetTitleOffset(1.2);
  hLow->GetXaxis()->CenterTitle(1);
  hLow->GetXaxis()->SetTickLength(0.02);
  hLow->GetXaxis()->SetTitleSize(0.03);
  hLow->GetXaxis()->SetLabelSize(hLow->GetXaxis()->GetTitleSize()-0.01);
  hLow->GetXaxis()->SetTitleFont(42);
  
  hLow->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hLow->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hLow->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hLow->GetYaxis()->SetLabelFont(42);
  hLow->GetYaxis()->SetTitleOffset(1.7);
  hLow->GetYaxis()->CenterTitle(1);
  hLow->GetYaxis()->SetTickLength(0.02);
  hLow->GetYaxis()->SetTitleSize(0.03);
  hLow->GetYaxis()->SetLabelSize(hLow->GetXaxis()->GetLabelSize());
  hLow->GetYaxis()->SetTitleFont(42);
  
  hLow->GetXaxis()->SetNdivisions(10);
  hLow->GetYaxis()->SetNdivisions(10);

  // hLow->GetXaxis()->SetLimits(-1,3);
  // // hLow->GetYaxis()->SetRangeUser(1e-3,stoi(threshold)/10.);
  hLow->GetYaxis()->SetRangeUser(1e-3,maxY);

  hLow->SetTitle("");
  hLow->GetXaxis()->SetTitle("Ratio");

  
  hLow->SetLineColor(kCyan+2);
  hLow->SetMarkerColor(hLow->GetLineColor());
  hLow->SetLineWidth(hHigh->GetLineWidth());
  
  hLow->Draw();

  TString OutputFileLow = "plots/Energy_ratio_Low" + threshold + ".png";
  c2->SaveAs(OutputFileLow);


  
  TCanvas *c3 = new TCanvas("c3", "c3",0,72,1368,1368);

  // gPad->SetLogy();

  gStyle->SetOptStat(0);
 
  TGaxis::SetMaxDigits(5);

  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  hGamma->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  hGamma->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hGamma->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hGamma->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hGamma->GetXaxis()->SetLabelFont(42);
  hGamma->GetXaxis()->SetTitleOffset(1.2);
  hGamma->GetXaxis()->CenterTitle(1);
  hGamma->GetXaxis()->SetTickLength(0.02);
  hGamma->GetXaxis()->SetTitleSize(0.03);
  hGamma->GetXaxis()->SetLabelSize(hGamma->GetXaxis()->GetTitleSize()-0.01);
  hGamma->GetXaxis()->SetTitleFont(42);
  
  hGamma->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hGamma->GetYaxis()->SetLabelFont(42);
  hGamma->GetYaxis()->SetTitleOffset(1.7);
  hGamma->GetYaxis()->CenterTitle(1);
  hGamma->GetYaxis()->SetTickLength(0.02);
  hGamma->GetYaxis()->SetTitleSize(0.03);
  hGamma->GetYaxis()->SetLabelSize(hGamma->GetXaxis()->GetLabelSize());
  hGamma->GetYaxis()->SetTitleFont(42);
  
  hGamma->GetXaxis()->SetNdivisions(10);
  hGamma->GetYaxis()->SetNdivisions(10);

  // hGamma->GetXaxis()->SetLimits(-1,3);
  // // hGamma->GetYaxis()->SetRangeUser(1e-3,stoi(threshold)/10.);
  hGamma->GetYaxis()->SetRangeUser(1e-3,maxY);

  hGamma->SetTitle("");
  hGamma->GetXaxis()->SetTitle("Ratio");

  
  hGamma->SetLineColor(kOrange+7);
  hGamma->SetMarkerColor(hGamma->GetLineColor());
  hGamma->SetLineWidth(hHigh->GetLineWidth());
  hGamma->SetMarkerStyle(hHigh->GetMarkerStyle());
  
  hGamma->Draw();

  TString OutputFileGamma = "plots/Energy_ratio_Gamma" + threshold + ".png";
  c3->SaveAs(OutputFileGamma);

  // TLine l(-1, 1, 3, 1);
  // l.SetLineColor(kGray+2);
  // l.SetLineWidth(2);
  // l.SetLineStyle(7);
  // l.Draw("SAME");

  // TLegend *legend = new TLegend(0.604685, 0.733683, 0.891654, 0.892723); // linear scale
  // // legend->SetNColumns(2);;
  // legend->AddEntry(hHigh, "e+ 1.821 MeV", "lp");
  // legend->AddEntry(hLow, "e+ 0.547 MeV", "lp");
  // legend->AddEntry(hGamma, "#gamma  1.274 MeV", "lp");

  // legend->SetBorderSize(1);
  // legend->SetLineColor(gPad->GetFrameLineColor());
  // legend->SetFillColor(0);
  // legend->SetTextColor(gPad->GetFrameLineColor());
  // legend->SetTextSize(0.035);

  // legend->Draw();

  // TString OutputFile = "plots/Energy_ratio_" + threshold + ".png";
  // c1->SaveAs(OutputFile);

}
