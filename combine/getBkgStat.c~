#include <RooDataSet.h>

// This ROOT macro gets you the MC error for each channel

void getBkgStat() {

  TFile *f1 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_ewk/ZZ4lAnalysis.root");
  TTree *sig = (TTree*)f1->Get("ZZTree/candTree");
  TH1F *hs = (TH1F*)f1->Get("ZZTree/Counters");


  TFile *f2 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_qcd/ZZ4lAnalysis.root");
// ZZjj_qcd xsec = 9.335E-03 pb
  TTree *bkg = (TTree*)f2->Get("ZZTree/candTree");
  TH1F *h0 = (TH1F*)f2->Get("ZZTree/Counters");	

  TFile *f5 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo2e2mu_Contin_MCFM701/ZZ4lAnalysis.root");
//  ggTo2e2mu xsec = 0.0031942 pb
  TTree *bkg1 = (TTree*)f5->Get("ZZTree/candTree");
  TH1F *h5 = (TH1F*)f5->Get("ZZTree/Counters");

  TFile *f6 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo4e_Contin_MCFM701/ZZ4lAnalysis.root");
//  ggTo4e  xsec = 0.00158549 pb
  TTree *bkg2 = (TTree*)f6 ->Get("ZZTree/candTree");
  TH1F *h6 = (TH1F*)f6->Get("ZZTree/Counters");


  TFile *f7 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo4mu_Contin_MCFM701/ZZ4lAnalysis.root");
//  ggTo4mu xsec = 0.00158549 pb
  TTree *bkg3 = (TTree*)f7 ->Get("ZZTree/candTree");
  TH1F *h7 = (TH1F*)f7->Get("ZZTree/Counters");




  static const int ncuts = 100; //I changed this wrt the previous version 
  float cuts[ncuts];

/* //I dont need this now 
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



   float Lumi=36.8E03; //Luminosity in pb-1 	
   
   float normSig= Lumi*0.4404E-03/NgenSig;

   float normbkg= Lumi*9.335E-03/NgenBKG;
   float normBkg1= Lumi*0.0031942/NgenBkg1;
   float normBkg2 = Lumi*0.00158549/NgenBkg2;
   float normBkg3 = Lumi*0.00158549/NgenBkg3;
*/

  TH1F *h1 = new TH1F("h1","h1",100,-1000,1000);
  char cutting[400];
  char cutting4e[400];
  char cutting4mu[400];
  char cutting2e2mu[400];

//Find the real number of events.  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu


sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > 0.66");

sprintf(cutting4e,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");


    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu); 

    float Nsig2e2mu = h1->Integral();
    cout << "Signal events 2e2mu:" << Nsig2e2mu << endl;
    
    float err2e2mu = 1/sqrt(Nsig2e2mu);
    cout << "Signal error 2e2mu: " << err2e2mu << endl;

    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    
    float Nsig4e = h1->Integral();
    cout << "Signal events 4e: " << Nsig4e << endl;
    
    float err4e = 1/sqrt(Nsig4e);
    cout << "Signal error 4e: " << err4e << endl;

    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    
    float Nsig4mu = h1->Integral();
    cout << "Signal events 4mu:" << Nsig4mu << endl;
    
    float err4mu = 1/sqrt(Nsig4mu);
    cout << "Signal error 4mu: " << err4mu << endl; 

    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    
    float NbkgZZto4e = h1->Integral();
    cout << "ZZ Bkg events 4e: " << NbkgZZto4e << endl;
    
    float errZZto4e = 1/sqrt(NbkgZZto4e);
    cout << "ZZ bkg error 4e: " << errZZto4e << endl;	

    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    
    float NbkgZZto4mu = h1->Integral();
    cout << "ZZ Bkg events 4mu: " << NbkgZZto4mu << endl;
    
    float errZZto4mu = 1/sqrt(NbkgZZto4mu);
    cout << "ZZ bkg error 4mu: " << errZZto4mu << endl;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu);
    
    float NbkgZZto2e2mu = h1->Integral();
    cout << "ZZ Bkg events 2e2mu: " << NbkgZZto2e2mu << endl;
    
    float errZZto2e2mu = 1/sqrt(NbkgZZto2e2mu);
    cout << "ZZ bkg error 2e2mu: " << errZZto2e2mu << endl;

//bkg1 -> gg to 2e2mu
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    
    float NbkgGGto2e2mu = h1->Integral();
    cout << "GG Bkg events 2e2mu: " << NbkgGGto2e2mu << endl;
    
    float errGGto2e2mu = 1/sqrt(NbkgGGto2e2mu);
    cout << "GG bkg error 2e2mu: " << errGGto2e2mu << endl;

//bkg 2 gg to 4e
    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    
    float NbkgGGto4e = h1->Integral();
    cout << "GG Bkg events 4e: " << NbkgGGto4e << endl;
    
    float errGGto4e = 1/sqrt(NbkgGGto4e);
    cout << "GG bkg error 4e: " << errGGto4e << endl;

//bkg3 gg to 4mu
    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    
    float NbkgGGto4mu = h1->Integral();
    cout << "GG Bkg events 4mu: " << NbkgGGto4mu << endl;
    
    float errGGto4mu = 1/sqrt(NbkgGGto4mu);
    cout << "GG bkg error 4mu: " << errGGto4mu << endl;



}
