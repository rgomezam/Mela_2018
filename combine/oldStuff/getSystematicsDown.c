#include <RooDataSet.h>

// This ROOT macro gets you the rates for each channel, to put in combine

void getSystematicsDown() {

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
  char cutting4e[400];
  char cutting4mu[400];
  char cutting2e2mu[400];
  char cuttingDn[400];
  char cutting4eDn[400];
  char cutting4muDn[400];
  char cutting2e2muDn[400];


//(no loop) find the rates (effsig=X , effbkg=Y)  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu (only needed in one sample) 


sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66");

sprintf(cuttingDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66");

sprintf(cutting4e,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");

sprintf(cutting4eDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4muDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2muDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");


    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu); 
    float rate2e2mu = h1->Integral()*normSig;

    sig->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cutting2e2muDn); 
    float rate2e2muDn = h1->Integral()*normSig;
    
    cout << "Signal rate 2e2mu: " << rate2e2mu << endl;
    cout << "Signal rate 2e2muDn: " << rate2e2muDn << endl;
    
    float DeltaSig2e2mu = (rate2e2muDn - rate2e2mu)/rate2e2mu;
    cout << "Delta S (2e2mu) " << DeltaSig2e2mu << endl; 
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    float rate4e = h1->Integral()*normSig;
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cutting4eDn);
    float rate4eDn = h1->Integral()*normSig;

    cout << "Signal rate 4e:" << rate4e << endl;
    cout << "Signal rate 4eDn: " << rate4eDn << endl;

    float DeltaSig4e = (rate4eDn -rate4e)/rate4e;
    cout << "Delta S (4e) " << DeltaSig4e << endl; 

     
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    float rate4mu =  h1->Integral()*normSig;
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cutting4muDn);
    float rate4muDn =  h1->Integral()*normSig;

    cout << "Signal rate 4mu: " << rate4mu << endl;  
    cout << "Signal rate 4muDn: " << rate4muDn << endl;

    float DeltaSig4mu = (rate4muDn -rate4mu)/rate4mu;
    cout << "Delta S (4mu) " << DeltaSig4mu << endl; 
     

    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    float ratebkgZZ4e = h1->Integral()*normbkg;
     
    bkg->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cutting4eDn);
    float ratebkgZZ4eDn = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4e:" << ratebkgZZ4e << endl; 
    //cout << bkg->Scan("GenLep1Id:GenLep2Id:GenLep3Id:GenLep4Id") << endl;
    cout << "Bkg rate ZZ -> 4e Dn:" << ratebkgZZ4eDn << endl;	


    float DeltaBkgZZto4e = (ratebkgZZ4eDn - ratebkgZZ4e)/ratebkgZZ4e;
    cout << "Delta Bkg ZZ (4e) " << DeltaBkgZZto4e << endl; 



    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    float ratebkgZZ4mu = h1->Integral()*normbkg;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cutting4muDn);
    float ratebkgZZ4muDn = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4mu:" << ratebkgZZ4mu << endl;
    cout << "Bkg rate ZZ -> 4mu Dn: " << ratebkgZZ4muDn << endl;

    float DeltaBkgZZto4mu = (ratebkgZZ4muDn - ratebkgZZ4mu)/ratebkgZZ4mu;
    cout << "Delta Bkg ZZ (4mu) " << DeltaBkgZZto4mu << endl; 
   
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu);
    float ratebkgZZ2e2mu = h1->Integral()*normbkg;

    bkg->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cutting2e2muDn);
    float ratebkgZZ2e2muDn = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 2e2mu:" << ratebkgZZ2e2mu << endl;
    cout << "Bkg rate ZZ -> 2e2mu Dn:" << ratebkgZZ2e2muDn << endl;

    float DeltaBkgZZto2e2mu = (ratebkgZZ2e2muDn - ratebkgZZ2e2mu)/ratebkgZZ2e2mu;
    cout << "Delta Bkg ZZ (2e2mu) " << DeltaBkgZZto2e2mu << endl; 


//bkg1 -> gg to 2e2mu
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float rategg2e2mu = h1->Integral()*normBkg1;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cuttingDn);
    float rategg2e2muDn = h1->Integral()*normBkg1;

    cout << "Bkg rate gg -> 2e2mu:" << rategg2e2mu << endl;
    cout << "Bkg rate gg -> 2e2mu Dn:" << rategg2e2muDn << endl;

    float DeltaBkgGGto2e2mu = (rategg2e2muDn - rategg2e2mu)/rategg2e2mu;
    cout << "Delta Bkg gg (2e2mu) " << DeltaBkgGGto2e2mu << endl; 


//bkg 2 gg to 4e
    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float rategg4e = h1->Integral()*normBkg2;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cuttingDn);
    float rategg4eDn = h1->Integral()*normBkg2;

    cout << "Bkg rate gg -> 4e:" << rategg4e << endl;
    cout << "Bkg rate gg -> 4e Dn:" << rategg4eDn << endl;

    
    float DeltaBkgGGto4e = (rategg4eDn - rategg4e)/rategg4e;
    cout << "Delta Bkg gg (4e) " << DeltaBkgGGto4e << endl; 



//bkg3 gg to 4mu
    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float rategg4mu = h1->Integral()*normBkg3;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1",cuttingDn);
    float rategg4muDn = h1->Integral()*normBkg3;	
  
    cout << "Bkg rate gg -> 4mu:" << rategg4mu << endl;
    cout << "Bkg rate gg -> 4mu Dn:" << rategg4muDn << endl;
   
    
    float DeltaBkgGGto4mu = (rategg4muDn - rategg4mu)/rategg4mu;
    cout << "Delta Bkg gg (4mu) " << DeltaBkgGGto4mu << endl;

    




}
