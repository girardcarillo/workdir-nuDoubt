#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <map>
#include <cmath>
#include <sstream>
#include <TNtuple.h>
#include <TObject.h>
#include <limits>

//Define the strcture to represent an optical hit in the fibre
struct Hit {
  double x;
  double y;
  double z;
  double time;

  //less than operator (needed in case of comparing time)
  bool operator<(const Hit& other) const{
    return time < other.time;
  }
};

//Define the structure to represent a real hit: a collection of hits that happen in the same fiber in a given time interval
struct realHit {
  double x;
  double y;
  double avgZ;
  double avgTime;
  int numHits;
  int timeInterval;

  // Equality operator to compare two real hit structures
  bool operator==(const realHit& other) const {
    return x == other.x && y == other.y && avgZ == other.avgZ && avgTime == other.avgTime && numHits == other.numHits && timeInterval == other.timeInterval;
  }

};

vector<realHit> CreateRealHits(const char* fileName, int targetEventNumber = 0, bool Include_FiberSiPM_efficiency = 1){

  //Read the data from the simulation
  TFile* input = new TFile(fileName, "read");
  TTree *tree = (TTree*)input->Get("Hits");

  //Define variables for the branches
  int event, fN;
  double fx,fy,fz, hitx, hity, hitz, time_hit;

  //read tree branches
  tree->SetBranchAddress("Event_Number", &event);
  tree->SetBranchAddress("fibreX", &fx);
  tree->SetBranchAddress("fibreY", &fy);
  tree->SetBranchAddress("fibreZ", &fz);
  tree->SetBranchAddress("fibreNumber", &fN);
  tree->SetBranchAddress("Hit_X", &hitx);
  tree->SetBranchAddress("Hit_Y", &hity);
  tree->SetBranchAddress("Hit_Z", &hitz);
  tree->SetBranchAddress("Time_ns", &time_hit);


  ////////////// First step: get the optical hits /////////////////////
  //Get the number of entries, and define the target number event
  int entries = tree->GetEntries();;
  int numberOfHits = 0;  //counter to keep track of the hits used to check that the hits are getting group rigth (can be omitted)

  //First group hits with the same x,y (hits that happen in a given fibre)
  map<pair<double, double>, map< int, vector<Hit>>> hitsMap;

  //loop over all entries that are within the event and fill the optical hits structure
  for (int i=0; i<entries; i++) {
    tree->GetEntry(i);
    if (event == targetEventNumber){
      Hit currentHit;
      currentHit.x = fx;
      currentHit.y = fy;
      currentHit.z = hitz;
      currentHit.time = time_hit;
      numberOfHits++;

      //create a pair of x and y as the key of the map
      pair<double, double> xyPair = {currentHit.x, currentHit.y};
      
      //define a time interval to group hits within the same fibre (in this case 10 ns)
      int timeInterval = static_cast<int>(round(currentHit.time/10.0))*10;
      
      //Add the hit to the corresponding group in the map
      hitsMap[xyPair][timeInterval].push_back(currentHit);

    }
  }

  //// Second step: Get the real hits //////////////////
  //Define a vector to store the real hits
  vector<realHit> realHitsVector;
  // start by accesing the hits with the same x,y and  the time interval
  for (const auto& entry : hitsMap){
    const auto& xyPair = entry.first;
    const auto& timeIntervals = entry.second;

    // then access the hits that are in the time interval
    for (const auto& timeEntry : timeIntervals){
      const auto& hits = timeEntry.second;
      const int timeInterval = timeEntry.first;

      //calculate average z, time and number of hits
      double sumZ = 0.0;
      double sumTime = 0.0;
      // loop through the hits
      for (const auto& hit : hits){
	sumZ += hit.z;
	sumTime += hit.time;
      }
      // int numHits = hits.size(); // if we want to account (artificially) for the efficiency of fibers+SiPMs, we should degrade this number. Final number: 500 PE/MeV should be collected
      int numHits = hits.size();
      if (Include_FiberSiPM_efficiency) numHits = numHits - 0.1*hits.size(); // if we want to account (artificially) for the efficiency of fibers+SiPMs, we should degrade this number. Final number: 500 PE/MeV should be collected
      
      double avgZ = (numHits > 0) ? sumZ/numHits : 0.0;
      double avgTime = (numHits > 0) ? sumTime/numHits : 0.0;

      //define an element (real hit) of the vector and fill the real hit structure.

      realHit fH;
      fH.x = xyPair.first;
      fH.y = xyPair.second;
      fH.avgZ = avgZ;
      fH.avgTime = avgTime;
      fH.numHits = numHits;
      fH.timeInterval = timeInterval;
      realHitsVector.push_back(fH);

    }

  }

  return realHitsVector;
  
  // //sort based on decreasing numHits
  // sort(realHitsVector.begin(), realHitsVector.end(), [](const realHit& a, const realHit& b){
  //   return a.numHits > b.numHits;
  // });

}
