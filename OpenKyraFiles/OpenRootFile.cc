
struct EventData {
  int event;
  int fN;
  double hitx, hity, hitz;
};

void OpenRootFile(string path, string fileName, int eventNumber = 0) {
  
  string file = path + fileName + ".root";
  const char * cfile = file.c_str();

  // Open the input file
  TFile *inputFile = new TFile(cfile, "read");

  // Get the tree from the file
  TTree *tree = (TTree*)inputFile->Get("Hits");

  // Get the number of entries in the tree
  // Ensure that the tree is not empty
  int entries = tree ? tree->GetEntries() : 0;
  
  EventData eventData;

  // Set the branch status to 0 for all branches
  tree->SetBranchStatus("*", 0);

  // Enable the branches we need
  tree->SetBranchStatus("fEvent", 1);
  tree->SetBranchStatus("fX", 1);
  tree->SetBranchStatus("fY", 1);
  
  // Set branch addresses for the tree
  tree->SetBranchAddress("fEvent", &eventData.event);
  tree->SetBranchAddress("fX", &eventData.hitx);
  tree->SetBranchAddress("fY", &eventData.hity);

  double particleGunX = 6.2/10.; // mm
  double particleGunY = 4.2/10.; // mm
  double particleGunZ = 0.; // mm

  double fiberPitch = 10.; // mm

  double minX = -70.;
  double maxX = 70.;
  
  double minY = -70.;
  double maxY = 70.;
    
  double minZ = -70.;
  double maxZ = 70.;

  int nbinsX = (maxX - minX) / fiberPitch * 10.;
  int nbinsY = (maxY - minY) / fiberPitch * 10.;

  // Create a 2D histograms
  TH2F *histogramXY = new TH2F("histogramXY", "", nbinsX, minX, maxX, nbinsY, minY, maxY);

  // double X_value = 0.;
  // double Y_value = 0.;
  // double Z_value = 0.;

  // // Get the number of entries in the tree
  // Long64_t nEntries = tree->GetEntries();
  
  // // Loop over entries and fill the histogram
  // for (int i = 0; i < nEntries; i++) {
  //   tree->GetEntry(i);

  //   if (eventData.event == eventNumber) {

  //     X_value = eventData.hitx/10.-particleGunX; // conversion in cm - re-centering the particle gun
  //     Y_value = eventData.hity/10.-particleGunY; // conversion in cm - re-centering the particle gun
  //     Z_value = eventData.hitz/10.-particleGunZ; // conversion in cm - re-centering the particle gun

  //     histogramXY->Fill(X_value, Y_value);

  //   }

  //   if (eventData.event > eventNumber) break;

  // }

  // Use TTree::Draw to fill the histogram
  TString drawCommand = Form("(fY/10.-%f):(fX/10.-%f)", particleGunY, particleGunX);
  TString cutCommand = Form("fEvent==%d", eventNumber);
  
  // Draw the selected events into the histogram
  tree->Draw(drawCommand + ">>histogramXY", cutCommand, "colz");
    
  gStyle->SetOptStat(0);
  
  histogramXY->Draw("colz");
  
  // // Clean up
  // inputFile->Close();
  // delete inputFile;

}
