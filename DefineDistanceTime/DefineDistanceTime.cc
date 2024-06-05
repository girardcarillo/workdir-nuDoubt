struct EventData {
  int event;
  int fN;
  double hitx, hity, hitz, time;
};

TH1F* AverageDistance(string path, string fileName, int eventNumber = 0) {

  int nbins = 20;
    
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

  // Kyra's files
  // Enable the branches we need
  tree->SetBranchStatus("fEvent", 1);
  tree->SetBranchStatus("fX", 1);
  tree->SetBranchStatus("fY", 1);
  tree->SetBranchStatus("Time", 1);
  
  // Set branch addresses for the tree
  tree->SetBranchAddress("fEvent", &eventData.event);
  tree->SetBranchAddress("fX", &eventData.hitx);
  tree->SetBranchAddress("fY", &eventData.hity);
  tree->SetBranchAddress("Time", &eventData.time);

  // Susie's files
  // // Enable the branches we need
  // tree->SetBranchStatus("Event_Number", 1);
  // tree->SetBranchStatus("Hit_X", 1);
  // tree->SetBranchStatus("Hit_Y", 1);
  // tree->SetBranchStatus("Hit_Z", 1);
  // tree->SetBranchStatus("Time_ns", 1);
  
  // // Set branch addresses for the tree
  // tree->SetBranchAddress("Event_Number", &eventData.event);
  // tree->SetBranchAddress("Hit_X", &eventData.hitx);
  // tree->SetBranchAddress("Hit_Y", &eventData.hity);
  // tree->SetBranchAddress("Hit_Z", &eventData.hitz);
  // tree->SetBranchAddress("Time_ns", &eventData.time);

  double fiberPitch = 10.; // mm

  // double particleGunX = 75; // mm
  // double particleGunY = 75; // mm
  // double particleGunZ = 0.; // mm

  double particleGunX = 6.2/10.; // mm
  double particleGunY = 4.2/10.; // mm
  double particleGunZ = 0.; // mm

  double minX = 0.;
  double maxX = 1000.;
  
  double minY = 0.;
  double maxY = 100.;
    
  int nbinsX = nbins;
  int nbinsY = nbins;

  // Create a 2D histograms
  TH2F *histogramXY = new TH2F("histogramXY", "", nbinsX, minX, maxX, nbinsY, minY, maxY);
  TH1F *avgDistanceHist = new TH1F("avgDistanceHist", "Average Distance vs Time;Time of optical hit on fiber (ns);Average Distance to vertex (mm)", nbinsX, minX, maxX);

  double X_value = 0.;
  double Y_value = 0.;
  double Z_value = 0.;
  double T_value = 0.;
  double distance_to_vertex = 0.;
  
  // Get the number of entries in the tree
  Long64_t nEntries = tree->GetEntries();

  int counter = 0;

  // Create vectors to store data for each x bin
  vector<vector<double>> distances(nbinsX);
  
  // Loop over entries and fill the histogram
  for (int i = 0; i < nEntries; i++) {
    tree->GetEntry(i);

    if (eventData.event == eventNumber) {

      X_value = eventData.hitx; 
      Y_value = eventData.hity; 
      Z_value = eventData.hitz; 
      // T_value = eventData.time; 
      T_value = eventData.time*1000.; // convert in ns for Kyra's files 

      distance_to_vertex = sqrt(pow(X_value - particleGunX, 2) + pow(Y_value - particleGunY, 2) + pow(Z_value - particleGunZ, 2));

      // Find which x bin this entry belongs to
      int x_bin = avgDistanceHist->GetXaxis()->FindBin(T_value);
      // int x_bin = (int)((T_value - minX) / ((maxX - minX) / nbinsX));
      // cout << x_bin << " " << T_value << endl;
      
	
      // Ensure x_bin is within valid range
      if (x_bin >= 0 && x_bin <= nbinsX) {
	// Store the distance in the corresponding x bin vector
	distances[x_bin-1].push_back(distance_to_vertex);
      } // else {
      // 	// Handle out-of-range x_bin value
      // 	cerr << "Warning: x_bin out of range: " << x_bin << endl;
      // }
	
      // histogramXY->Fill(T_value, distance_to_vertex);
      // histogram->SetBinContent(histogram->GetXaxis()->FindBin(T_value), histogram->GetBinContent(histogram->GetXaxis()->FindBin(T_value)) + distance_to_vertex);

    }

    if (eventData.event > eventNumber) break;

  }
  
  
  // histogram->Scale(1./counter);  
    
  // // Use TTree::Draw to fill the histogram
  // TString drawCommand = Form("(fY/10.-%f):(fX/10.-%f)", particleGunY, particleGunX);
  // TString cutCommand = Form("fEvent==%d", eventNumber);
  
  // // Draw the selected events into the histogram
  // tree->Draw(drawCommand + ">>histogramXY", cutCommand, "colz");
  
  // TCanvas *c1 = new TCanvas("c1", "c1",0,72,1368,1368);
  // histogram->Draw("HIST");
  
  // TCanvas *c2 = new TCanvas("c2", "c2",0,72,1368,1368);

  // histogramXY->SetLineColor(kCyan+3);
  // histogramXY->SetMarkerStyle(53);
  // histogramXY->SetLineWidth(2);
  // histogramXY->GetXaxis()->CenterTitle(true);
  // histogramXY->GetYaxis()->CenterTitle(true);
  // histogramXY->GetYaxis()->SetTitleOffset(1.3);

  // histogramXY->Draw();


  
  // Calculate the average distance for each x bin
  for (int ix = 1; ix <= nbinsX; ++ix) {
    const vector<double>& dist = distances[ix - 1];
    double sumY = 0.;

    for (double distance : dist) {
      sumY += distance;
    }

    double avgY = dist.empty() ? 0 : sumY / dist.size();
    avgDistanceHist->SetBinContent(ix, avgY);
  }
  
  // avgDistanceHist->Draw();

  return avgDistanceHist;
    
}

void DefineDistanceTime(string path, string fileName){

  int nevents = 50;
  
  TH1F *h = AverageDistance(path, fileName, 0);
  int nbinsX = h->GetXaxis()->GetNbins();
  double minX = h->GetXaxis()->GetXmin();
  double maxX = h->GetXaxis()->GetXmax();

  vector<TH1F*> histograms;
  for (int i = 0; i < nevents; i++) {
    cout << "Event " << i << endl;
    TH1F* hist = AverageDistance(path, fileName, i);
    histograms.push_back(hist);
  }

  // Create a histogram to hold the average of all histograms
  TH1F *avgHist = new TH1F("avgHist", "Average Distance vs Time over all events;Time of optical hit on fiber (ns);Average Distance to vertex (mm)", nbinsX, minX, maxX);

  // Average the histograms
  for (int bin = 1; bin <= avgHist->GetNbinsX(); ++bin) {
    double sum = 0;
    int count = 0;

    for (auto hist : histograms) {
      sum += hist->GetBinContent(bin);
      count++;
    }

    if (count > 0) {
      avgHist->SetBinContent(bin, sum / count);
    }
  }

  gStyle->SetOptStat(0);
  
  // Draw the final average histogram
  TCanvas *c2 = new TCanvas("c2", "c2",0,72,1368,1368);
  // gPad->SetLogy();

  avgHist->SetLineColor(kCyan+3);
  avgHist->SetLineWidth(2);
  avgHist->GetXaxis()->CenterTitle(true);
  avgHist->GetYaxis()->CenterTitle(true);
  avgHist->GetYaxis()->SetTitleOffset(1.3);

  avgHist->Draw();

  c2->SaveAs("DistanceTime_average.pdf");
  
  // Cleanup
  for (auto hist : histograms) {
    delete hist;
  }

}
