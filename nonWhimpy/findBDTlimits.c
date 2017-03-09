#include <RooDataSet.h>


void findBDTlimits() {

  TFile *f1 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_ewk/ZZ4lAnalysis.root");
// ZZjj_ewk xsec= 0.4404E-03
  TTree *sig = (TTree*)f1->Get("ZZTree/candTree");

  TH1F *h1 = new TH1F("h1","h1",200,-0.65,0.9);

 sig->Draw("ZZjj_MVA >> h1","nCleanedJetsPt30 > 1 && DiJetMass > 100. && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120."); 


}
