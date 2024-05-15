// root -l -b -q 'VisualizeHits.cc("../DefineEventSize/Simus/1.821positron75.root")'

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
#include "CreateRealHits.cc"

// void PlotEnergyDistance(const char* fileName, int eventNumber) {

void PlotEnergyDistance(string path, string fileName, int eventNumber = 0) {

  //Define a vector to store the real hits
  vector<realHit> realHitsVector;

  string file = path + fileName + ".root";
  const char * cfile = file.c_str();
  realHitsVector = CreateRealHits(cfile,eventNumber);

  double max_energy = 4000.;
  double max_distance = 2000.;

  int nbins_energy = 40;
  int nbins_distance = 35;
  
  TH1F *h1_distance_energy = new TH1F("h1_distance_energy", "", nbins_distance, 0., max_distance);
  // TH1D *h1_distance_energyCum = new TH1D("h1_distance_energyCum", "", nbins_distance, 0., max_distance);

  double distance_to_vertex;
  double distance_to_vertex_XY;
  double distance_to_vertex_XZ;
  double energy_deposited;
  
  double fiberPitch = 15.; // mm
  double particleGunX = 75.; // mm
  double particleGunY = 75.; // mm
  double particleGunZ = 0.; // mm

  double Light_Yield = 9000.; // PE/MeV

  double test_energy_first = 0;
  double test_energy_rest = 0;

  int threshold = 200;

  double energy_deposited_currentBin = 0.;
  double energy_deposited_previousBin = 0.;

  ofstream Energy_file;
  Energy_file.open("txtFiles/HighestEnergy_distance_" + fileName + ".txt", ios::app);

  double highestEnergy = 0.;
  double distance_highestEnergy = 0.;
  
  for (const auto& hit : realHitsVector) {

    distance_to_vertex = sqrt(pow((hit.x-particleGunX),2)+pow((hit.y-particleGunY),2)+pow((hit.avgZ-particleGunZ),2)); // mm
    distance_to_vertex_XY = sqrt(pow((hit.x-particleGunX),2)+pow((hit.y-particleGunY),2)); // mm
    distance_to_vertex_XZ = sqrt(pow((hit.x-particleGunX),2)+pow((hit.avgZ-particleGunZ),2)); // mm
    energy_deposited = hit.numHits; 

    if (energy_deposited > highestEnergy){
      highestEnergy = energy_deposited;
      distance_highestEnergy = distance_to_vertex;
    }

    energy_deposited_currentBin = h1_distance_energy->GetBinContent((int)((nbins_distance/max_distance)*distance_to_vertex)+1)+energy_deposited;
    energy_deposited_previousBin = h1_distance_energy->GetBinContent((int)((nbins_distance/max_distance)*distance_to_vertex));
    
    // h1_distance_energy->SetBinContent((int)((nbins_distance/max_distance)*distance_to_vertex)+1, energy_deposited_currentBin);
    h1_distance_energy->SetBinContent(h1_distance_energy->GetXaxis()->FindBin(distance_to_vertex), energy_deposited_currentBin);
   
    if (distance_to_vertex <= threshold) {
      test_energy_first+=energy_deposited;
    }
    else {
      test_energy_rest+=energy_deposited;
    }
  }

  TH1* h1_distance_energyCum = h1_distance_energy->GetCumulative();

  // int whichFile;
  // if (fileName == "1.821positron75")
  //   whichFile = 0;
  // else if (fileName == "0.547MeVpositron100")
  //   whichFile = 1;
  // else if (fileName == "1.274MeVgamma100")
  //   whichFile = 2;
  
  Energy_file << distance_highestEnergy << " " << highestEnergy << endl;
  Energy_file.close();
  
  TString OutputRootFileEnergy = "histograms/" + fileName + "/Distance_energy_" + fileName + "_event" + to_string(eventNumber) + ".root";
  h1_distance_energy->SaveAs(OutputRootFileEnergy);
  
  TString OutputRootFileCumulative = "histograms/" + fileName + "/Distance_energyCum_" + fileName + "_event" + to_string(eventNumber) + ".root";
  h1_distance_energyCum->SaveAs(OutputRootFileCumulative);

}
