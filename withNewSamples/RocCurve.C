#include <RooDataSet.h>
//#include "tdrstyle.C"
//#include "CMS_lumi.C"
//#include "CMS_lumi.h"


void RocCurve() {

gROOT->ProcessLine(".x tdrstyle.C"); 
//gROOT->ProcessLine(".x CMS_lumi.C");


  TFile *f1 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_ewk/ZZ4lAnalysis.root");
// ZZjj_ewk xsec= 0.4404E-03
  TTree *sig = (TTree*)f1->Get("ZZTree/candTree");
  TH1F *hs = (TH1F*)f1->Get("ZZTree/Counters");


  TFile *f2 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ZZjj_qcd/ZZ4lAnalysis.root");
// ZZjj_qcd xsec = 9.335E-03 pb
  TTree *bkg = (TTree*)f2->Get("ZZTree/candTree");
  TH1F *h0 = (TH1F*)f2->Get("ZZTree/Counters");	

  TFile *f5 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo2e2mu_Contin_MCFM701_NonWimpy/ZZ4lAnalysis.root");
//  ggTo2e2mu xsec = 0.0031942 pb
  TTree *bkg1 = (TTree*)f5->Get("ZZTree/candTree");
  TH1F *h5 = (TH1F*)f5->Get("ZZTree/Counters");

  TFile *f6 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo4e_Contin_MCFM701_NonWimpy/ZZ4lAnalysis.root");
//  ggTo4e  xsec = 0.00158549 pb
  TTree *bkg2 = (TTree*)f6 ->Get("ZZTree/candTree");
  TH1F *h6 = (TH1F*)f6->Get("ZZTree/Counters");


  TFile *f7 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170210/ggTo4mu_Contin_MCFM701_NonWimpy/ZZ4lAnalysis.root");
//  ggTo4mu xsec = 0.00158549 pb
  TTree *bkg3 = (TTree*)f7 ->Get("ZZTree/candTree");
  TH1F *h7 = (TH1F*)f7->Get("ZZTree/Counters");




  static const int ncuts = 101;
  float cuts[ncuts];
  float cutsMVA[ncuts];

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

   float X,Y,Z,T;
   float Xp[ncuts];
   float Yp[ncuts];   
   float Zp[ncuts];
   float Tp[ncuts];

  TCanvas * c1 = new TCanvas("c1", "c1", 1000., 1000.);
  TH1F *h1 = new TH1F("h1","h1",100,-1000.,1000.);
  char cutting[400];
  char cutting2[400];
  char cuttingMVA[400];


// First (no loop) find the denominators (effsig=X , effbkg=Y)  OBS Here there is a cut on mjj is 100 (fiducial)

    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. ");
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting); 
    float effsig0 = h1->Integral()*normSig;    
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg0 = h1->Integral()*normbkg;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg3;     

    X = effbkg0;
    Y = effsig0;	
  
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
	
    
    Z = effbkgMVA0;
    T = effsigMVA0;
    


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Second (loop) find the numerators (effsig=X , effbkg=Y)   
  for (int i=0; i<ncuts; i++) {
    cuts[i] = i*0.01;
    sprintf(cutting,"nCleanedJetsPt30 > 1 && DiJetMass > 100. && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > %f",cuts[i]);
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effsig = h1->Integral()*normSig;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg = h1->Integral()*normbkg;
    //cout << "### Cut at " << cuts[i] << " : pass bkg = " << h1->Integral() << " eff bkg = " << effbkg << endl;
    
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg2;

    bkg3->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg3;

    Yp[i] = effsig;
    Xp[i] = effbkg;

// ZZjj_MVA
   cutsMVA[i] = -0.63 + i*0.0147;
   sprintf(cuttingMVA,"nCleanedJetsPt30 > 1 && DiJetMass > 100. && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && ZZjj_MVA > %f",cutsMVA[i]);
    sig->Draw("ZZjj_MVA >> h1",cuttingMVA); 
    float effsigMVA = h1->Integral()*normSig;    
    
    bkg->Draw("ZZjj_MVA >> h1",cuttingMVA);
    float effbkgMVA = h1->Integral()*normbkg;

    bkg1->Draw("ZZjj_MVA >> h1",cuttingMVA);
    effbkgMVA =+ h1->Integral()*normBkg1;

    bkg2->Draw("ZZjj_MVA >> h1",cuttingMVA);
    effbkgMVA =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("ZZjj_MVA >> h1",cuttingMVA);
    effbkgMVA =+ h1->Integral()*normBkg3;



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
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    float effsig2 = h1->Integral()*normSig;
   
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    float effbkg2 = h1->Integral()*normbkg;
 

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effbkg2 =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effbkg2 =+ h1->Integral()*normBkg2;
 
    bkg3->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effbkg2 =+ h1->Integral()*normBkg3;
    
  
    float Y2 = effsig2/Y; //Tmarker is double, TGraph is float
    float X2 = effbkg2/X;
    
	

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
    
    float Z2 = effbkgMVA2/Z;    
    float T2 = effsigMVA2/T;
    




TMultiGraph* mg  = new TMultiGraph();
mg->SetTitle("Global title; #epsilon_{B}; #epsilon_{S}");
TGraph *gr1 = new TGraph(ncuts, Beff, Seff); 
//TMarker *gr2 = new TMarker(X2,Y2,22);
TGraph *gr3 = new TGraph(ncuts, BeffMVA, SeffMVA); 
TMarker *gr4 = new TMarker(Z2,T2,21);
   
    //gr1->SetTitle("ROC curve MELA");
    gr1->SetLineWidth(7);
    gr1->SetLineColor(kRed);
    gr1->GetXaxis()->SetLimits(-0.07,1.07);
    //gr1->GetXaxis()->SetTitle("Background eff");
    //gr1->GetYaxis()->SetTitle("Signal eff");
    gr1->SetMinimum(0.);
    gr1->SetMaximum(1.07);
    mg->Add(gr1); 
    
    
    gr3->SetLineWidth(7);
    gr3->SetLineColor(kBlue);
    gr3->GetXaxis()->SetLimits(-0.07,1.07);
    //gr3->GetXaxis()->SetTitle("Background eff");
    //gr3->GetYaxis()->SetTitle("Signal eff");
    gr3->SetMinimum(0.);
    gr3->SetMaximum(1.07); 
    mg->Add(gr3); 
 
    //gr2->SetMarkerStyle(22);
    gr4->SetMarkerSize(4);	
    gr4->SetMarkerStyle(22);


    //mg->SetTitle("ROC curve MELA");
    mg->Draw("AL"); 	
    //gr2->Draw("same");
    gr4->Draw("same");

    /*gPad->Update();
    mg->GetXaxis()->SetTitle("Background eff");
    mg->GetYaxis()->SetTitle("Signal eff");
    
    gPad->Update();
    mg->GetHistogram()->SetTitle("ROC curve MELA");
*/

  TLegend *legend = new TLegend(0.50,0.25,0.80,0.40,NULL,"brNDC");
  legend->SetBorderSize(     0);
  legend->SetFillColor (     0);
  legend->SetTextAlign (    12);
  legend->SetTextFont  (    62);
  legend->SetTextSize  (0.04);
  legend->AddEntry(gr1, "MELA" , "l");
  // legend->AddEntry(gr2, "VBS cut-based" , "l");
  legend->AddEntry(gr3, "BDT" , "l");
  legend->AddEntry(gr4, "Cut-based" , "p");
  //legend->SetMarkerSize(20);
  legend->Draw("same");
 
TPaveText *pt = new TPaveText(0.18,0.9,0.4,0.85, "NDC");
pt->SetFillColor(0);
pt->SetTextFont(62);
pt->SetTextSize  (0.04);
pt->AddText("CMS ");
pt->Draw("same");

TPaveText *pt2 = new TPaveText(0.18,0.85,0.4,0.80, "NDC");
pt2->AddText(" Simulation");
pt2->SetFillColor(0);
pt2->SetTextFont(52);
pt2->SetTextSize  (0.04);
pt2->Draw("same");

//gPad->Update();
//gPad->Modified();




}


