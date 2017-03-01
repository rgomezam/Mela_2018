void plotSsuSpiuB() {
  
  TFile *f2 = TFile::Open("root://eoscms//eos/cms//store/user/covarell/vbsTrees/170109/ZZTo4l/ZZ4lAnalysis.root");
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
  float ssb[ncuts];
  float ssbkg[ncuts];	

  TH1F *h1 = new TH1F("h1","h1",100,0.,1.1);
  char cutting[400];

  for (int i=0; i<ncuts; i++) {
    cuts[i] = i*0.02;
    sprintf(cutting,"nCleanedJetsPt30 > 1 && Z1Mass > 60. && Z1Mass < 120. && Z2Mass > 60. && Z2Mass < 120. && p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) > %f",cuts[i]);
    
    sig->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    float effsig = h1->Integral()*norms/5000.;

    sigee->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig += h1->Integral()*normsss/11200.;
    sigmm->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.05*p_JJQCD_BKG_MCFM_JECNominal) >> h1",cutting);
    effsig += h1->Integral()*normsss/10400.;
    cout << "### Cut at " << cuts[i] << " : pass sig = " << h1->Integral() << " eff sig = " << effsig << endl;
 
    bkg->Draw("p_JJVBF_BKG_MCFM_JECNominal/(p_JJVBF_BKG_MCFM_JECNominal+0.5*p_JJQCD_BKG_MCFM_JECNominal)>> h1",cutting); //Trial and error....
    float effbkg = h1->Integral()*normb/5957960.;
    cout << "### Cut at " << cuts[i] << " : pass bkg = " << h1->Integral() << " eff bkg = " << effbkg << endl;
    ssb[i] = effsig/sqrt(effsig*effsig+effbkg*effbkg); //Why sqroot in the den? 
    ssbkg[i]= effsig/sqrt(effsig*effsig+effbkg*effbkg); 
  }

 //TGraph* gr = new TGraph(ncuts,cuts,ssb);
  //gr->Draw("ALP*");


 TGraph* gr2 = new TGraph(ncuts,ssbkg,ssb);
 gr2->Draw("ALP*");
}

