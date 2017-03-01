#include <RooDataSet.h>


void melaNEW() {

  TFile *f2 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ZZTo4l/ZZ4lAnalysis.root");
// ZZTo4l xsec = 1.256 pb
  TTree *bkg = (TTree*)f2->Get("ZZTree/candTree");
  TH1F *h0 = (TH1F*)f2->Get("ZZTree/Counters");	
  

  TFile *f = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo2e2muJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
// VBFTo2e2muJJ_0PMH125Contin_phantom128 xsec = 8.375E-04 pb
  TTree *sig = (TTree*)f->Get("ZZTree/candTree");
  TH1F *h2 = (TH1F*)f->Get("ZZTree/Counters");

  TFile *f3 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo4eJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
//VBFTo4eJJ_0PMH125Contin_phantom128 xsec= 4.180E-04 pb  
  TTree *sigee = (TTree*)f3->Get("ZZTree/candTree");
  TH1F *h3 = (TH1F*)f3->Get("ZZTree/Counters");

  TFile *f4 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo4muJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
//VBFTo4muJJ_0PMH125Contin_phantom128 xsec= 4.180E-04 pb
  TTree *sigmm = (TTree*)f4->Get("ZZTree/candTree");
  TH1F *h4 = (TH1F*)f4->Get("ZZTree/Counters");

  TFile *f5 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ggTo2e2mu_Contin_MCFM701/ZZ4lAnalysis.root");
//  ggTo2e2mu xsec = 0.0031942 pb
  TTree *bkg1 = (TTree*)f5->Get("ZZTree/candTree");
  TH1F *h5 = (TH1F*)f5->Get("ZZTree/Counters");

  TFile *f6 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ggTo4e_Contin_MCFM701/ZZ4lAnalysis.root");
//  ggTo4e  xsec = 0.00158549 pb
  TTree *bkg2 = (TTree*)f6 ->Get("ZZTree/candTree");
  TH1F *h6 = (TH1F*)f6->Get("ZZTree/Counters");


  TFile *f7 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ggTo4mu_Contin_MCFM701/ZZ4lAnalysis.root");
//  ggTo4mu xsec = 0.00158549 pb
  TTree *bkg3 = (TTree*)f7 ->Get("ZZTree/candTree");
  TH1F *h7 = (TH1F*)f7->Get("ZZTree/Counters");




  static const int ncuts = 50; 
  float cuts[ncuts];

  float NgenBKG = h0->GetBinContent(1);
  cout << "NgenBKG = " << NgenBKG << endl;
  
  float NgenSig = h2->GetBinContent(1);
  cout << "NgenSig 2e2mu = " << NgenSig << endl;  

  float NgenSig2 = h3->GetBinContent(1);
  cout << "NgenSig 4e = " << NgenSig2 << endl;

  float NgenSig3 = h4->GetBinContent(1);
  cout << "NgenSig 4mu = " << NgenSig3 << endl;
  
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
   float normbkg= Lumi*1.256/NgenBKG;
   float normSig2e2mu= Lumi*8.375E-04/NgenSig;
   float normSig4e= Lumi*4.180E-04/NgenSig2;
   float normSig4mu= Lumi*4.180E-04/NgenSig3;

   float normBkg1= Lumi*0.0031942/NgenBkg1;
   float normBkg2 = Lumi*0.00158549/NgenBkg2;
   float normBkg3 = Lumi*0.00158549/NgenBkg3;


   float X;
   float Y;
   float Xp[ncuts];
   float Yp[ncuts];

  TH1F *h1 = new TH1F("h1","h1",100,0.,1.1);
  char cutting[400];
  char cutting2[400];


// First (no loop) find the denominators (effsig=X , effbkg=Y)  OBS Here there is a cut on mjj is 100 (fiducial)

    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && DiJetMass > 100. ");
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting); 
    float effsig0 = h1->Integral()*normSig2e2mu;    

    sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig0 += h1->Integral()*normSig4e;
    
    
    sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig0 += h1->Integral()*normSig4mu;
    
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg0 = h1->Integral()*normbkg;

    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg2;

    bkg3 ->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg0 =+ h1->Integral()*normBkg3;	
  
    Y = effsig0;
    X = effbkg0;



// Second (loop) find the numerators (effsig=X , effbkg=Y)   
  for (int i=0; i<ncuts; i++) {
    cuts[i] = i*0.02;
    sprintf(cutting,"nCleanedJetsPt30 > 1 && DiJetMass > 100. && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > %f",cuts[i]);
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effsig = h1->Integral()*normSig2e2mu;
    
    
    sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig += h1->Integral()*normSig4e;
    
    
    sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig += h1->Integral()*normSig4mu;
    //cout << "### Cut at " << cuts[i] << " : pass sig = " << h1->Integral() << " eff sig = " << effsig << endl;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg = h1->Integral()*normbkg;
    //cout << "### Cut at " << cuts[i] << " : pass bkg = " << h1->Integral() << " eff bkg = " << effbkg << endl;
   
    bkg1->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg1;

    bkg2->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg2;

    bkg3->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effbkg =+ h1->Integral()*normBkg3;

    Yp[i] = effsig;
    Xp[i] = effbkg;
  }


float Seff[ncuts];
float Beff[ncuts];

for (int i=0; i<ncuts; i++) {
Beff[i]=Xp[i]/X;
Seff[i]=Yp[i]/Y;
}


//Third: find the point given by the cuts: 
   sprintf(cutting2,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && abs(DiJetDEta) > 2.5 && DiJetMass > 400. ");
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    float effsig2 = h1->Integral()*normSig2e2mu;
    
    
    sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effsig2 += h1->Integral()*normSig4e;
    
    
    sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effsig2 += h1->Integral()*normSig4mu;
    
    
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
   
    gr1->SetTitle("ROC curve");
    gr1->SetLineWidth(1);
    gr1->SetLineColor(2);
    gr1->GetXaxis()->SetLimits(-0.07,1.07);
    gr1->GetXaxis()->SetTitle("Background eff");
    gr1->GetYaxis()->SetTitle("Signal eff");
    gr1->SetMinimum(0.);
    gr1->SetMaximum(1.07);
       

    gr1->Draw("ALP");
    gr2->Draw("same");

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

