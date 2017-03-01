#include <RooDataSet.h>


void mela() {

  TFile *f2 = 
  TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ZZTo4l/ZZ4lAnalysis.root");
  TTree *bkg = (TTree*)f2->Get("ZZTree/candTree");
  TFile *f = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo2e2muJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
  TTree *sig = (TTree*)f->Get("ZZTree/candTree");
  TFile *f3 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo4eJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
  TTree *sigee = (TTree*)f3->Get("ZZTree/candTree");
  TFile *f4 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/VBFTo4muJJ_0PMH125Contin_phantom128/ZZ4lAnalysis.root");
  TTree *sigmm = (TTree*)f4->Get("ZZTree/candTree");

  static const int ncuts = 50; 
  float cuts[ncuts];
  float norms = 30.08;
  float normsss = 15.05;
  float normb = 45216.;
  //float ssb[ncuts];
   float X;
   float Y;
   float Xp[ncuts];
   float Yp[ncuts];

  TH1F *h1 = new TH1F("h1","h1",100,0.,1.1);
  char cutting[400];
  char cutting2[400];


// First (no loop) find the denominators (effsig=X , effbkg=Y) 

    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120.");
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting); 

float effsig0 = h1->Integral()*norms/5000;    
sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig0 += h1->Integral()*normsss/11200.;
    
    
sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig0 += h1->Integral()*normsss/10400.;
    
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg0 = h1->Integral()*normb/5957960.;
  
    Y = effsig0;
    X = effbkg0;



// Second (loop) find the numerators (effsig=X , effbkg=Y) 
  for (int i=0; i<ncuts; i++) {
    cuts[i] = i*0.02;
    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > %f",cuts[i]);
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effsig = h1->Integral()*norms/5000;
    
    
sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig += h1->Integral()*normsss/11200.;
    
    
sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig += h1->Integral()*normsss/10400.;
    //cout << "### Cut at " << cuts[i] << " : pass sig = " << h1->Integral() << " eff sig = " << effsig << endl;
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effbkg = h1->Integral()*normb/5957960.;
    //cout << "### Cut at " << cuts[i] << " : pass bkg = " << h1->Integral() << " eff bkg = " << effbkg << endl;
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
    float effsig2 = h1->Integral()*norms/5000;
    
    
sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effsig2 += h1->Integral()*normsss/11200.;
    
    
sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    effsig2 += h1->Integral()*normsss/10400.;
    
    
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting2);
    float effbkg2 = h1->Integral()*normb/5957960.;
  
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
cout << "distance X" << abs(Beff[i]-X2) << endl;
if (abs(Beff[i]-X2)< distX){
distX=abs(Beff[i]-X2);
minX=i;
cout << "Closest x is" << i << endl;
}
cout << "distance Y" << abs(Seff[i]-Y2) << endl;
if (abs(Seff[i]-Y2)< distY){
distY=abs(Seff[i]-Y2);
minY=i;
cout << "Closest y is" << i << endl;
}

}

epsilonX= abs(Beff[minY]-X2); 
cout << "EpsilonX: " << epsilonX << endl;
epsilonY=abs(Seff[minX]-Y2);
cout << "EpsilonY: " << epsilonY << endl; 

}

