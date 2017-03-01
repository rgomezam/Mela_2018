#include <RooDataSet.h>


void getNGen() {

//  TFile *f2 = 
//  TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ZZTo4l/ZZ4lAnalysis.root");
// ZZTo4l xsec = 1.256 pb
//  TTree *bkg = (TTree*)f2->Get("ZZTree/candTree");
  TFile *f = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo2e2muJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
// VBFTo2e2muJJ_0PMH125Contin_phantom128 xsec = 8.375E-04 pb
//  TTree *sig = (TTree*)f->Get("ZZTree/candTree");
//  TFile *f3 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo4eJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
//VBFTo4eJJ_0PMH125Contin_phantom128 xsec= 4.180E-04 pb  
//  TTree *sigee = (TTree*)f3->Get("ZZTree/candTree");
//  TFile *f4 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo4muJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
//VBFTo4muJJ_0PMH125Contin_phantom128 xsec= 4.180E-04 pb
//  TTree *sigmm = (TTree*)f4->Get("ZZTree/candTree");

//.ls 	
//TH1F *h1 = new TH1F("h1","h1",100,0.,1.1);
TH1F *h1 = (TH1F*)f->Get("ZZTree/Counters");
float NgenBKG; 
NgenBKG = h1->GetBinContent(1);
cout << "NGENBKG = " << NgenBKG << endl;

//sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. ");
    
//bkg->Draw("nCounters >> h1"); 
   
//sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
/*    effsig0 += h1->Integral()*normsss/11200.;
    
    
sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig0 += h1->Integral()*normsss/10400.;
    
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg0 = h1->Integral()*normb/5957960.;
  
    Y = effsig0;
    X = effbkg0;*/



}
