#include <RooDataSet.h>

// This ROOT macro gets you the rates for each channel, to put in combine

void getSystematics() {

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


  TH1F *h1 = new TH1F("h1","h1",100,0.,1.1);
  char cutting[400];
  char cutting4e[400];
  char cutting4mu[400];
  char cutting2e2mu[400];
  char cuttingUp[400];
  char cutting4eUp[400];
  char cutting4muUp[400];
  char cutting2e2muUp[400];


//(no loop) find the rates (effsig=X , effbkg=Y)  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu (only needed in one sample) 


sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66");

sprintf(cuttingUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66");

sprintf(cutting4e,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");

sprintf(cutting4eUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4muUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2muUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");


    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu); 
    float rate2e2mu = h1->Integral()*normSig;

    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cutting2e2muUp); 
    float rate2e2muUp = h1->Integral()*normSig;
    
    cout << "Signal rate 2e2mu: " << rate2e2mu << endl;
    cout << "Signal rate 2e2muUp: " << rate2e2muUp << endl;
    
    float DeltaSig2e2mu = (rate2e2muUp -rate2e2mu)/rate2e2mu;
    cout << "Delta S (2e2mu) " << DeltaSig2e2mu << endl; 
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    float rate4e = h1->Integral()*normSig;
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cutting4eUp);
    float rate4eUp = h1->Integral()*normSig;

    cout << "Signal rate 4e:" << rate4e << endl;
    cout << "Signal rate 4eUp: " << rate4eUp << endl;

    float DeltaSig4e = (rate4eUp -rate4e)/rate4e;
    cout << "Delta S (4e) " << DeltaSig4e << endl; 

     
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    float rate4mu =  h1->Integral()*normSig;
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cutting4muUp);
    float rate4muUp =  h1->Integral()*normSig;

    cout << "Signal rate 4mu: " << rate4mu << endl;  
    cout << "Signal rate 4muUp: " << rate4muUp << endl;

    float DeltaSig4mu = (rate4muUp -rate4mu)/rate4mu;
    cout << "Delta S (4mu) " << DeltaSig4mu << endl; 
     

    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    float ratebkgZZ4e = h1->Integral()*normbkg;
     
    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cutting4eUp);
    float ratebkgZZ4eUp = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4e:" << ratebkgZZ4e << endl; 
    //cout << bkg->Scan("GenLep1Id:GenLep2Id:GenLep3Id:GenLep4Id") << endl;
    cout << "Bkg rate ZZ -> 4e Up:" << ratebkgZZ4eUp << endl;	


    float DeltaBkgZZto4e = (ratebkgZZ4eUp - ratebkgZZ4e)/ratebkgZZ4e;
    cout << "Delta Bkg ZZ (4e) " << DeltaBkgZZto4e << endl; 



    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    float ratebkgZZ4mu = h1->Integral()*normbkg;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cutting4muUp);
    float ratebkgZZ4muUp = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4mu:" << ratebkgZZ4mu << endl;
    cout << "Bkg rate ZZ -> 4mu Up: " << ratebkgZZ4muUp << endl;

    float DeltaBkgZZto4mu = (ratebkgZZ4muUp - ratebkgZZ4mu)/ratebkgZZ4mu;
    cout << "Delta Bkg ZZ (4mu) " << DeltaBkgZZto4mu << endl; 
   
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu);
    float ratebkgZZ2e2mu = h1->Integral()*normbkg;

    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cutting2e2muUp);
    float ratebkgZZ2e2muUp = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 2e2mu:" << ratebkgZZ2e2mu << endl;
    cout << "Bkg rate ZZ -> 2e2mu Up:" << ratebkgZZ2e2muUp << endl;

    float DeltaBkgZZto2e2mu = (ratebkgZZ2e2muUp - ratebkgZZ2e2mu)/ratebkgZZ2e2mu;
    cout << "Delta Bkg ZZ (2e2mu) " << DeltaBkgZZto2e2mu << endl; 


//bkg1 -> gg to 2e2mu
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float rategg2e2mu = h1->Integral()*normBkg1;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    float rategg2e2muUp = h1->Integral()*normBkg1;

    cout << "Bkg rate gg -> 2e2mu:" << rategg2e2mu << endl;
    cout << "Bkg rate gg -> 2e2mu Up:" << rategg2e2muUp << endl;

    float DeltaBkgGGto2e2mu = (rategg2e2muUp - rategg2e2mu)/rategg2e2mu;
    cout << "Delta Bkg gg (2e2mu) " << DeltaBkgGGto2e2mu << endl; 


//bkg 2 gg to 4e
    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float rategg4e = h1->Integral()*normBkg2;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    float rategg4eUp = h1->Integral()*normBkg2;

    cout << "Bkg rate gg -> 4e:" << rategg4e << endl;
    cout << "Bkg rate gg -> 4e Up:" << rategg4eUp << endl;

    
    float DeltaBkgGGto4e = (rategg4eUp - rategg4e)/rategg4e;
    cout << "Delta Bkg gg (4e) " << DeltaBkgGGto4e << endl; 



//bkg3 gg to 4mu
    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float rategg4mu = h1->Integral()*normBkg3;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1",cuttingUp);
    float rategg4muUp = h1->Integral()*normBkg3;	
  
    cout << "Bkg rate gg -> 4mu:" << rategg4mu << endl;
    cout << "Bkg rate gg -> 4mu Up:" << rategg4muUp << endl;
   
    
    float DeltaBkgGGto4mu = (rategg4muUp - rategg4mu)/rategg4mu;
    cout << "Delta Bkg gg (4mu) " << DeltaBkgGGto4mu << endl;

    




}
