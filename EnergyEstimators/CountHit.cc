// Macro to count the total number of optical hits for a simulated event 
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

// int CountHit(string path, string fileName, int eventNumber = 0, bool is_degraded = 1) {
int CountHit(TTree *tree, int eventNumber = 0, bool is_degraded = 1) {

  //Define a vector to store the real hits
  vector<realHit> realHitsVector;
  // vector<realHit> realHitsVector_degraded;

  realHitsVector = CreateRealHits(tree, eventNumber, is_degraded);
  
  double TotalPEPerMeV = 0.;
  for (const auto& hit : realHitsVector) {
    TotalPEPerMeV += hit.numHits;
  }

  
  // cout << "Number of real hits " << realHitsVector.size() << endl;
  // cout << "Number of optical hits " << TotalPEPerMeV << endl;

  return TotalPEPerMeV;
}
