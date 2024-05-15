// .L /uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/PlotEtrueEreco.cc
// PlotEtrueEreco("/uni-mainz.de/homes/cgirardc/Workdir/nuDoubt/EnergyEstimators/txtFiles","0.547MeVpositron100", "2", 200);

#include <iostream>
#include <fstream>
#include <sstream>
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"

// Function to find the minimum and maximum values in the text file
void findMinMax(const char* filename, double& minX, double& maxX, double& minY, double& maxY) {
    // Open the text file
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Initialize min/max values
    minX = numeric_limits<double>::max();
    maxX = numeric_limits<double>::lowest();
    minY = numeric_limits<double>::max();
    maxY = numeric_limits<double>::lowest();

    // Read data from the text file and find min/max values
    double x, y;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        if (!(iss >> x >> y)) {
            cerr << "Error reading line: " << line << endl;
            continue;
        }
        // Update min/max values
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    // Close the text file
    infile.close();
}

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

void MyCanvasStyle2D(TH2F *hist){

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
  
  
  hist->GetZaxis()->SetTitleColor(gPad->GetFrameLineColor());
  hist->GetZaxis()->SetLabelColor(gPad->GetFrameLineColor());
  hist->GetZaxis()->SetAxisColor(gPad->GetFrameLineColor());
  hist->GetZaxis()->SetLabelFont(42);
  hist->GetZaxis()->SetTitleOffset(1.4);
  hist->GetZaxis()->CenterTitle(1);
  hist->GetZaxis()->SetTickLength(0.01);
  hist->GetZaxis()->SetTitleSize(0.019);
  hist->GetZaxis()->SetLabelSize(0.015);
  hist->GetZaxis()->SetTitleFont(42);
  
}

void plotDataFromTextFile(string path, string file, string energy_estimator, int threshold) {

  string file_energy_estimator;
  if (energy_estimator == "1") file_energy_estimator = "FirstEnergyEstimator";
  else if (energy_estimator == "2") file_energy_estimator = "SecondEnergyEstimator";
  else {
    cout << "Wrong energy estimator chosen" << endl;
    return;
  }
    
  string inputFile = path + "/" + file_energy_estimator + "/threshold_" + to_string(threshold) + "mm/EnergyEstimator_" + file + ".txt";
  const char * filename = inputFile.c_str();

  // Open the text file
  ifstream infile(filename);
  if (!infile.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return;
  }

  double minX, maxX, minY, maxY;
  // Find min/max values
  findMinMax(filename, minX, maxX, minY, maxY);
  
  double minX1D = -0.6;
  int nBins = 20;
  if (energy_estimator == "1") {
    // nBins = 10;
    minX1D = -1;
  }
  
  // Create a TH2 histogram with appropriate range
  TH2F *hist = new TH2F("hist", file.c_str(), nBins, minX, maxX, nBins, minY, maxY);
  // TH1F *hist1D = new TH1F("hist1D", file.c_str(), nBins, -1, 0);
  TH1F *hist1D = new TH1F("hist1D", file.c_str(), nBins, minX1D, 0);

  hist->GetXaxis()->SetTitle("Etrue");
  hist->GetYaxis()->SetTitle("Ereco");
  
  // hist1D->GetXaxis()->SetTitle("Ereco/Etrue");
  // hist1D->GetYaxis()->SetTitle("# counts");

  // Read data from the text file and fill the histogram
  double Etrue, Ereco;
  string line;
  while (getline(infile, line)) {
    istringstream iss(line);
    if (!(iss >> Etrue >> Ereco)) {
      cerr << "Error reading line: " << line << endl;
      continue;
    }
    hist->Fill(Etrue, Ereco);
    hist1D->Fill((Ereco-Etrue)/Etrue);
  }

  // Close the text file
  infile.close();

  cout << "Warning! Manual normalization to the number of simulated events!" << endl;
  int scaleFactor = 0.;
  if (file == "1.821positron75") scaleFactor = 75.;
  else if (file == "0.547MeVpositron100") scaleFactor = 100.;
  else if (file == "1.274MeVgamma100") scaleFactor = 100.;
  else cout << "Problem with scaling factor: no corresponding file name!" << endl;
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);

  MyCanvasStyle2D(hist);
  
  hist->Scale(1./scaleFactor);

  // hist->Draw("surf2z");
  hist->Draw("colz");

  TCanvas *c2 = new TCanvas("c2", "c2",0,72,1368,1368);

  // MyCanvasStyle1D(hist1D);

  hist1D->Scale(1./scaleFactor);
    
  hist1D->Draw("HIST");

  string OutputPdfFile = "plots/Etrue_Ereco_" + file_energy_estimator + "_threshold_" + to_string(threshold) + "_" + file + ".pdf";
  const char * cOutputPdfFile = OutputPdfFile.c_str();
  c1->SaveAs(cOutputPdfFile);

  // string OutputPdfFile1D = "plots/Ratio_Etrue_Ereco_threshold_" + to_string(threshold) + "mm_" + file + ".pdf";
  // const char * cOutputPdfFile1D = OutputPdfFile1D.c_str();
  // c2->SaveAs(cOutputPdfFile1D);

  string OutputRootFile1D = "histograms/Ratio_Etrue_Ereco_" + file_energy_estimator + "_threshold_" + to_string(threshold) + "_" + file + ".root";
  const char * cOutputRootFile1D = OutputRootFile1D.c_str();
  hist1D->SaveAs(cOutputRootFile1D);

}

void PlotEtrueEreco(string path, string fileName, string energy_estimator, int threshold) {

  gStyle->SetOptStat(0);

  plotDataFromTextFile(path, fileName, energy_estimator, threshold);

}
