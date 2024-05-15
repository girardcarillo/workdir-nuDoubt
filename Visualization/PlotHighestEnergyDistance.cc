void PlotHighestEnergyDistance(){

  string filePositronLow = "txtFiles/HighestEnergy_distance_1.821positron75.txt";
  const char *cfilePositronLow = filePositronLow.c_str();

  string filePositronHigh = "txtFiles/HighestEnergy_distance_0.547MeVpositron100.txt";
  const char *cfilePositronHigh = filePositronHigh.c_str();

  string fileGamma = "txtFiles/HighestEnergy_distance_1.274MeVgamma100.txt";
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

  // cout << "Number of points in grPositronHigh: " << nPointsPositronHigh << endl;
  // cout << "Number of points in grPositronHigh: " << nPointsPositronLow << endl;
  // cout << "Number of points in grPositronHigh: " << nPointsGamma << endl;
  
  // Define histogram bin edges
  const int nBins = 10;
  double xmin = 0.;
  double xmax = 1250.;
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
    // hHigh->SetBinContent(hHigh->GetXaxis()->FindBin(xPositronHigh[i]), yPositronHigh[i]);
    hHigh->Fill(xPositronHigh[i]);
  }

  // Fill the histogram
  for (int i = 0; i < nPointsPositronLow; ++i) {
    // hLow->Fill(yPositronLow[i]);
    // hLow->SetBinContent(hLow->GetXaxis()->FindBin(xPositronLow[i]), yPositronLow[i]);
    hLow->Fill(xPositronLow[i]);
  }

  // Fill the histogram
  for (int i = 0; i < nPointsGamma; ++i) {
    // hGamma->Fill(yGamma[i]);
    // hGamma->SetBinContent(hGamma->GetXaxis()->FindBin(xGamma[i]), yGamma[i]);
    hGamma->Fill(xGamma[i]);
  }

  cout << "Warning! Manual normalization to the number of simulated events!" << endl;
  int scaleFactorHigh = 75;
  int scaleFactorLow = 100;
  int scaleFactorGamma = 100;

  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);

  hHigh->Scale(1./scaleFactorHigh);
  hLow->Scale(1./scaleFactorLow);
  hGamma->Scale(1./scaleFactorGamma);

  gPad->SetLogy();

  gStyle->SetOptStat(0);
 
  TGaxis::SetMaxDigits(5);

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
  hHigh->GetYaxis()->SetTitleOffset(1.2);
  hHigh->GetYaxis()->CenterTitle(1);
  hHigh->GetYaxis()->SetTickLength(0.02);
  hHigh->GetYaxis()->SetTitleSize(0.03);
  hHigh->GetYaxis()->SetLabelSize(hHigh->GetXaxis()->GetLabelSize());
  hHigh->GetYaxis()->SetTitleFont(42);
  
  hHigh->GetXaxis()->SetNdivisions(10);
  hHigh->GetYaxis()->SetNdivisions(10);

  // hHigh->GetXaxis()->SetLimits(-1,3);
  hHigh->GetYaxis()->SetRangeUser(0.001,1.1);

  hHigh->SetTitle("");
  hHigh->GetXaxis()->SetTitle("Distance to vertex (mm)");
  hHigh->GetYaxis()->SetTitle("Highest energy deposition in fiber (a.u.)");

  hHigh->SetLineColor(kViolet-1);
  hHigh->SetFillColorAlpha(hHigh->GetLineColor(),0.1);
  hHigh->SetMarkerColor(hHigh->GetLineColor());
  hHigh->SetLineWidth(2);
  
  hHigh->Draw("HIST");

  hLow->SetLineColor(46);
  hLow->SetFillColorAlpha(hLow->GetLineColor(),0.1);
  hLow->SetMarkerColor(hLow->GetLineColor());
  hLow->SetLineWidth(hHigh->GetLineWidth());
  hLow->Draw("SAMEHIST");
  
  hGamma->SetLineColor(30);
  hGamma->SetFillColorAlpha(hGamma->GetLineColor(),0.1);
  hGamma->SetMarkerColor(hLow->GetLineColor());
  hGamma->SetLineWidth(hHigh->GetLineWidth());
  hGamma->Draw("SAMEHIST");

  TLegend *legend = new TLegend(0.604685, 0.733683, 0.891654, 0.892723); // linear scale
  // legend->SetNColumns(2);;
  legend->AddEntry(hHigh, "e+ 1.821 MeV", "f");
  legend->AddEntry(hLow, "e+ 0.547 MeV", "f");
  legend->AddEntry(hGamma, "#gamma  1.274 MeV", "f");

  legend->SetBorderSize(1);
  legend->SetLineColor(gPad->GetFrameLineColor());
  legend->SetFillColor(0);
  legend->SetTextColor(gPad->GetFrameLineColor());
  legend->SetTextSize(0.035);

  legend->Draw();

  TString OutputFileHigh = "plots/HighestEnergy_distance.pdf";
  c1->SaveAs(OutputFileHigh);

}
