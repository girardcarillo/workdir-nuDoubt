#include "CountHit.cc"

void MyCanvasStyle(TH1F *hist){

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
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetXaxis()->SetTickLength(0.01);
  hist->GetXaxis()->SetTitleSize(0.04);
  hist->GetXaxis()->SetLabelSize(hist->GetXaxis()->GetTitleSize()-0.01);
  hist->GetXaxis()->SetTitleFont(42);
  
  hist->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetTitleOffset(1.7);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTickLength(0.01);
  hist->GetYaxis()->SetTitleSize(hist->GetXaxis()->GetTitleSize());
  hist->GetYaxis()->SetLabelSize(hist->GetXaxis()->GetLabelSize());
  hist->GetYaxis()->SetTitleFont(42);
  
  hist->GetXaxis()->SetNdivisions(7);
  hist->GetYaxis()->SetNdivisions(12);

}

// Function to remove outliers from a vector of doubles
vector<double> removeOutliers(const vector<int>& data, double threshold = 3.0) {
  // Calculate mean and standard deviation
  
  double mean = TMath::Mean(data.begin(), data.end());
  double standardDeviation = TMath::RMS(data.begin(), data.end());

  // Define the lower and upper bounds for outliers
  double lowerBound = mean - threshold * standardDeviation;
  double upperBound = mean + threshold * standardDeviation;

  // Remove outliers
  vector<double> cleanedData;
  for (double value : data) {
    if (value >= lowerBound && value <= upperBound) {
      cleanedData.push_back(value);
    }
  }

  return cleanedData;
}

void PlotNumberOfHits(string path, string fileName) {

  // path = "../DefineEventSize/Simus/";
  // fileName = "1.821positron75";
  // fileName = "0.547MeVpositron100";
  // fileName = "1.274MeVgamma100";
  
  string file = path + fileName + ".root";

  //Read the data from the simulation
  TFile* input = new TFile(file.c_str(), "read");
  TTree *tree = (TTree*)input->Get("Hits");

  vector<realHit> realHitsVector;
  vector<realHit> realHitsVectorDegraded;
  
  // This has to be updated because it's not good the number of events is hardcoded.
  // We should take as input the number of events in the root tree.
  int Number_of_events = 100;
  if (fileName == "1.821positron75") {
    Number_of_events = 75;
  }
  
  int Number_of_hit, Number_of_hit_degraded;

  vector<int> hits, hits_degraded;
  
  for (int i = 0; i < Number_of_events; ++i) {
    // for (int i = 0; i < 5; ++i) {
    cout << "Event number " << i << endl;
    
    Number_of_hit = CountHit(tree, i, 0);
    Number_of_hit_degraded = CountHit(tree, i, 1);

    cout << "Number of real hits " << Number_of_hit << " deteriorated " << Number_of_hit_degraded << endl;

    hits.push_back(Number_of_hit);
    hits_degraded.push_back(Number_of_hit_degraded);
  }

  // Remove outliers -> THose points have to be investigated
  vector<double> cleanedHits = removeOutliers(hits);
  vector<double> cleanedHits_degraded = removeOutliers(hits_degraded);

  double mean = TMath::Mean(cleanedHits.begin(), cleanedHits.end());
  double mean_degraded = TMath::Mean(cleanedHits_degraded.begin(), cleanedHits_degraded.end());
  
  double standardDeviation = TMath::RMS(cleanedHits.begin(), cleanedHits.end());
  double standardDeviation_degraded = TMath::RMS(cleanedHits_degraded.begin(), cleanedHits_degraded.end());

  int nBins = 20;
  TH1F *h = new TH1F("h", "", 20, mean-3*standardDeviation, mean+3*standardDeviation);
  TH1F *hdegraded = new TH1F("hdegraded", "", 20, mean_degraded-3*standardDeviation_degraded, mean_degraded+3*standardDeviation_degraded);

  // Fill the TH1 histogram with the values stored in the vector
  for (int i = 0; i < hits.size(); ++i) {
    h->Fill(hits[i]);
    hdegraded->Fill(hits_degraded[i]);
  }

  gStyle->SetOptStat("emr");

  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);

  c1->Divide(1,2);

  c1->cd(1);
  MyCanvasStyle(h);

  // double minY = min(h->GetMinimum(),hdegraded->GetMinimum());
  // double maxY = max(h->GetMaximum(),hdegraded->GetMaximum());
  
  // h->GetYaxis()->SetRangeUser(0, maxY+0.1*maxY);
  h->SetLineColor(kTeal+3);
  h->SetFillColor(kTeal+2);
  h->SetLineWidth(2);
  h->SetTitle("Perfect fibers and SiPMs");
  h->GetXaxis()->SetTitle("Recorded charge (a.u.)");
  h->Draw();

  c1->cd(2);
  MyCanvasStyle(hdegraded);

  hdegraded->SetLineColor(kOrange+9);
  hdegraded->SetFillColor(kOrange+8);
  hdegraded->SetLineWidth(h->GetLineWidth());
  hdegraded->SetTitle("Taking into account fibers and SiPMs efficiencies");
  hdegraded->GetXaxis()->SetTitle("Recorded charge (a.u.)");
  hdegraded->Draw();

  string OutputPdfFile = "plots/NumberOfPEPerMeV_" + fileName + ".pdf";
  c1->SaveAs(OutputPdfFile.c_str());

  string OutputRootFile = "histograms/NumberOfPEPerMeV_" + fileName + ".root";
  h->SaveAs(OutputRootFile.c_str());
  string OutputRootFile_degraded = "histograms/NumberOfPEPerMeV_" + fileName + "_degraded.root";
  hdegraded->SaveAs(OutputRootFile_degraded.c_str());

}
