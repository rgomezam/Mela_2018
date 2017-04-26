#include <RooDataSet.h>
#include <string.h> //strncat
#include <cmath> // abs

//Functions:
void retrieveRocCurve();
void plotRocCurve();
void getRates();
void getSystematics();
void getBkgStat() ;
void SetCuts();
void SetCutsScale(int n);
void SetCutsPDF(int n);
void scaleVariations();
void PDFVariations();

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

 
  char Discriminant[400] = {"p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) >> h1"};
  char Discriminant_JeCUp[400] = {"p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) >> h1"};
  char Discriminant_JeCDn[400] = {"p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) >> h1"};


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

char cutting[400];
char cuttingCandC[400];
char cutting66[400];
char cutting4e66[400];
char cutting4mu66[400];
char cutting2e2mu66[400];
char cuttingUp[400];
char cutting4eUp[400];
char cutting4muUp[400];
char cutting2e2muUp[400];
char cuttingDn[400]; 
char cutting4eDn[400];
char cutting4muDn[400];
char cutting2e2muDn[400];


void mela3() {

char opt;

SetCuts(); //Allocate all the cutting functions

//while(true){

  cout << "Enter:" << endl;
  
  cout << "a) to get the plot (previously calculated) with the ROC curve for MELA vs BDT" << endl;
  cout << "b) to recalculate the plot with the ROC curve for MELA vs BDT" << endl;
  cout << "c) To get the rates for the combine cards" << endl;
  cout << "d) To get the systematics for the combine cards" << endl;
  cout << "e) To get the MC stats. for the combine cards" << endl;
  cout << "f) To test the scale variations" << endl;
  cout << "g) to test the PDF variations" << endl;
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

case 'e':
    cout << "Getting MC stats" << endl;
    getBkgStat();
    break;

case 'f':
    cout << "Getting scale variations" << endl;
    scaleVariations();
    break;

case 'g':
   cout << "Getting PDF variations" << endl;
   PDFVariations();
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


  char cuttingi[400]; 
  char cuttingCandC[400];
  char cuttingMVA[400];
  

// First (no loop) find the denominators (effsig=X , effbkg=Y)  OBS Here there is a cut on mjj is 100 (fiducial)
    
    sig->Draw(Discriminant,cutting); 
    float effsig0 = h1->Integral()*normSig;    
    

    bkg->Draw(Discriminant,cutting);
    float effbkg0 = h1->Integral()*normbkg;

    bkg1->Draw(Discriminant,cutting);
    effbkg0 =+ h1->Integral()*normBkg1;


    bkg2->Draw(Discriminant,cutting);
    effbkg0 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw(Discriminant,cutting);
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
    sprintf(cuttingi,"nCleanedJetsPt30 > 1 && DiJetMass > 100. && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > %f",cuts[i]);
    
    sig->Draw(Discriminant,cutting);
    float effsig = h1->Integral()*normSig;
    cout << "This is a test: effsig" <<  effsig << endl; // This is a test

    
    bkg->Draw(Discriminant,cutting);
    float effbkg = h1->Integral()*normbkg;
    //cout << "### Cut at " << cuts[i] << " : pass bkg = " << h1->Integral() << " eff bkg = " << effbkg << endl;
    
    bkg1->Draw(Discriminant,cutting);
    effbkg =+ h1->Integral()*normBkg1;

    bkg2->Draw(Discriminant,cutting);
    effbkg =+ h1->Integral()*normBkg2;

    bkg3->Draw(Discriminant,cutting);
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
/*  
    sig->Draw(Discriminant,cutting2);
    float effsig2 = h1->Integral()*normSig;
   
    
    bkg->Draw(Discriminant,cutting2);
    float effbkg2 = h1->Integral()*normbkg;
 

    bkg1->Draw(Discriminant,cutting2);
    effbkg2 =+ h1->Integral()*normBkg1;

    bkg2->Draw(Discriminant,cutting2);
    effbkg2 =+ h1->Integral()*normBkg2;
 
    bkg3->Draw(Discriminant,cutting2);
    effbkg2 =+ h1->Integral()*normBkg3;
    
  
    float Y2 = effsig2/Y; //Tmarker is double, TGraph is float
    float X2 = effbkg2/X;
   

*/  


//Fourth: test see if you produce the same point with the mva

    // ZZjj_MVA

    sig->Draw("ZZjj_MVA >> h1",cuttingCandC); 
    float effsigMVA2 = h1->Integral()*normSig;    
    
    bkg->Draw("ZZjj_MVA >> h1",cuttingCandC);
    float effbkgMVA2 = h1->Integral()*normbkg;

    bkg1->Draw("ZZjj_MVA >> h1",cuttingCandC);
    effbkgMVA2 =+ h1->Integral()*normBkg1;

    bkg2->Draw("ZZjj_MVA >> h1",cuttingCandC);
    effbkgMVA2 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("ZZjj_MVA >> h1",cuttingCandC);
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

return; 

}



void getRates(/*TFile *f1, TFile *f2, TFile *f5, TFile *f6, TFile *f7 , TH1F *h1*/){


//(no loop) find the rates (effsig=X , effbkg=Y)  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu (only needed in one sample) 


    sig->Draw(Discriminant,cutting2e2mu66); 
    float rate2e2mu = h1->Integral()*normSig;

    cout << "Signal rate 2e2mu:" << rate2e2mu << endl;
    
    
    sig->Draw(Discriminant,cutting4e66);
    float rate4e = h1->Integral()*normSig;

    cout << "Signal rate 4e:" << rate4e << endl;
    
    
    sig->Draw(Discriminant,cutting4mu66);
    float rate4mu =  h1->Integral()*normSig;
    
    cout << "Signal rate 4mu:" << rate4mu << endl;  


    bkg->Draw(Discriminant,cutting4e66);
    float ratebkgZZ4e = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4e:" << ratebkgZZ4e << endl; 
    //cout << bkg->Scan("GenLep1Id:GenLep2Id:GenLep3Id:GenLep4Id") << endl; 

    bkg->Draw(Discriminant,cutting4mu66);
    float ratebkgZZ4mu = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4mu:" << ratebkgZZ4mu << endl;
    
    bkg->Draw(Discriminant,cutting2e2mu66);
    float ratebkgZZ2e2mu = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 2e2mu:" << ratebkgZZ2e2mu << endl;

//bkg1 -> gg to 2e2mu
    bkg1->Draw(Discriminant,cutting66);
    float rategg2e2mu = h1->Integral()*normBkg1;

    cout << "Bkg rate gg -> 2e2mu:" << rategg2e2mu << endl;

//bkg 2 gg to 4e
    bkg2->Draw(Discriminant,cutting66);
    float rategg4e = h1->Integral()*normBkg2;

    cout << "Bkg rate gg -> 4e:" << rategg4e << endl;

//bkg3 gg to 4mu
    bkg3 ->Draw(Discriminant,cutting66);
    float rategg4mu = h1->Integral()*normBkg3;  
  
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

//(no loop) find the rates (effsig=X , effbkg=Y)  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu (only needed in one sample) 

    sig->Draw(Discriminant,cutting2e2mu66); 
    float rate2e2mu = h1->Integral()*normSig;

    sig->Draw(Discriminant_JeCUp,cutting2e2muUp); 
    float rate2e2muUp = h1->Integral()*normSig;

    sig->Draw(Discriminant_JeCDn,cutting2e2muDn); 
    float rate2e2muDn = h1->Integral()*normSig;
    
    cout << "Signal rate 2e2mu: " << rate2e2mu << endl;
    cout << "Signal rate 2e2muUp: " << rate2e2muUp << endl; 
    cout << "Signal rate 2e2muDn: " << rate2e2muDn << endl; 
    
    float DeltaSig2e2mu = (rate2e2muUp -rate2e2mu)/rate2e2mu;
    cout << "Delta S (2e2mu) [UP]" << DeltaSig2e2mu << endl; 
    float DeltaSig2e2muDn = abs((rate2e2muDn -rate2e2mu)/rate2e2mu);
    cout << "Delta S (2e2mu) [Dn]" << DeltaSig2e2muDn << endl; 

    cout << "Delta S (2e2mu) [Average]" << (DeltaSig2e2mu + DeltaSig2e2muDn)/2. << endl;
    
    sig->Draw(Discriminant,cutting4e66);
    float rate4e = h1->Integral()*normSig;
    
    sig->Draw(Discriminant_JeCUp,cutting4eUp);
    float rate4eUp = h1->Integral()*normSig;

    sig->Draw(Discriminant_JeCDn,cutting4eDn);
    float rate4eDn = h1->Integral()*normSig;

    
    cout << "Signal rate 4e:" << rate4e << endl;
    cout << "Signal rate 4eUp: " << rate4eUp << endl;
    cout << "Signal rate 4eDn: " << rate4eDn << endl;

    float DeltaSig4e = (rate4eUp -rate4e)/rate4e;
    cout << "Delta S (4e) [UP]" << DeltaSig4e << endl; 
    float DeltaSig4eDn = abs((rate4eDn -rate4e)/rate4e);
    cout << "Delta S (4e) [Dn]" << DeltaSig4eDn << endl; 

    cout << "Delta S (4e) [Average]" << (DeltaSig4e + DeltaSig4eDn)/2. << endl;      
    
    sig->Draw(Discriminant,cutting4mu66);
    float rate4mu =  h1->Integral()*normSig;
    
    sig->Draw(Discriminant_JeCUp,cutting4muUp);
    float rate4muUp =  h1 ->Integral()*normSig;

     sig->Draw(Discriminant_JeCDn,cutting4muDn);
    float rate4muDn =  h1->Integral()*normSig;

    cout << "Signal rate 4mu: " << rate4mu << endl;  
    cout << "Signal rate 4muUp: " << rate4muUp << endl;
    cout << "Signal rate 4muDn: " << rate4muDn << endl;

    float DeltaSig4mu = (rate4muUp -rate4mu)/rate4mu;
    cout << "Delta S (4mu) [UP]" << DeltaSig4mu << endl; 
    float DeltaSig4muDn = abs((rate4muDn -rate4mu)/rate4mu);
    cout << "Delta S (4mu) [Dn]" << DeltaSig4muDn << endl; 

    cout << "Delta S (4mu) [Average]" << (DeltaSig4mu + DeltaSig4muDn)/2. << endl;

    bkg->Draw(Discriminant,cutting4e66);
    float ratebkgZZ4e = h1->Integral()*normbkg;
     
    bkg->Draw(Discriminant_JeCUp,cutting4eUp);
    float ratebkgZZ4eUp = h1->Integral()*normbkg;

    bkg->Draw(Discriminant_JeCDn,cutting4eDn);
    float ratebkgZZ4eDn = h1->Integral()*normbkg;

    cout << "Bkg rate ZZ -> 4e:" << ratebkgZZ4e << endl; 
    //cout << bkg->Scan("GenLep1Id:GenLep2Id:GenLep3Id:GenLep4Id") << endl;
    cout << "Bkg rate ZZ -> 4e Up:" << ratebkgZZ4eUp << endl;	
    cout << "Bkg rate ZZ -> 4e Dn:" << ratebkgZZ4eDn << endl;	
   

    float DeltaBkgZZto4e = (ratebkgZZ4eUp - ratebkgZZ4e)/ratebkgZZ4e;
    cout << "Delta Bkg ZZ (4e) [UP]" << DeltaBkgZZto4e << endl; 
    float DeltaBkgZZto4eDn = abs((ratebkgZZ4eDn - ratebkgZZ4e)/ratebkgZZ4e);
    cout << "Delta Bkg ZZ (4e) [Dn]" << DeltaBkgZZto4eDn << endl; 

    cout << "Delta Bkg ZZ (4e) [Average]" << (DeltaBkgZZto4e + DeltaBkgZZto4eDn)/2. << endl;

    bkg->Draw(Discriminant,cutting4mu66);
    float ratebkgZZ4mu = h1->Integral()*normbkg;
    
    bkg->Draw(Discriminant_JeCUp,cutting4muUp);
    float ratebkgZZ4muUp = h1->Integral()*normbkg;

    bkg->Draw(Discriminant_JeCDn,cutting4muDn);
    float ratebkgZZ4muDn = h1->Integral()*normbkg;
   
    cout << "Bkg rate ZZ -> 4mu:" << ratebkgZZ4mu << endl;
    cout << "Bkg rate ZZ -> 4mu Up: " << ratebkgZZ4muUp << endl;
    cout << "Bkg rate ZZ -> 4mu Dn: " << ratebkgZZ4muDn << endl;

    float DeltaBkgZZto4mu = (ratebkgZZ4muUp - ratebkgZZ4mu)/ratebkgZZ4mu;
    cout << "Delta Bkg ZZ (4mu) [UP]" << DeltaBkgZZto4mu << endl; 
    float DeltaBkgZZto4muDn = abs((ratebkgZZ4muDn - ratebkgZZ4mu)/ratebkgZZ4mu);
    cout << "Delta Bkg ZZ (4mu) [Dn]" << DeltaBkgZZto4muDn << endl; 
    
    cout << "Delta Bkg ZZ (4mu) [Average]" << (DeltaBkgZZto4mu + DeltaBkgZZto4muDn)/2. << endl;

    bkg->Draw(Discriminant,cutting2e2mu66);
    float ratebkgZZ2e2mu = h1->Integral()*normbkg;

    bkg->Draw(Discriminant_JeCUp,cutting2e2muUp);
    float ratebkgZZ2e2muUp = h1->Integral()*normbkg;
  
    bkg->Draw(Discriminant_JeCDn,cutting2e2muDn);
    float ratebkgZZ2e2muDn = h1->Integral()*normbkg;
  
    cout << "Bkg rate ZZ -> 2e2mu:" << ratebkgZZ2e2mu << endl;
    cout << "Bkg rate ZZ -> 2e2mu Up:" << ratebkgZZ2e2muUp << endl;
    cout << "Bkg rate ZZ -> 2e2mu Dn:" << ratebkgZZ2e2muDn << endl;
 

    float DeltaBkgZZto2e2mu = (ratebkgZZ2e2muUp - ratebkgZZ2e2mu)/ratebkgZZ2e2mu;
    cout << "Delta Bkg ZZ (2e2mu) [UP]" << DeltaBkgZZto2e2mu << endl; 
    float DeltaBkgZZto2e2muDn = abs((ratebkgZZ2e2muDn - ratebkgZZ2e2mu)/ratebkgZZ2e2mu);
    cout << "Delta Bkg ZZ (2e2mu) [Dn]" << DeltaBkgZZto2e2muDn << endl;

    cout << "Delta Bkg ZZ (2e2mu) [Average]" << (DeltaBkgZZto2e2mu + DeltaBkgZZto2e2muDn)/2. << endl;

//bkg1 -> gg to 2e2mu
    bkg1->Draw(Discriminant,cutting66);
    float rategg2e2mu = h1->Integral()*normBkg1;

    bkg1->Draw(Discriminant_JeCUp,cuttingUp);
    float rategg2e2muUp = h1->Integral()*normBkg1;

    bkg1->Draw(Discriminant_JeCDn,cuttingDn);
    float rategg2e2muDn = h1->Integral()*normBkg1;

    cout << "Bkg rate gg -> 2e2mu:" << rategg2e2mu << endl;
    cout << "Bkg rate gg -> 2e2mu Up:" << rategg2e2muUp << endl;
    cout << "Bkg rate gg -> 2e2mu Dn:" << rategg2e2muDn << endl;
    
    float DeltaBkgGGto2e2mu = (rategg2e2muUp - rategg2e2mu)/rategg2e2mu;
    cout << "Delta Bkg gg (2e2mu) [UP]" << DeltaBkgGGto2e2mu << endl; 
    float DeltaBkgGGto2e2muDn = abs((rategg2e2muDn - rategg2e2mu)/rategg2e2mu);
    cout << "Delta Bkg gg (2e2mu) [Dn]" << DeltaBkgGGto2e2muDn << endl; 

    cout << "Delta Bkg gg (2e2mu) [Average]" << (DeltaBkgGGto2e2mu + DeltaBkgGGto2e2muDn)/2. << endl;

//bkg 2 gg to 4e
    bkg2->Draw(Discriminant,cutting66);
    float rategg4e = h1->Integral()*normBkg2;

    bkg2->Draw(Discriminant_JeCUp,cuttingUp);
    float rategg4eUp = h1->Integral()*normBkg2;

    bkg2->Draw(Discriminant_JeCDn,cuttingDn);
    float rategg4eDn = h1->Integral()*normBkg2;

    cout << "Bkg rate gg -> 4e:" << rategg4e << endl;
    cout << "Bkg rate gg -> 4e Up:" << rategg4eUp << endl;
    cout << "Bkg rate gg -> 4e Dn:" << rategg4eDn << endl;
    
    float DeltaBkgGGto4e = (rategg4eUp - rategg4e)/rategg4e;
    cout << "Delta Bkg gg (4e) [UP]" << DeltaBkgGGto4e << endl; 
    float DeltaBkgGGto4eDn = abs((rategg4eDn - rategg4e)/rategg4e);
    cout << "Delta Bkg gg (4e) [Dn]" << DeltaBkgGGto4eDn << endl; 

    cout << "Delta Bkg gg (4e) [Average]" << (DeltaBkgGGto4e + DeltaBkgGGto4eDn)/2. << endl;


//bkg3 gg to 4mu
    bkg3 ->Draw(Discriminant,cutting66);
    float rategg4mu = h1->Integral()*normBkg3;

    bkg3 ->Draw(Discriminant_JeCUp,cuttingUp);
    float rategg4muUp = h1->Integral()*normBkg3;	

    bkg3 ->Draw(Discriminant_JeCDn,cuttingDn);
    float rategg4muDn = h1->Integral()*normBkg3;	
   
    cout << "Bkg rate gg -> 4mu:" << rategg4mu << endl;
    cout << "Bkg rate gg -> 4mu Up:" << rategg4muUp << endl;
    cout << "Bkg rate gg -> 4mu Dn:" << rategg4muDn << endl;
    
    float DeltaBkgGGto4mu = (rategg4muUp - rategg4mu)/rategg4mu;
    cout << "Delta Bkg gg (4mu) [UP]" << DeltaBkgGGto4mu << endl;
    float DeltaBkgGGto4muDn = abs((rategg4muDn - rategg4mu)/rategg4mu);
    cout << "Delta Bkg gg (4mu) [Dn]" << DeltaBkgGGto4muDn << endl;
    
    cout << "Delta Bkg gg (4mu) [Average]" << (DeltaBkgGGto4mu + DeltaBkgGGto4muDn)/2. << endl;


return;

}




void getBkgStat() {

//Find the real number of events.  OBS the cuts here are: mjj > 100, Zs on shell, 
//MELA discriminant > 0.66 and then an extra cut to separate eeee, 2e2mu, mumumumu

    sig->Draw(Discriminant,cutting2e2mu66); 

    float Nsig2e2mu = h1->Integral();
    cout << "Signal events 2e2mu:" << Nsig2e2mu << endl;
    
    float err2e2mu = 1/sqrt(Nsig2e2mu);
    cout << "Signal error 2e2mu: " << err2e2mu << endl;

    
    sig->Draw(Discriminant,cutting4e66);
    
    float Nsig4e = h1->Integral();
    cout << "Signal events 4e: " << Nsig4e << endl;
    
    float err4e = 1/sqrt(Nsig4e);
    cout << "Signal error 4e: " << err4e << endl;

    
    sig->Draw(Discriminant,cutting4mu66);
    
    float Nsig4mu = h1->Integral();
    cout << "Signal events 4mu:" << Nsig4mu << endl;
    
    float err4mu = 1/sqrt(Nsig4mu);
    cout << "Signal error 4mu: " << err4mu << endl; 

    bkg->Draw(Discriminant,cutting4e66);
    
    float NbkgZZto4e = h1->Integral();
    cout << "ZZ Bkg events 4e: " << NbkgZZto4e << endl;
    
    float errZZto4e = 1/sqrt(NbkgZZto4e);
    cout << "ZZ bkg error 4e: " << errZZto4e << endl;	

    bkg->Draw(Discriminant,cutting4mu66);
    
    float NbkgZZto4mu = h1->Integral();
    cout << "ZZ Bkg events 4mu: " << NbkgZZto4mu << endl;
    
    float errZZto4mu = 1/sqrt(NbkgZZto4mu);
    cout << "ZZ bkg error 4mu: " << errZZto4mu << endl;
    
    bkg->Draw(Discriminant,cutting2e2mu66);
    
    float NbkgZZto2e2mu = h1->Integral();
    cout << "ZZ Bkg events 2e2mu: " << NbkgZZto2e2mu << endl;
    
    float errZZto2e2mu = 1/sqrt(NbkgZZto2e2mu);
    cout << "ZZ bkg error 2e2mu: " << errZZto2e2mu << endl;

//bkg1 -> gg to 2e2mu
    bkg1->Draw(Discriminant,cutting66);
    
    float NbkgGGto2e2mu = h1->Integral();
    cout << "GG Bkg events 2e2mu: " << NbkgGGto2e2mu << endl;
    
    float errGGto2e2mu = 1/sqrt(NbkgGGto2e2mu);
    cout << "GG bkg error 2e2mu: " << errGGto2e2mu << endl;

//bkg 2 gg to 4e
    bkg2->Draw(Discriminant,cutting66);
    
    float NbkgGGto4e = h1->Integral();
    cout << "GG Bkg events 4e: " << NbkgGGto4e << endl;
    
    float errGGto4e = 1/sqrt(NbkgGGto4e);
    cout << "GG bkg error 4e: " << errGGto4e << endl;

//bkg3 gg to 4mu
    bkg3 ->Draw(Discriminant,cutting66);
    
    float NbkgGGto4mu = h1->Integral();
    cout << "GG Bkg events 4mu: " << NbkgGGto4mu << endl;
    
    float errGGto4mu = 1/sqrt(NbkgGGto4mu);
    cout << "GG bkg error 4mu: " << errGGto4mu << endl;

return;

}


void SetCuts(){

//char cuttingCandC[400];
sprintf(cuttingCandC,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && abs(DiJetDEta) > 2.5 && DiJetMass > 400. ");
//char cutting[400];
sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. ");

//char cutting66[400];
sprintf(cutting66,"(nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66)");
//char cutting4e66[400];
sprintf(cutting4e66,"(nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -121 && Z2Flav == -121))");
//char cutting4mu66[400];
sprintf(cutting4mu66,"(nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && (Z1Flav == -169 && Z2Flav == -169))");
//char cutting2e2mu66[400];
sprintf(cutting2e2mu66,"(nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.2*p_JJQCD_BKG_MCFM_JECNominal) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169)))");

sprintf(cuttingUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66");

sprintf(cutting4eUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4muUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2muUp,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECUp/(p_JJVBF_BKG_MCFM_JECUp+0.2*p_JJQCD_BKG_MCFM_JECUp) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");

sprintf(cuttingDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66");

sprintf(cutting4eDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && (Z1Flav == -121 && Z2Flav == -121)");

sprintf(cutting4muDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && (Z1Flav == -169 && Z2Flav == -169)");

sprintf(cutting2e2muDn,"nCleanedJetsPt30_jecDn > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. && p_JJVBF_BKG_MCFM_JECDn/(p_JJVBF_BKG_MCFM_JECDn+0.2*p_JJQCD_BKG_MCFM_JECDn) > 0.66 && ((Z1Flav == -169 && Z2Flav == -121) || (Z1Flav == -121 && Z2Flav == -169))");


return;
}



void SetCutsScale(int n){

SetCuts();

char scale[9][400] ={"*LHEweight_QCDscale_muR1_muF1", "*LHEweight_QCDscale_muR1_muF2","*LHEweight_QCDscale_muR1_muF0p5", "*LHEweight_QCDscale_muR2_muF1",  "*LHEweight_QCDscale_muR2_muF2",  "*LHEweight_QCDscale_muR2_muF0p5", "*LHEweight_QCDscale_muR0p5_muF1", "*LHEweight_QCDscale_muR0p5_muF2", "*LHEweight_QCDscale_muR0p5_muF0p5"};


//strncat(cutting66, scale[n], 100);
strncat(cutting4e66, scale[n], 100);
strncat(cutting4mu66, scale[n], 100);
strncat(cutting2e2mu66, scale[n], 100);

/*
strcpy(cutting66, str2[0].c_str());
strcpy(cutting4e66, str2[1].c_str());
strcpy(cutting4mu66, str2[2].c_str());
strcpy(cutting2e2mu66, str2[3].c_str());

cout << cutting66 << endl;
cout << cutting4e66 << endl;
cout << cutting4mu66 << endl;
cout << cutting2e2mu66 << endl;
*/

return;
}


void SetCutsPDF(int n){

SetCuts();

char scale[5][400] ={" ","*LHEweight_PDFVariation_Up","*LHEweight_PDFVariation_Dn", "*LHEweight_AsMZ_Up","*LHEweight_AsMZ_Dn"}; //We leave an empty one for the normalization

//strncat(cutting66, scale[n], 100);
strncat(cutting4e66, scale[n], 100);
strncat(cutting4mu66, scale[n], 100);
strncat(cutting2e2mu66, scale[n], 100);

/*
strcpy(cutting66, str2[0].c_str());
strcpy(cutting4e66, str2[1].c_str());
strcpy(cutting4mu66, str2[2].c_str());
strcpy(cutting2e2mu66, str2[3].c_str());

cout << cutting66 << endl;
cout << cutting4e66 << endl;
cout << cutting4mu66 << endl;
cout << cutting2e2mu66 << endl;
*/

return;
}



void scaleVariations(){

float sigVar2e2mu[9];
float sigVar4e[9];
float sigVar4mu[9];
float BkgZZVar2e2mu[9];
float BkgZZVar4e[9];
float BkgZZVar4mu[9];
float BkgGGVar2e2mu[9];
float BkgGGVar4e[9];
float BkgGGVar4mu[9];


//LHEweight_QCDscale_muR1_muF1 is the trivial one 
for (int i=0; i < 9; i++){

SetCutsScale(i);


cout << "cutting =  " << cutting2e2mu66 << endl;


    sig->Draw(Discriminant, cutting2e2mu66); 

    sigVar2e2mu[i] = h1->Integral();
    cout << "Signal variation 2e2mu: " << sigVar2e2mu[i] << endl;

    
    sig->Draw(Discriminant,cutting4e66);
    
    sigVar4e[i] = h1->Integral();
    cout << "Signal variation 4e : " << sigVar4e[i] << endl;
    
 
    sig->Draw(Discriminant,cutting4mu66);
    
    sigVar4mu[i] = h1->Integral();
    cout << "Signal variation 4mu:" << sigVar4mu[i] << endl;
    

    bkg->Draw(Discriminant,cutting4e66);
    
    BkgZZVar4e[i] = h1->Integral();
    cout << "ZZ Bkg variation 4e: " << BkgZZVar4e[i] << endl;
    	

    bkg->Draw(Discriminant,cutting4mu66);
    
    BkgZZVar4mu[i] = h1->Integral();
    cout << "ZZ Bkg variation 4mu: " << BkgZZVar4mu[i] << endl;
    

    
    bkg->Draw(Discriminant,cutting2e2mu66);
    
    BkgZZVar2e2mu[i] = h1->Integral();
    cout << "ZZ Bkg variation 2e2mu: " << BkgZZVar2e2mu[i] << endl;
    

//bkg1 -> gg to 2e2mu
    bkg1->Draw(Discriminant,cutting66);
    
    BkgGGVar2e2mu[i] = h1->Integral();
    cout << "GG Bkg variation 2e2mu: " << BkgGGVar2e2mu[i] << endl;

//bkg 2 gg to 4e
    bkg2->Draw(Discriminant,cutting66);
    
    BkgGGVar4e[i] = h1->Integral();
    cout << "GG Bkg variation 4e: " << BkgGGVar4e[i] << endl;

//bkg3 gg to 4mu
    bkg3 ->Draw(Discriminant,cutting66);
    
    BkgGGVar4mu[i] = h1->Integral();
    cout << "GG Bkg variation 4mu: " << BkgGGVar4mu[i] << endl;

} //end of for



cout << "Find the maximum variations: " << endl;
float max2e2mu = 0;
float max4e = 0;
float max4mu = 0;
float tmp1,tmp2,tmp3;

//Signal
for (int i=1; i<9 ; i++){
tmp1 = abs(sigVar2e2mu[i]-sigVar2e2mu[0])/sigVar2e2mu[0];
tmp2 = abs(sigVar4e[i]-sigVar4e[0])/sigVar4e[0];
tmp3 = abs(sigVar4mu[i]-sigVar4mu[0])/sigVar4mu[0];


if (tmp1 >= max2e2mu){
max2e2mu = tmp1;
}

if (tmp2 >= max4e){
max4e = tmp2;
}

if (tmp3 >= max4mu){
max4mu = tmp3;
}

}

cout << "max Signal variations: " << endl;
cout << "2e2mu: " << max2e2mu << endl;
cout << "4e: " << max4e << endl;
cout << "4mu: " << max4mu << endl;


// ZZ Background
max2e2mu = 0;
max4e = 0;
max4mu = 0;



for (int i=1; i<9 ; i++){
tmp1 = abs(BkgZZVar2e2mu[i]-BkgZZVar2e2mu[0])/BkgZZVar2e2mu[0];
tmp2 = abs(BkgZZVar4e[i]-BkgZZVar4e[0])/BkgZZVar4e[0];
tmp3 = abs(BkgZZVar4mu[i]-BkgZZVar4mu[0])/BkgZZVar4mu[0];

cout << "tmp1 = " << tmp1 << endl; 

if (tmp1 >= max2e2mu){
max2e2mu = tmp1;
}

if (tmp2 >= max4e){
max4e = tmp2;
}

if (tmp3 >= max4mu){
max4mu = tmp3;
}

}

cout << "max ZZ Bkg. variations: " << endl;
cout << "2e2mu: " << max2e2mu << endl;
cout << "4e: " << max4e << endl;
cout << "4mu: " << max4mu << endl;


// GG Background
max2e2mu = 0;
max4e = 0;
max4mu = 0;

for (int i=1; i<9 ; i++){
tmp1 = abs(BkgGGVar2e2mu[i]-BkgGGVar2e2mu[0])/BkgGGVar2e2mu[0];
tmp2 = abs(BkgGGVar4e[i]-BkgGGVar4e[0])/BkgGGVar4e[0];
tmp3 = abs(BkgGGVar4mu[i]-BkgGGVar4mu[0])/BkgGGVar4mu[0];

if (tmp1 >= max2e2mu){
max2e2mu = tmp1;
}

if (tmp2 >= max4e){
max4e = tmp2;
}

if (tmp3 >= max4mu){
max4mu = tmp3;
}

}

cout << "max GG Bkg. variations: " << endl;
cout << "2e2mu: " << max2e2mu << endl;
cout << "4e: " << max4e << endl;
cout << "4mu: " << max4mu << endl;



return;
}



void PDFVariations(){

float sigVar2e2mu[9];
float sigVar4e[9];
float sigVar4mu[9];
float BkgZZVar2e2mu[9];
float BkgZZVar4e[9];
float BkgZZVar4mu[9];
float BkgGGVar2e2mu[9];
float BkgGGVar4e[9];
float BkgGGVar4mu[9];


//LHEweight_QCDscale_muR1_muF1 is the trivial one 
for (int i=0; i < 5; i++){

SetCutsPDF(i);


cout << "cutting =  " << cutting2e2mu66 << endl;


    sig->Draw(Discriminant, cutting2e2mu66); 

    sigVar2e2mu[i] = h1->Integral();
    cout << "Signal variation 2e2mu: " << sigVar2e2mu[i] << endl;

    
    sig->Draw(Discriminant,cutting4e66);
    
    sigVar4e[i] = h1->Integral();
    cout << "Signal variation 4e : " << sigVar4e[i] << endl;
    
 
    sig->Draw(Discriminant,cutting4mu66);
    
    sigVar4mu[i] = h1->Integral();
    cout << "Signal variation 4mu:" << sigVar4mu[i] << endl;
    

    bkg->Draw(Discriminant,cutting4e66);
    
    BkgZZVar4e[i] = h1->Integral();
    cout << "ZZ Bkg variation 4e: " << BkgZZVar4e[i] << endl;
    
    bkg->Draw(Discriminant,cutting4mu66);
    
    BkgZZVar4mu[i] = h1->Integral();
    cout << "ZZ Bkg variation 4mu: " << BkgZZVar4mu[i] << endl;

    bkg->Draw(Discriminant,cutting2e2mu66);
    
    BkgZZVar2e2mu[i] = h1->Integral();
    cout << "ZZ Bkg variation 2e2mu: " << BkgZZVar2e2mu[i] << endl;
    

//bkg1 -> gg to 2e2mu
    bkg1->Draw(Discriminant,cutting66);
    
    BkgGGVar2e2mu[i] = h1->Integral();
    cout << "GG Bkg variation 2e2mu: " << BkgGGVar2e2mu[i] << endl;
    

//bkg 2 gg to 4e
    bkg2->Draw(Discriminant,cutting66);
    
    BkgGGVar4e[i] = h1->Integral();
    cout << "GG Bkg variation 4e: " << BkgGGVar4e[i] << endl;
    
//bkg3 gg to 4mu
    bkg3 ->Draw(Discriminant,cutting66);
    
    BkgGGVar4mu[i] = h1->Integral();
    cout << "GG Bkg variation 4mu: " << BkgGGVar4mu[i] << endl;
    


} //end of for



cout << "Find the maximum variations: " << endl;
float max2e2mu,max4e,max4mu, tmp1,tmp2,tmp3;

//Signal
max2e2mu = 0;
max4e = 0;
max4mu = 0;
for (int i=1; i<5 ; i++){
tmp1 = abs((sigVar2e2mu[i]-sigVar2e2mu[0])/sigVar2e2mu[0]);
tmp2 = abs((sigVar4e[i]-sigVar4e[0])/sigVar4e[0]);
tmp3 = abs((sigVar4mu[i]-sigVar4mu[0])/sigVar4mu[0]);

if (tmp1 >= max2e2mu){
max2e2mu = tmp1;
}

if (tmp2 >= max4e){
max4e = tmp2;
}

if (tmp3 >= max4mu){
max4mu = tmp3;
}

}

cout << "max Signal variations: " << endl;
cout << "2e2mu: " << max2e2mu << endl;
cout << "4e: " << max4e << endl;
cout << "4mu: " << max4mu << endl;


// ZZ Background
max2e2mu = 0;
max4e = 0;
max4mu = 0;

for (int i=1; i<5 ; i++){
tmp1 = abs((BkgZZVar2e2mu[i]-BkgZZVar2e2mu[0])/BkgZZVar2e2mu[0]);
tmp2 = abs((BkgZZVar4e[i]-BkgZZVar4e[0])/BkgZZVar4e[0]);
tmp3 = abs((BkgZZVar4mu[i]-BkgZZVar4mu[0])/BkgZZVar4mu[0]);

if (tmp1 >= max2e2mu){
max2e2mu = tmp1;
}

if (tmp2 >= max4e){
max4e = tmp2;
}

if (tmp3 >= max4mu){
max4mu = tmp3;
}

}

cout << "max ZZ Bkg. variations: " << endl;
cout << "2e2mu: " << max2e2mu << endl;
cout << "4e: " << max4e << endl;
cout << "4mu: " << max4mu << endl;


// GG Background
max2e2mu = 0;
max4e = 0;
max4mu = 0;

for (int i=1; i<5 ; i++){
tmp1 = abs((BkgGGVar2e2mu[i]-BkgGGVar2e2mu[0])/BkgGGVar2e2mu[0]);
tmp2 = abs((BkgGGVar4e[i]-BkgGGVar4e[0])/BkgGGVar4e[0]);
tmp3 = abs((BkgGGVar4mu[i]-BkgGGVar4mu[0])/BkgGGVar4mu[0]);

if (tmp1 >= max2e2mu){
max2e2mu = tmp1;
}

if (tmp2 >= max4e){
max4e = tmp2;
}

if (tmp3 >= max4mu){
max4mu = tmp3;
}

}

cout << "max GG Bkg. variations: " << endl;
cout << "2e2mu: " << max2e2mu << endl;
cout << "4e: " << max4e << endl;
cout << "4mu: " << max4mu << endl;



return;
}


