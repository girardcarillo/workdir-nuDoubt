void CalculateCalibrationConstant(string path, string fileName, bool is_degraded = 1) {
  
  // string path = "histograms/";
  // string fileName = "0.547MeVpositron100";

  string file = path + "NumberOfPEPerMeV_" + fileName;
  if (is_degraded) file += "_degraded";
  file += ".root";
  
  const char * cfile = file.c_str();
  TFile *f = new TFile(cfile);

  string hName = "h";
  if (is_degraded) hName += "degraded";
  TH1F* h =(TH1F*)f->Get(hName.c_str());

  h->Fit("gaus");
  h->Draw();

}
