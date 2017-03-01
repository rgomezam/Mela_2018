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
   float Lumi=36.8E-03; //Luminosity in pb-1 	
   
   float normSig= Lumi*0.4404E-03/NgenSig;

   float normbkg= Lumi*9.335E-03/NgenBKG;
   float normBkg1= Lumi*0.0031942/NgenBkg1;
   float normBkg2 = Lumi*0.00158549/NgenBkg2;
   float normBkg3 = Lumi*0.00158549/NgenBkg3;


   float X,Y,Z,T;
   float Xp[ncuts];
   float Yp[ncuts];   
   float Zp[ncuts];
   float Tp[ncuts];

  TH1F *h1 = new TH1F("h1","h1",100,0.,1.1);
  char cutting[400];
  char cutting2[400];


// First (no loop) find the denominators (effsig=X , effbkg=Y)  OBS Here there is a cut on mjj is 100 (fiducial)

    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. ");
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting); 
    float effsig0 = h1->Integral()*normSig;    

    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg0 = h1->Integral()*normbkg;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg3;	
  
    //ZZjj_MVA

    sig->Draw("ZZjj_MVA >> h1",cutting); 
    float effsigMVA0 = h1->Integral()*normSig;    
    
    bkg->Draw("ZZjj_MVA >> h1",cutting);
    float effbkgMVA0 = h1->Integral()*normbkg;

    bkg1->Draw("ZZjj_MVA >> h1",cutting);
    effbkgMVA0 =+ h1->Integral()*normBkg1;

    bkg2->Draw("ZZjj_MVA >> h1",cutting);
    effbkgMVA0 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("ZZjj_MVA >> h1",cutting);
    effbkgMVA0 =+ h1->Integral()*normBkg3;	

    X = effbkg0;
    Y = effsig0;
    
    Z = effbkgMVA0;
    T = effsigMVA0;
    

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Second (loop) find the numerators (effsig=X , effbkg=Y)   
  for (int i=0; i<ncuts; i++) {
    cuts[i] = i*0.02;
    sprintf(cutting,"nCleanedJetsPt30 > 1 && DiJetMass > 100. && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && ZZjj_MVA > %f",cuts[i]);
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effsig = h1->Integral()*normSig;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg = h1->Integral()*normbkg;
    //cout << "### Cut at " << cuts[i] << " : pass bkg = " << h1->Integral() << " eff bkg = " << effbkg << endl;
   
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg2;

    bkg3->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg3;

// ZZjj_MVA

    sig->Draw("ZZjj_MVA >> h1",cutting); 
    float effsigMVA = h1->Integral()*normSig;    
    
    bkg->Draw("ZZjj_MVA >> h1",cutting);
    float effbkgMVA = h1->Integral()*normbkg;

    bkg1->Draw("ZZjj_MVA >> h1",cutting);
    effbkgMVA =+ h1->Integral()*normBkg1;

    bkg2->Draw("ZZjj_MVA >> h1",cutting);
    effbkgMVA =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("ZZjj_MVA >> h1",cutting);
    effbkgMVA =+ h1->Integral()*normBkg3;



    Yp[i] = effsig;
    Xp[i] = effbkg;
    Tp[i] = effsigMVA;
    Zp[i] = effbkgMVA;

  }


float Seff[ncuts];
float Beff[ncuts];
float SeffMVA[ncuts];
float BeffMVA[ncuts];

for (int i=0; i<ncuts; i++) {
Beff[i]=Xp[i]/X;
Seff[i]=Yp[i]/Y;
BeffMVA[i]=Zp[i]/Z;
SeffMVA[i]=Tp[i]/T;
}


//Third: find the point given by the cuts: 
   sprintf(cutting2,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && abs(DiJetDEta) > 2.5 && DiJetMass > 400. ");
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    float effsig2 = h1->Integral()*normSig;
   
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    float effbkg2 = h1->Integral()*normbkg;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effbkg2 =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effbkg2 =+ h1->Integral()*normBkg2;
 
    bkg3->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effbkg2 =+ h1->Integral()*normBkg3;
    

  
    double Y2 = effsig2/Y;
    double X2 = effbkg2/X;
    
	

//Fourth: test see if you produce the same point with the mva

    // ZZjj_MVA

    sig->Draw("ZZjj_MVA >> h1",cutting2); 
    float effsigMVA2 = h1->Integral()*normSig;    
    
    bkg->Draw("ZZjj_MVA >> h1",cutting2);
    float effbkgMVA2 = h1->Integral()*normbkg;

    bkg1->Draw("ZZjj_MVA >> h1",cutting2);
    effbkgMVA2 =+ h1->Integral()*normBkg1;

    bkg2->Draw("ZZjj_MVA >> h1",cutting2);
    effbkgMVA2 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("ZZjj_MVA >> h1",cutting2);
    effbkgMVA2 =+ h1->Integral()*normBkg3;


    double Z2 = effbkgMVA2/Z;    
    double T2 = effsigMVA2/T;
    



  //TGraph* gr = new TGraph(ncuts, Beff, Seff);
  //gr->Draw("ALP*");
  //TGraph *gr2 = new TGraph(1, Y2, X2);
  //gr2->SetMarkerStyle(21);  
  //gr2->Draw("ALP* same");

  

//TMultiGraph* mg  = new TMultiGraph();
TGraph *gr1 = new TGraph(ncuts, Beff, Seff); 
//TGraph *gr2 = new TGraph(1, Y2, X2);
TMarker *gr2 = new TMarker(X2,Y2,22);
   //gROOT->ProcessLine(".x tdrstyle.C");
//TMultiGraph* mg  = new TMultiGraph();
TGraph *gr3 = new TGraph(ncuts, BeffMVA, SeffMVA); 
//TGraph *gr2 = new TGraph(1, Y2, X2);
TMarker *gr4 = new TMarker(Z2,T2,21);
   //gROOT->ProcessLine(".x tdrstyle.C");
   
    gr1->SetTitle("ROC curve MELA");
    gr1->SetLineWidth(1);
    gr1->SetLineColor(2);
    gr1->GetXaxis()->SetLimits(-0.07,1.07);
    gr1->GetXaxis()->SetTitle("Background eff");
    gr1->GetYaxis()->SetTitle("Signal eff");
    gr1->SetMinimum(0.);
    gr1->SetMaximum(1.07);
    
    gr3->SetTitle("ROC curve MVA");
    gr3->SetLineWidth(1);
    gr3->SetLineColor(3);
    gr3->GetXaxis()->SetLimits(-0.07,1.07);
    //gr3->GetXaxis()->SetTitle("Background eff");
    //gr3->GetYaxis()->SetTitle("Signal eff");
    gr3->SetMinimum(0.);
    gr3->SetMaximum(1.07);   

    gr1->Draw("ALP");
    gr2->Draw("same");
//    gr3->Draw("same");
//    gr4->Draw("same");

//mg->Add(gr1); gr1->SetTitle("esempio"); gr1->GetYaxis()->SetTitle("#epsilon_{S}");
//mg->Add(gr2); gr2->SetTitle("esempi2"); 
//mg->Draw("ALP*"); 	
  TLegend *legend = new TLegend(0.70,0.25,0.95,0.40,NULL,"brNDC");
  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    42);
  legend->SetTextSize  (0.03);
  legend->AddEntry(gr1, "MELA" , "l");
  legend->AddEntry(gr2, "VBS cut-based" , "l");
  legend->AddEntry(gr3, "BDT" , "l");
  legend->AddEntry(gr2, "BDT cut-based" , "l");
  legend->Draw("same");
 
float distX=abs(Beff[0]-X2);
float distY=abs(Seff[0]-Y2);
float epsilonX, epsilonY;
int minX, minY;

for (int i=1;i<ncuts; i++){
cout << "distance X " << abs(Beff[i]-X2) << endl;
if (abs(Beff[i]-X2)< distX){
distX=abs(Beff[i]-X2);
minX=i;
cout << "Closest x is " << i << endl;
}
cout << "distance Y " << abs(Seff[i]-Y2) << endl;
if (abs(Seff[i]-Y2)< distY){
distY=abs(Seff[i]-Y2);
minY=i;
cout << "Closest y is " << i << endl;
}

}

epsilonX= abs(Beff[minY]-X2); 
cout << "EpsilonX: " << epsilonX << endl;
epsilonY=abs(Seff[minX]-Y2);
cout << "EpsilonY: " << epsilonY << endl; 

}




