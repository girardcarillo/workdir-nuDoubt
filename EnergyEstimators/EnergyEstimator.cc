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
#include "../Visualization/CreateRealHits.cc"

// void PlotEnergyDistance(const char* fileName, int eventNumber) {

void EnergyEstimator(string path, string fileName, int eventNumber = 0, string energy_estimator = "1", int threshold = 500) {
  // Here the definition of "threshold" is important, because it will not have the same meaning for different energy estimators.
  // First energy estimator: "threshold" refers to the radius (or distance to particle creation vertex) below which we integrate the deposited energy.
  // Second energy estimator: "threshold" refers to the number of hits of highest energy we take into account for the calculation of the energy estimator

  if (energy_estimator == "1") 
    cout << "Executing macro with first energy estimator with threshold = " << threshold << "mm file " << fileName << " event " << eventNumber << endl;
  else if (energy_estimator == "2") 
    cout << "Executing macro with second energy estimator with N = " << threshold << " file " << fileName << " event " << eventNumber << endl;
  else if (energy_estimator == "3") 
    cout << "Executing macro with third energy estimator with N = " << threshold << " file " << fileName << " event " << eventNumber << endl;
  else {
    cout << "Wrong energy estimator chosen" << endl;
    return 6;
  }
  
  //Define a vector to store the real hits
  vector<realHit> realHitsVector;

  string file = path + fileName + ".root";
  const char * cfile = file.c_str();
  realHitsVector = CreateRealHits(cfile,eventNumber);

  double distance_to_vertex;
  double E_true = 0.;
  double E_reco = 0.;
  
  double particleGunX = 75.; // mm
  double particleGunY = 75.; // mm
  double particleGunZ = 0.; // mm

  double Light_Yield = 9000.; // PE/MeV
  
  ofstream Energy_file;
  Energy_file.open("txtFiles/threshold_" + to_string(threshold) + "mm/EnergyEstimator_" + fileName + ".txt", ios::app);

  vector<double> energy_deposited; // Vector to store the energies of hits

  // First energy estimator
  if (energy_estimator == "1") { // First energy estimator: Ereco = take all hits below given threshold
    for (const auto& hit : realHitsVector) {

      distance_to_vertex = sqrt(pow((hit.x-particleGunX),2)+pow((hit.y-particleGunY),2)+pow((hit.avgZ-particleGunZ),2)); // mm
    
      E_true += hit.numHits;

      // energy estimator
      // Calculate the sum of the hit energies contained in a given radius around the particle vertex
      if(distance_to_vertex <= threshold)
	E_reco += hit.numHits;

    }

  }

  // Second energy estimator
  if (energy_estimator == "2") {
    
    for (const auto& hit : realHitsVector) {
      E_true += hit.numHits;
      energy_deposited.push_back(hit.numHits); // Store the energy of each hit
    }

    // Sort the energies in descending order
    sort(energy_deposited.begin(), energy_deposited.end(), std::greater<double>());

    // energy estimator
    // Calculate the sum of the top N values
    for (int i = 0; i < threshold && i < energy_deposited.size(); ++i) {
      E_reco += energy_deposited[i];
    }
  
    // // Print the sum of the top N energies
    // cout << "Sum of top " << threshold << " energies: " << E_reco << endl;
  
  }

  // // Third energy estimator
  // if (energy_estimator == "3") {
  //   double center_of_mass;
        
  //   for (const auto& hit : realHitsVector) {
  //     E_true += hit.numHits;
  //     energy_deposited.push_back(hit.numHits); // Store the energy of each hit
  //   }

  //   // Sort the energies in descending order
  //   sort(energy_deposited.begin(), energy_deposited.end(), std::greater<double>());

  //   // energy estimator
  //   // Calculate the sum of the top N values
  //   for (int i = 0; i < threshold && i < energy_deposited.size(); ++i) {
  //     E_reco += energy_deposited[i];
  //   }
  
  //   for (const auto& hit : realHitsVector) {

  //     distance_to_vertex = sqrt(pow((hit.x-particleGunX),2)+pow((hit.y-particleGunY),2)+pow((hit.avgZ-particleGunZ),2)); // mm
    
  //     E_true += hit.numHits;

  //     // energy estimator
  //     // Calculate the sum of the hit energies contained in a given radius around the particle vertex
  //     if(distance_to_vertex <= threshold)
  // 	E_reco += hit.numHits;

  //   }

  // }

  Energy_file << E_true << " " << E_reco << endl;
  Energy_file.close();
  
}
