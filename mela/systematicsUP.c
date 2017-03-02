#include <RooDataSet.h>


void systematicsUP() {

  TFile *f1 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_ewk/ZZ4lAnalysis.root");
  TTree *sig = (TTree*)f1->Get("ZZTree/candTree");
  TH1F *hs = (TH1F*)f1->Get("ZZTree/Counters");


  TFile *f2 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_qcd/ZZ4lAnalysis.root");
// ZZjj_qcd xsec = 9.335E-03 pb
  TTree *bkg = (TTree*)f2->Get("ZZTree/candTree");
  TH1F *h0 = (TH1F*)f2->Get("ZZTree/Counters");	

  TFile *f5 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo2e2mu_Contin_MCFM701/ZZ4lAnalysis.root");
// ggTo2e2mu xsec = 0.0031942 pb
  TTree *bkg1 = (TTree*)f5->Get("ZZTree/candTree");
  TH1F *h5 = (TH1F*)f5->Get("ZZTree/Counters");

  TFile *f6 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo4e_Contin_MCFM701/ZZ4lAnalysis.root");
// ggTo4e  xsec = 0.00158549 pb
  TTree *bkg2 = (TTree*)f6 ->Get("ZZTree/candTree");
  TH1F *h6 = (TH1F*)f6->Get("ZZTree/Counters");


  TFile *f7 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo4mu_Contin_MCFM701/ZZ4lAnalysis.root");
// ggTo4mu xsec = 0.00158549 pb
  TTree *bkg3 = (TTree*)f7 ->Get("ZZTree/candTree");
  TH1F *h7 = (TH1F*)f7->Get("ZZTree/Counters");




  static const int ncuts = 100; //I changed this wrt the previous version 
  float cuts[ncuts];

  float NgenSig = hs->GetBinContent(1);
  cout << "NgenSig = " << NgenSig << endl;  

  float NgenBKG = h0->GetBinContent(1);
  cout << "NgenBKG = " << NgenBKG << endl;
  
  float NgenBkg1 = h5->GetBinContent(1);
  cout << "NgenBkg 2e2mu = " << NgenBkg1 << endl;  

  float NgenBkg2 = h6->GetBinContent(1);
  cout << "NgenBkg 4e = " << NgenBkg2 << endl;

  float NgenBkg3 = h7->GetBinContent(1);
  cout << "NgenBkg 4mu = " << NgenBkg3 << endl;



  //float norms = 30.08;
  //float normsss = 15.05;
  //float normb = 45216.;
  //float ssb[ncuts];
   float Lumi=36.8E03; //Luminosity in pb-1 	
   
   float normSig= Lumi*0.4404E-03/NgenSig;

   float normbkg= Lumi*9.335E-03/NgenBKG;
   float normBkg1= Lumi*0.0031942/NgenBkg1;
   float normBkg2 = Lumi*0.00158549/NgenBkg2;
   float normBkg3 = Lumi*0.00158549/NgenBkg3;


  TH1F *h1 = new TH1F("h1","h1",100,-1000,1000);
  char cutting[400];
  char cuttingUp[400];
 

// First (no loop) find the denominators (effsig=X , effbkg=Y)  OBS Here there is a cut on mjj is 100 (fiducial)

    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100.  && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal)> 0.66");
    sprintf(cuttingUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66");   

    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting); 
    float effsig0 = h1->Integral()*normSig;    

    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp); 
    float effsigUp = h1->Integral()*normSig;
	
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg0 = h1->Integral()*normbkg;

    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    float effbkgUp = h1->Integral()*normbkg;


    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg1;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    effbkgUp =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg2;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    effbkgUp =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg3;	

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    effbkgUp =+ h1->Integral()*normBkg3;
  

    float DeltaS=(effsigUp - effsig0)/effsig0;
    float DeltaB=(effbkgUp - effbkg0)/effbkg0;
	
    cout << "Delta Sig = " << DeltaS << endl;
    cout << "Delta Bkg = " << DeltaB << endl;   



}
