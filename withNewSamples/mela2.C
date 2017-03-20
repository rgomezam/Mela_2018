#include <RooDataSet.h>



//Functions:

void retrieveRocCurve();
void plotRocCurve();
void getRates();
void getSystematics();

//Global Variables:
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

  TCanvas * c1 = new TCanvas("c1", "c1", 1000., 1000.);
  TH1F *h1 = new TH1F("h1","h1",100,-1000.,1000.);


  static const int ncuts = 101;
  float cuts[ncuts];
  float cutsMVA[ncuts];

  float NgenSig = hs->GetBinContent(1);
  float NgenBKG = h0->GetBinContent(1);
  float NgenBkg1 = h5->GetBinContent(1);
  float NgenBkg2 = h6->GetBinContent(1);
  float NgenBkg3 = h7->GetBinContent(1);
  
  float Lumi=36.8E03; //Luminosity in pb-1   
   
   float normSig= Lumi*0.4404E-03/NgenSig;
   float normbkg= Lumi*9.335E-03/NgenBKG;
   float normBkg1= Lumi*0.0031942/NgenBkg1;
   float normBkg2 = Lumi*0.00158549/NgenBkg2;
   float normBkg3 = Lumi*0.00158549/NgenBkg3;




void mela2() {

char opt;

//while(true){

  cout << "Enter:" << endl;
  
  cout << "a) to get the plot (previously calculated) with the ROC curve for MELA vs BDT" << endl;
  cout << "b) to recalculate the plot with the ROC curve for MELA vs BDT" << endl;
  cout << "c) To get the rates for the combine cards" << endl;
  cout << "d) To get the systematics for the combine cards" << endl;
  cout << " other to exit" << endl;
  
  cin >> opt;
  switch(opt){
  case 'a':
     cout << "Retrieving Roc curve" << endl;
     retrieveRocCurve();
     break;
   
  case 'b':
     cout << "Calculating Roc curve" << endl;
     plotRocCurve();
     break;

  case 'c': 
    cout << "Getting rates" << endl;
    getRates(/*f1, f2, f5, f6, f7, h1*/);
    break;

 case 'd':
    cout << "Getting systematics" << endl;
    getSystematics();
    break;

  default:
    break;

}  


return;

}





void plotRocCurve(){

gROOT->ProcessLine(".x tdrstyle.C"); 

  TCanvas * c1 = new TCanvas("c1", "c1", 1000., 1000.);
  TH1F *h1 = new TH1F("h1","h1",100,-1000.,1000.);

   float X,Y,Z,T;
   float Xp[ncuts];
   float Yp[ncuts];   
   float Zp[ncuts];
   float Tp[ncuts];


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



//Third and fourth: find the point given by the cuts: // (This has already been tested so I comment one of both) 
  sprintf(cutting2,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && abs(DiJetDEta) > 2.5 && DiJetMass > 400. ");
/*  sprintf(cutting2,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && abs(DiJetDEta) > 2.5 && DiJetMass > 400. ");

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
   

*/  


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
mg->SetTitle("; #epsilon_{B}; #epsilon_{S}"); // You can add a tittle in the first entry
TGraph *gr1 = new TGraph(ncuts, Beff, Seff); 
//TMarker *gr2 = new TMarker(X2,Y2,22);
TGraph *gr3 = new TGraph(ncuts, BeffMVA, SeffMVA); 
TMarker *gr4 = new TMarker(Z2,T2,22);
   
    gr1->SetLineWidth(7);
    gr1->SetLineColor(kRed);
    gr1->GetXaxis()->SetLimits(-0.07,1.07);
    gr1->SetMinimum(0.);
    gr1->SetMaximum(1.07);
    mg->Add(gr1); 
    
    
    gr3->SetLineWidth(7);
    gr3->SetLineColor(kBlue);
    gr3->GetXaxis()->SetLimits(-0.07,1.07);
    gr3->SetMinimum(0.);
    gr3->SetMaximum(1.07); 
    mg->Add(gr3); 
 

   // gr2->SetMarkerSize(4);
   // gr2->SetMarkerStyle(22);
    gr4->SetMarkerSize(4);  
    gr4->SetMarkerStyle(22);


    mg->Draw("AL");   
    //gr2->Draw("same");
    gr4->Draw("same");


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


//To save the plot in a ROOT file
TFile *fout =new TFile("ROC_MELA_vs_BDT.root", "RECREATE");
c1->Write();
fout-> Close();


c1->SaveAs("ROCcurve.gif");
c1->SaveAs("ROCcurve.pdf");

return;   //OBS I don't want return here, because then the canvas closes! 

}



void getRates(/*TFile *f1, TFile *f2, TFile *f5, TFile *f6, TFile *f7 , TH1F *h1*/){


  TH1F *h2 = new TH1F("h2","h2",100,0.,1.1);

  char cutting[400];
  char cutting4e[400];
  char cutting4mu[400];
  char cutting2e2mu[400];

//(no loop) find the rates (effsig=X , effbkg=Y)  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu (only needed in one sample) 

sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66");

sprintf(cutting4e,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2mu,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");


    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2e2mu); 
    float rate2e2mu = h2->Integral()*normSig;

    cout << "Signal rate 2e2mu:" << rate2e2mu << endl;
    
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4e);
    float rate4e = h2->Integral()*normSig;

    cout << "Signal rate 4e:" << rate4e << endl;
    
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting4mu);
    float rate4mu =  h2->Integral()*normSig;
    
    cout << "Signal rate 4mu:" << rate4mu << endl;  


    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h2",cutting4e);
    float ratebkgZZ4e = h2->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4e:" << ratebkgZZ4e << endl; 
    //cout << bkg->Scan("GenLep1Id:GenLep2Id:GenLep3Id:GenLep4Id") << endl; 

    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h2",cutting4mu);
    float ratebkgZZ4mu = h2->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4mu:" << ratebkgZZ4mu << endl;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h2",cutting2e2mu);
    float ratebkgZZ2e2mu = h2->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 2e2mu:" << ratebkgZZ2e2mu << endl;

//bkg1 -> gg to 2e2mu
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h2",cutting);
    float rategg2e2mu = h2->Integral()*normBkg1;

    cout << "Bkg rate gg -> 2e2mu:" << rategg2e2mu << endl;

//bkg 2 gg to 4e
    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h2",cutting);
    float rategg4e = h2->Integral()*normBkg2;

    cout << "Bkg rate gg -> 4e:" << rategg4e << endl;

//bkg3 gg to 4mu
    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h2",cutting);
    float rategg4mu = h2->Integral()*normBkg3;  
  
    cout << "Bkg rate gg -> 4mu:" << rategg4mu << endl;

return;
}




void retrieveRocCurve(){
gROOT->ProcessLine(".x tdrstyle.C"); 
TFile *roc = TFile::Open("ROC_MELA_vs_BDT.root");
TCanvas *c1 = (TCanvas*)roc->Get("c1"); 
c1->Draw();
//roc->Close();
return;
}





void getSystematics() {


  TH1F *h3 = new TH1F("h3","h3",100,0.,1.1);
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

sprintf(cutting4eDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4muDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2muDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");



    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting2e2mu); 
    float rate2e2mu = h3->Integral()*normSig;

    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cutting2e2muUp); 
    float rate2e2muUp = h3->Integral()*normSig;

    sig->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cutting2e2muDn); 
    float rate2e2muDn = h3->Integral()*normSig;
    
    cout << "Signal rate 2e2mu: " << rate2e2mu << endl;
    cout << "Signal rate 2e2muUp: " << rate2e2muUp << endl; 
    cout << "Signal rate 2e2muDn: " << rate2e2muDn << endl; 
    
    float DeltaSig2e2mu = (rate2e2muUp -rate2e2mu)/rate2e2mu;
    cout << "Delta S (2e2mu) [UP]" << DeltaSig2e2mu << endl; 
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting4e);
    float rate4e = h3->Integral()*normSig;
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cutting4eUp);
    float rate4eUp = h3->Integral()*normSig;

    sig->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cutting4eDn);
    float rate4eDn = h3->Integral()*normSig;

    
    cout << "Signal rate 4e:" << rate4e << endl;
    cout << "Signal rate 4eUp: " << rate4eUp << endl;
    cout << "Signal rate 4eDn: " << rate4eDn << endl;

    float DeltaSig4e = (rate4eUp -rate4e)/rate4e;
    cout << "Delta S (4e) [UP]" << DeltaSig4e << endl; 

     
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting4mu);
    float rate4mu =  h3->Integral()*normSig;
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cutting4muUp);
    float rate4muUp =  h3 ->Integral()*normSig;

     sig->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cutting4muDn);
    float rate4muDn =  h3->Integral()*normSig;

    cout << "Signal rate 4mu: " << rate4mu << endl;  
    cout << "Signal rate 4muUp: " << rate4muUp << endl;
    cout << "Signal rate 4muDn: " << rate4muDn << endl;

    float DeltaSig4mu = (rate4muUp -rate4mu)/rate4mu;
    cout << "Delta S (4mu) [UP]" << DeltaSig4mu << endl; 
     

    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting4e);
    float ratebkgZZ4e = h3->Integral()*normbkg;
     
    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cutting4eUp);
    float ratebkgZZ4eUp = h3->Integral()*normbkg;

    bkg->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cutting4eDn);
    float ratebkgZZ4eDn = h3->Integral()*normbkg;

    cout << "Bkg rate ZZ -> 4e:" << ratebkgZZ4e << endl; 
    //cout << bkg->Scan("GenLep1Id:GenLep2Id:GenLep3Id:GenLep4Id") << endl;
    cout << "Bkg rate ZZ -> 4e Up:" << ratebkgZZ4eUp << endl;	
    cout << "Bkg rate ZZ -> 4e Dn:" << ratebkgZZ4eDn << endl;	
   

    float DeltaBkgZZto4e = (ratebkgZZ4eUp - ratebkgZZ4e)/ratebkgZZ4e;
    cout << "Delta Bkg ZZ (4e) [UP]" << DeltaBkgZZto4e << endl; 



    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting4mu);
    float ratebkgZZ4mu = h3->Integral()*normbkg;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cutting4muUp);
    float ratebkgZZ4muUp = h3->Integral()*normbkg;

    bkg->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cutting4muDn);
    float ratebkgZZ4muDn = h3->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4mu:" << ratebkgZZ4mu << endl;
    cout << "Bkg rate ZZ -> 4mu Up: " << ratebkgZZ4muUp << endl;
    cout << "Bkg rate ZZ -> 4mu Dn: " << ratebkgZZ4muDn << endl;

    float DeltaBkgZZto4mu = (ratebkgZZ4muUp - ratebkgZZ4mu)/ratebkgZZ4mu;
    cout << "Delta Bkg ZZ (4mu) [UP]" << DeltaBkgZZto4mu << endl; 
   
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting2e2mu);
    float ratebkgZZ2e2mu = h3->Integral()*normbkg;

    bkg->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cutting2e2muUp);
    float ratebkgZZ2e2muUp = h3->Integral()*normbkg;
  
    bkg->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cutting2e2muDn);
    float ratebkgZZ2e2muDn = h3->Integral()*normbkg;
  
    cout << "Bkg rate ZZ -> 2e2mu:" << ratebkgZZ2e2mu << endl;
    cout << "Bkg rate ZZ -> 2e2mu Up:" << ratebkgZZ2e2muUp << endl;
    cout << "Bkg rate ZZ -> 2e2mu Dn:" << ratebkgZZ2e2muDn << endl;
 

    float DeltaBkgZZto2e2mu = (ratebkgZZ2e2muUp - ratebkgZZ2e2mu)/ratebkgZZ2e2mu;
    cout << "Delta Bkg ZZ (2e2mu) [UP]" << DeltaBkgZZto2e2mu << endl; 


//bkg1 -> gg to 2e2mu
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting);
    float rategg2e2mu = h3->Integral()*normBkg1;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cuttingUp);
    float rategg2e2muUp = h3->Integral()*normBkg1;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cuttingDn);
    float rategg2e2muDn = h3->Integral()*normBkg1;

    cout << "Bkg rate gg -> 2e2mu:" << rategg2e2mu << endl;
    cout << "Bkg rate gg -> 2e2mu Up:" << rategg2e2muUp << endl;
    cout << "Bkg rate gg -> 2e2mu Dn:" << rategg2e2muDn << endl;
    
    float DeltaBkgGGto2e2mu = (rategg2e2muUp - rategg2e2mu)/rategg2e2mu;
    cout << "Delta Bkg gg (2e2mu) [UP]" << DeltaBkgGGto2e2mu << endl; 


//bkg 2 gg to 4e
    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting);
    float rategg4e = h3->Integral()*normBkg2;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cuttingUp);
    float rategg4eUp = h3->Integral()*normBkg2;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cuttingDn);
    float rategg4eDn = h3->Integral()*normBkg2;

    cout << "Bkg rate gg -> 4e:" << rategg4e << endl;
    cout << "Bkg rate gg -> 4e Up:" << rategg4eUp << endl;
    cout << "Bkg rate gg -> 4e Dn:" << rategg4eDn << endl;
    
    float DeltaBkgGGto4e = (rategg4eUp - rategg4e)/rategg4e;
    cout << "Delta Bkg gg (4e) [UP]" << DeltaBkgGGto4e << endl; 



//bkg3 gg to 4mu
    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h3",cutting);
    float rategg4mu = h3->Integral()*normBkg3;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h3",cuttingUp);
    float rategg4muUp = h3->Integral()*normBkg3;	

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h3",cuttingDn);
    float rategg4muDn = h3->Integral()*normBkg3;	
   
    cout << "Bkg rate gg -> 4mu:" << rategg4mu << endl;
    cout << "Bkg rate gg -> 4mu Up:" << rategg4muUp << endl;
    cout << "Bkg rate gg -> 4mu Dn:" << rategg4muDn << endl;
    
    float DeltaBkgGGto4mu = (rategg4muUp - rategg4mu)/rategg4mu;
    cout << "Delta Bkg gg (4mu) [UP]" << DeltaBkgGGto4mu << endl;

    


return;

}

