#include "analysis_3dst.hxx"

void MCMC::beauty(){
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat("");

  gStyle->SetLabelFont(102,"");
  gStyle->SetLabelSize(0.06,"");
  gStyle->SetLabelFont(102,"xyz");
  gStyle->SetLabelSize(0.04,"xyz");
  gStyle->SetLabelOffset(0.001,"x");
  gStyle->SetLabelOffset(0.01,"y");

  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleSize(0.06,"xyz");
  gStyle->SetTitleOffset(0.9,"x");
  gStyle->SetTitleOffset(0.9,"y");

  gStyle->SetStripDecimals(kFALSE);

  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);

  gStyle->SetStatW(0.35);
  gStyle->SetStatH(0.25);

  gStyle->SetPadTickX(kTRUE);
  gStyle->SetPadTickY(kTRUE);

  gStyle->SetPalette(1);
  gStyle->SetNumberContours(99);

  gStyle->SetHistLineWidth(2);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFuncWidth(2);

  gStyle->SetStatFont(42);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0000);
}

void MCMC::process_Ar(){

  TH1D* h1_nuwro_reco = new TH1D("","",100,-1,1);

  h2_trueE_trueY_nominal = new TH2D("h2_trueE_trueY_nominal","h2_trueE_trueY_nominal_Ar", 20, 0, 5, 20, 0, 1);
  h2_recoE_recoY_nominal = new TH2D("h2_recoE_recoY_nominal","h2_recoE_recoY_nominal_Ar", 20, 0, 5, 20, 0, 1);
  h2_nuwro_true = new TH2D("h2_nuwro_Ar","h2_nuwro_Ar", 20, 0, 5, 20, 0, 1);
  h2_Ar_diff = new TH2D("h2_Ar_diff","h2_Ar_diff", 20, 0, 5, 20, 0, 1);

  for(Int_t i=0;i<20;i++){
    h2_trueE_trueY_var[i] = new TH2D("","true", 20, 0, 5, 20, 0, 1);
    h2_recoE_recoY_var[i] = new TH2D("","reco", 20, 0, 5, 20, 0, 1);
  }

  h2_trueE_trueY_nominal_CH = new TH2D("h2_trueE_trueY_nominal_CH","h2_trueE_trueY_nominal_CH", 20, 0, 5, 20, 0, 1);
  h2_recoE_recoY_nominal_CH = new TH2D("h2_recoE_recoY_nominal_CH","h2_recoE_recoY_nominal_CH", 20, 0, 5, 20, 0, 1);
  h2_nuwro_true_CH = new TH2D("h2_nuwro_CH","h2_nuwro_CH", 20, 0, 5, 20, 0, 1);
  h2_Ar_diff_CH = new TH2D("h2_CH_diff","h2_CH_diff", 20, 0, 5, 20, 0, 1);

  for(Int_t i=0;i<20;i++){
    h2_trueE_trueY_var_CH[i] = new TH2D("","true", 20, 0, 5, 20, 0, 1);
    h2_recoE_recoY_var_CH[i] = new TH2D("","reco", 20, 0, 5, 20, 0, 1);
  }

  TFile genie_Ar("genie/CAF_Ar.root");
  TFile genie_CH("genie/CAF_CH.root");
  TFile nuwro_Ar("nuwro/my_Ar_tracker.root");
  TFile nuwro_CH("nuwro/my_CH_tracker.root");

  genieAr = (TTree*)genie_Ar.Get("caf");
  genieCH = (TTree*)genie_CH.Get("caf");
  nuwroAr = (TTree*)nuwro_Ar.Get("nRooTracker");
  nuwroCH = (TTree*)nuwro_CH.Get("nRooTracker");


  genieAr->SetBranchAddress("Ev",&Ev);
  genieAr->SetBranchAddress("Y",&YY);
  genieAr->SetBranchAddress("Ev_reco",&Ev_reco);
  genieAr->SetBranchAddress("Elep_reco",&Elep_reco);
  genieAr->SetBranchAddress("eP",&eP);
  genieAr->SetBranchAddress("isFD",&isFD);
  genieAr->SetBranchAddress("isCC",&isCC);
  genieAr->SetBranchAddress("nuPDG",&nuPDG);
  genieAr->SetBranchAddress("LepPDG",&LepPDG);
  genieAr->SetBranchAddress("LepE",&LepE);
  genieAr->SetBranchAddress("eDepN",&eDepN);
  genieAr->SetBranchAddress("eDepP",&eDepP);
  genieAr->SetBranchAddress("eDepPip",&eDepPip);
  genieAr->SetBranchAddress("eDepPim",&eDepPim);
  genieAr->SetBranchAddress("eDepPi0",&eDepPi0);
  genieAr->SetBranchAddress("eDepOther",&eDepOther);

  genieAr->SetBranchAddress("wgt_MaCCRES",&wgt_MaCCRES);
  genieAr->SetBranchAddress("wgt_MvCCRES",&wgt_MvCCRES);
  genieAr->SetBranchAddress("wgt_AhtBY",&wgt_AhtBY);
  genieAr->SetBranchAddress("wgt_BhtBY",&wgt_BhtBY);
  genieAr->SetBranchAddress("wgt_CV1uBY",&wgt_CV1uBY);
  genieAr->SetBranchAddress("wgt_CV2uBY",&wgt_CV2uBY);
  genieAr->SetBranchAddress("wgt_C12ToAr40_2p2hScaling_nu",&wgt_C12ToAr40_2p2hScaling_nu);
  genieAr->SetBranchAddress("wgt_nuenuebar_xsec_ratio",&wgt_nuenuebar_xsec_ratio);
  genieAr->SetBranchAddress("wgt_SPPLowQ2Suppression",&wgt_SPPLowQ2Suppression);
  genieAr->SetBranchAddress("wgt_FSILikeEAvailSmearing",&wgt_FSILikeEAvailSmearing);

  genieAr->SetBranchAddress("wgt_E2p2h_A_nu",&wgt_E2p2h_A_nu);
  genieAr->SetBranchAddress("wgt_E2p2h_B_nu",&wgt_E2p2h_B_nu);
  genieAr->SetBranchAddress("wgt_E2p2h_A_nubar",&wgt_E2p2h_A_nubar);
  genieAr->SetBranchAddress("wgt_E2p2h_B_nubar",&wgt_E2p2h_B_nubar);
  genieAr->SetBranchAddress("wgt_Mnv2p2hGaussEnhancement",&wgt_Mnv2p2hGaussEnhancement);

  bool selected = false;

  int Nentries = 0;
  if(genieAr->GetEntries()> nuwroAr->GetEntries()) Nentries = nuwroAr->GetEntries();
  else Nentries = genieAr->GetEntries();

  for(Int_t i=0;i<Nentries; i++){
    genieAr->GetEntry(i);
    //cout<<Ev<<" "<<YY<<" "<<Ev_reco<<" "<<Elep_reco<<endl;
    if(isCC && nuPDG == 14 ) selected = true;
    else selected = false;

    if (selected){
      if(isFD) Ev_reco = LepE + eDepP + eDepN + eDepPip + eDepPim + eDepPi0 + eDepOther;

      h2_trueE_trueY_nominal->Fill(Ev, YY);
      h2_recoE_recoY_nominal->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco);

      h2_trueE_trueY_var[0]->Fill(Ev, YY, wgt_MvCCRES[2]);
      h2_recoE_recoY_var[0]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_MvCCRES[2]);

      h2_trueE_trueY_var[1]->Fill(Ev, YY, wgt_AhtBY[2]);
      h2_recoE_recoY_var[1]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_AhtBY[2]);

      h2_trueE_trueY_var[2]->Fill(Ev, YY, wgt_BhtBY[2]);
      h2_recoE_recoY_var[2]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_BhtBY[2]);

      h2_trueE_trueY_var[3]->Fill(Ev, YY, wgt_C12ToAr40_2p2hScaling_nu[2]);
      h2_recoE_recoY_var[3]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_C12ToAr40_2p2hScaling_nu[2]);  

      h2_trueE_trueY_var[4]->Fill(Ev, YY, wgt_SPPLowQ2Suppression[2]);
      h2_recoE_recoY_var[4]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_SPPLowQ2Suppression[2]);

      h2_trueE_trueY_var[5]->Fill(Ev, YY, wgt_FSILikeEAvailSmearing[2]);
      h2_recoE_recoY_var[5]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_FSILikeEAvailSmearing[2]);

      h2_trueE_trueY_var[6]->Fill(Ev, YY, wgt_nuenuebar_xsec_ratio[2]);
      h2_recoE_recoY_var[6]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_nuenuebar_xsec_ratio[2]);

      h2_trueE_trueY_var[7]->Fill(Ev, YY, wgt_E2p2h_A_nu[2]);
      h2_recoE_recoY_var[7]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_E2p2h_A_nu[2]);

      h2_trueE_trueY_var[8]->Fill(Ev, YY, wgt_E2p2h_B_nu[2]);
      h2_recoE_recoY_var[8]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_E2p2h_B_nu[2]);

      h2_trueE_trueY_var[9]->Fill(Ev, YY, wgt_Mnv2p2hGaussEnhancement[2]);
      h2_recoE_recoY_var[9]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_Mnv2p2hGaussEnhancement[2]);
    }
  }


  nuwroAr->SetBranchAddress("StdHepP4",&StdHepP4);
  nuwroAr->SetBranchAddress("StdHepPdg",&StdHepPdg);

  for(Int_t j=0; j< Nentries; j++){
    nuwroAr->GetEntry(j);	
    selected = false;
    pEnergy = 0;

    //cout<<StdHepPdg[3]<<endl;
    for(Int_t i=0;i<6;i++){
      if(StdHepPdg[i] == 14)
        nuE = StdHepP4[i][3];
      if(StdHepPdg[i] == 13){
        lepE = StdHepP4[i][3];
        selected = true;
      }
      if(i>1 && (StdHepPdg[i] == 2212 || StdHepPdg[i] == 2112)){
        pEnergy += StdHepP4[i][3];
      }  
    }
    nuE_reco = nuE - 0.2 * pEnergy;
    if (selected ){
      h2_nuwro_true->Fill(nuE_reco, (nuE_reco-lepE) / nuE_reco );
      h1_nuwro_reco -> Fill((nuE-nuE_reco)/ nuE);
      //cout<<nuE<<" "<<lepE<<endl;
    }  
  }

  new TCanvas();
  h1_nuwro_reco->GetXaxis()->SetTitle("(E_{true} - E_{reco}) / E_{true}");
  h1_nuwro_reco->GetYaxis()->SetTitle("Events ");
  h1_nuwro_reco->SetLineWidth(3);
  h1_nuwro_reco->Draw("");
}

void MCMC::MCMC_master(){

  double saveList[10]={};
  double currVec[10];
  //double propVec[10];
  double saveRes = 10000000;

  std::vector<double> _currList ;

  for(int i = 0 ; i < iterationTime ; i ++){
    std::cout<<"MCM step number " << i<<std::endl;
    for(int ii = 0; ii < 10; ii ++){
      currVec[ii] = saveList[ii];
      _currList.push_back( currVec[ii] + gRandom -> Gaus(0,3) ); 
    }
    double res = MCMC_processing(_currList);
    cout<<"result chi2 "<<res<<" "<<saveRes<<endl;
    if( res/saveRes < 1 ){ 
      for(int j = 0; j < 10; j ++){
        saveList[j] = _currList.at(j);
	saveRes = res;
        cout<<i<<" "<<saveList[j]<<" "<<saveRes<<endl;
      }
    }
    _currList.clear();
  }
  for(int j = 0; j < 10; j ++)
  cout<<saveList[j]<<endl;
  cout<<saveRes<<endl;

  finI = saveList[0];
  finJ = saveList[1];
  finK = saveList[2];
  finII = saveList[3];
  finJJ = saveList[4];
  finKK = saveList[5];
  finIII = saveList[6];
  finJJJ = saveList[7];
  finKKK = saveList[8];
  finIIII = saveList[9];

  for(Int_t iX =0; iX<h2_trueE_trueY_var[0]->GetNbinsX();iX++ ){
    for(Int_t iY =0; iY<h2_trueE_trueY_var[0]->GetNbinsY();iY++ ){
      if(h2_nuwro_true->GetBinContent(iX+1,iY+1)>0)
        h2_Ar_diff -> SetBinContent( iX+1, iY+1, 
          h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1) + 
          h2_trueE_trueY_var[0]->GetBinContent(iX+1,iY+1)*finI + 
          h2_trueE_trueY_var[1]->GetBinContent(iX+1,iY+1)*finJ + 
	  h2_trueE_trueY_var[2]->GetBinContent(iX+1,iY+1)*finK + 
	  h2_trueE_trueY_var[3]->GetBinContent(iX+1,iY+1)*finII + 
	  h2_trueE_trueY_var[4]->GetBinContent(iX+1,iY+1)*finJJ + 
	  h2_trueE_trueY_var[5]->GetBinContent(iX+1,iY+1)*finKK  + 
	  h2_trueE_trueY_var[6]->GetBinContent(iX+1,iY+1)*finIII + 
	  h2_trueE_trueY_var[7]->GetBinContent(iX+1,iY+1)*finJJJ + 
	  h2_trueE_trueY_var[8]->GetBinContent(iX+1,iY+1)*finKKK + 
	  h2_trueE_trueY_var[9]->GetBinContent(iX+1,iY+1)*finIIII - 
	  10 * h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1) - h2_nuwro_true->GetBinContent(iX+1,iY+1)) ;
    }
  }

  TCanvas* c1 = new TCanvas();
  c1->Divide(3,4);
  c1->cd(1);
  h2_trueE_trueY_nominal->GetXaxis()->SetTitle("True Ev (GeV)");
  h2_trueE_trueY_nominal->GetYaxis()->SetTitle("True Y ");
  h2_trueE_trueY_nominal->Draw("colz");
  c1->cd(2);
  h2_recoE_recoY_nominal->Draw("colz");
  h2_recoE_recoY_nominal->GetXaxis()->SetTitle("Reco. Ev (GeV)");
  h2_recoE_recoY_nominal->GetYaxis()->SetTitle("Reco. Y ");

  for(Int_t i=0;i<6;i++){
    c1->cd(2*i+3);
    h2_trueE_trueY_var[i]->Draw("colz");
    h2_trueE_trueY_var[i]->GetXaxis()->SetTitle("True Ev (GeV)");
    h2_trueE_trueY_var[i]->GetYaxis()->SetTitle("True Y ");

    c1->cd(2*i+4);
    h2_recoE_recoY_var[i]->Draw("colz");
    h2_recoE_recoY_var[i]->GetXaxis()->SetTitle("Reco. Ev (GeV)");
    h2_recoE_recoY_var[i]->GetYaxis()->SetTitle("Reco. Y ");

  }

  new TCanvas();
  h2_nuwro_true->Draw("colz");
  h2_nuwro_true->GetXaxis()->SetTitle("Reco. Ev (GeV)");
  h2_nuwro_true->GetYaxis()->SetTitle("Reco. Y ") ;

  new TCanvas();
  h2_Ar_diff->Draw("colz");
  h2_Ar_diff->SetTitle("Difference between nuwro and fitted genie on Ar");
  h2_Ar_diff->GetXaxis()->SetTitle("True Ev (GeV)");
  h2_Ar_diff->GetYaxis()->SetTitle("True Y ") ;
  h2_Ar_diff->GetZaxis()->SetRangeUser(-1000,1000);

}

double MCMC::MCMC_processing(std::vector<double> currList){

  double currI[10];
  for(int i=0;i<10;i++){ 
    currI[i]   = currList[i];
  }
  double acc = 0;
  for(Int_t iX =0; iX<h2_trueE_trueY_var[0]->GetNbinsX();iX++ ){
    for(Int_t iY =0; iY<h2_trueE_trueY_var[0]->GetNbinsY();iY++ ){
      if(h2_nuwro_true->GetBinContent(iX+1,iY+1)>0) acc +=
        TMath::Power(h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1) +
        (h2_trueE_trueY_var[0]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[0] +
        (h2_trueE_trueY_var[1]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[1] +
        (h2_trueE_trueY_var[2]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[2] +
        (h2_trueE_trueY_var[3]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[3] +
        (h2_trueE_trueY_var[4]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[4] +
        (h2_trueE_trueY_var[5]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[5] +
        (h2_trueE_trueY_var[6]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[6] +
        (h2_trueE_trueY_var[7]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[7] +
        (h2_trueE_trueY_var[8]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[8] +
        (h2_trueE_trueY_var[9]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal->GetBinContent(iX+1,iY+1))*currI[9] -
        h2_nuwro_true->GetBinContent(iX+1,iY+1),2) / h2_nuwro_true->GetBinContent(iX+1,iY+1) ;
    }
  }
  for(int i=0;i<9;i++)
    acc += currI[i]*currI[i];

  return acc;

}


///////////////////////////////////////////////////////////////////////////////////////////////////
//applying to CH
//
void MCMC::applyToCH(){

  for(Int_t i=0;i<10;i++){
    wgt_MaCCQE[i]=0;
    wgt_VecFFCCQEshape[i]=0; 
    wgt_MaCCRES[i]=0;
    wgt_MvCCRES[i]=0;
    wgt_AhtBY[i]=0;
    wgt_BhtBY[i]=0; 
    wgt_CV1uBY[i]=0;
    wgt_CV2uBY[i]=0;
    wgt_FrElas_pi[i]=0; 
    wgt_FtInel_pi[i]=0; 
    wgt_FrAbs_pi[i]=0; 
    wgt_FormZone[i]=0; 
    wgt_FrPiProd_pi[i]=0;
    wgt_MFP_N[i]=0; 
    wgt_FrCEx_N[i]=0; 
    wgt_CCQEEPauliSupViaKF[i]=0; 
    wgt_Mnv2p2hGaussEnhancement[i]=0; 
    wgt_MKSPP_ReWeight[i]=0;
    wgt_E2p2h_A_nu[i]=0;
    wgt_E2p2h_B_nu[i]=0;
    wgt_E2p2h_A_nubar[i]=0; 
    wgt_E2p2h_B_nubar[i]=0; 
    wgt_BePRA_A[i]=0; 
    wgt_BePRA_B[i]=0;
    wgt_BePRA_D[i]=0;
    wgt_BePRA_E[i]=0; 
    wgt_C12ToAr40_2p2hScaling_nu[i]=0;
    wgt_C12ToAr40_2p2hScaling_nubar[i]=0;
    wgt_nuenuebar_xsec_ratio[i]=0;  
    wgt_nuenumu_xsec_ratio[i]=0; 
    wgt_SPPLowQ2Suppression[i]=0; 
    wgt_FSILikeEAvailSmearing[i]=0;
  }

  Ev=0;
  YY=0;
  Ev_reco=0;
  Elep_reco=0; 
  eP=0;
  isFD=0;
  isCC=0; 
  nuPDG=0; 
  LepPDG=0;
  LepE=0; eDepP=0; eDepN=0; eDepPip=0; eDepPim=0; eDepPi0=0; eDepOther=0;

  genieCH->SetBranchAddress("Ev",&Ev_CH);
  genieCH->SetBranchAddress("Y",&YY_CH);
  genieCH->SetBranchAddress("Ev_reco",&Ev_reco);
  genieCH->SetBranchAddress("Elep_reco",&Elep_reco);
  genieCH->SetBranchAddress("eP",&eP);
  genieCH->SetBranchAddress("isFD",&isFD);
  genieCH->SetBranchAddress("isCC",&isCC);
  genieCH->SetBranchAddress("nuPDG",&nuPDG);
  genieCH->SetBranchAddress("LepPDG",&LepPDG);
  genieCH->SetBranchAddress("LepE",&LepE);
  genieCH->SetBranchAddress("eDepN",&eDepN);
  genieCH->SetBranchAddress("eDepP",&eDepP);
  genieCH->SetBranchAddress("eDepPip",&eDepPip);
  genieCH->SetBranchAddress("eDepPim",&eDepPim);
  genieCH->SetBranchAddress("eDepPi0",&eDepPi0);
  genieCH->SetBranchAddress("eDepOther",&eDepOther);

  genieCH->SetBranchAddress("wgt_MaCCRES",&wgt_MaCCRES);
  genieCH->SetBranchAddress("wgt_MvCCRES",&wgt_MvCCRES);
  genieCH->SetBranchAddress("wgt_AhtBY",&wgt_AhtBY);
  genieCH->SetBranchAddress("wgt_BhtBY",&wgt_BhtBY);
  genieCH->SetBranchAddress("wgt_CV1uBY",&wgt_CV1uBY);
  genieCH->SetBranchAddress("wgt_CV2uBY",&wgt_CV2uBY);
  genieCH->SetBranchAddress("wgt_C12ToAr40_2p2hScaling_nu",&wgt_C12ToAr40_2p2hScaling_nu);
  genieCH->SetBranchAddress("wgt_nuenuebar_xsec_ratio",&wgt_nuenuebar_xsec_ratio);
  genieCH->SetBranchAddress("wgt_SPPLowQ2Suppression",&wgt_SPPLowQ2Suppression);
  genieCH->SetBranchAddress("wgt_FSILikeEAvailSmearing",&wgt_FSILikeEAvailSmearing);

  genieCH->SetBranchAddress("wgt_E2p2h_A_nu",&wgt_E2p2h_A_nu);
  genieCH->SetBranchAddress("wgt_E2p2h_B_nu",&wgt_E2p2h_B_nu);
  genieCH->SetBranchAddress("wgt_E2p2h_A_nubar",&wgt_E2p2h_A_nubar);
  genieCH->SetBranchAddress("wgt_E2p2h_B_nubar",&wgt_E2p2h_B_nubar);
  genieCH->SetBranchAddress("wgt_Mnv2p2hGaussEnhancement",&wgt_Mnv2p2hGaussEnhancement);

  bool selected = false;

  int Nentries = 0;
  if(genieCH->GetEntries()> nuwroCH->GetEntries()) Nentries = nuwroCH->GetEntries();
  else Nentries = genieCH->GetEntries();

  for(Int_t i=0;i<Nentries; i++){
    genieCH->GetEntry(i);
    //cout<<Ev<<" "<<YY<<" "<<Ev_reco<<" "<<Elep_reco<<endl;
    if(isCC && nuPDG == 14 ) selected = true;
    else selected = false;

    if (selected){
      if(isFD) Ev_reco = LepE + eDepP + eDepN + eDepPip + eDepPim + eDepPi0 + eDepOther;

      h2_trueE_trueY_nominal_CH->Fill(Ev_CH, YY_CH);
      h2_recoE_recoY_nominal_CH->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco);

      h2_trueE_trueY_var_CH[0]->Fill(Ev_CH, YY_CH, wgt_MvCCRES[2]);
      h2_recoE_recoY_var_CH[0]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_MvCCRES[2]);

      h2_trueE_trueY_var_CH[1]->Fill(Ev_CH, YY_CH, wgt_AhtBY[2]);
      h2_recoE_recoY_var_CH[1]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_AhtBY[2]);

      h2_trueE_trueY_var_CH[2]->Fill(Ev_CH, YY_CH, wgt_BhtBY[2]);
      h2_recoE_recoY_var_CH[2]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_BhtBY[2]);

      h2_trueE_trueY_var_CH[3]->Fill(Ev_CH, YY_CH, wgt_C12ToAr40_2p2hScaling_nu[2]);
      h2_recoE_recoY_var_CH[3]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_C12ToAr40_2p2hScaling_nu[2]);

      h2_trueE_trueY_var_CH[4]->Fill(Ev_CH, YY_CH, wgt_SPPLowQ2Suppression[2]);
      h2_recoE_recoY_var_CH[4]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_SPPLowQ2Suppression[2]);

      h2_trueE_trueY_var_CH[5]->Fill(Ev_CH, YY_CH, wgt_FSILikeEAvailSmearing[2]);
      h2_recoE_recoY_var_CH[5]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_FSILikeEAvailSmearing[2]);

      h2_trueE_trueY_var_CH[6]->Fill(Ev_CH, YY_CH, wgt_nuenuebar_xsec_ratio[2]);
      h2_recoE_recoY_var_CH[6]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_nuenuebar_xsec_ratio[2]);

      h2_trueE_trueY_var_CH[7]->Fill(Ev_CH, YY_CH, wgt_E2p2h_A_nu[2]);
      h2_recoE_recoY_var_CH[7]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_E2p2h_A_nu[2]);

      h2_trueE_trueY_var_CH[8]->Fill(Ev_CH, YY_CH, wgt_E2p2h_B_nu[2]);
      h2_recoE_recoY_var_CH[8]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_E2p2h_B_nu[2]);

      h2_trueE_trueY_var_CH[9]->Fill(Ev_CH, YY_CH, wgt_Mnv2p2hGaussEnhancement[2]);
      h2_recoE_recoY_var_CH[9]->Fill(Ev_reco, (Ev_reco-Elep_reco)/Ev_reco, wgt_Mnv2p2hGaussEnhancement[2]);    
    }
  }


  for(Int_t i=0;i<3;i++){
    EvtVtx[i]=0;
  }
  for(Int_t i=0;i<100;i++){
    for(Int_t j=0;j<4;j++){
      StdHepP4[i][j]=0;
    }
    StdHepPdg[i]=0;
  }  
  nuE=0; lepE=0;

  nuwroCH->SetBranchAddress("StdHepP4",&StdHepP4);
  nuwroCH->SetBranchAddress("StdHepPdg",&StdHepPdg);

  for(Int_t j=0; j< Nentries; j++){
    nuwroCH->GetEntry(j);
    selected = false;

    //cout<<StdHepPdg[3]<<endl;
    for(Int_t i=0;i<6;i++){
      if(StdHepPdg[i] == 14)
        nuE = StdHepP4[i][3];
      if(StdHepPdg[i] == 13){
        lepE = StdHepP4[i][3];
        selected = true;
      }
    }
    if (selected ){
      h2_nuwro_true_CH->Fill(nuE, (nuE-lepE) / nuE );
      //cout<<nuE<<" "<<lepE<<endl;
    }
  }

  for(Int_t iX =0; iX<h2_trueE_trueY_var_CH[0]->GetNbinsX();iX++ ){
    for(Int_t iY =0; iY<h2_trueE_trueY_var_CH[0]->GetNbinsY();iY++ ){
      if(h2_nuwro_true_CH->GetBinContent(iX+1,iY+1)>0)
        h2_Ar_diff_CH -> SetBinContent( iX+1, iY+1,
                      h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1) +
                      (h2_trueE_trueY_var_CH[0]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finI +
                      (h2_trueE_trueY_var_CH[1]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finJ +
                      (h2_trueE_trueY_var_CH[2]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finK  +
                      (h2_trueE_trueY_var_CH[3]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finII +
                      (h2_trueE_trueY_var_CH[4]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finJJ +
                      (h2_trueE_trueY_var_CH[5]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finKK +
                      (h2_trueE_trueY_var_CH[6]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finIII +
                      (h2_trueE_trueY_var_CH[7]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finJJJ +
                      (h2_trueE_trueY_var_CH[8]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finKKK  +
                      (h2_trueE_trueY_var_CH[9]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finIIII -
                      h2_nuwro_true_CH->GetBinContent(iX+1,iY+1)) ;
    }
  }

  int acc=0;
  for(Int_t iX =0; iX<h2_trueE_trueY_var_CH[0]->GetNbinsX();iX++ ){
    for(Int_t iY =0; iY<h2_trueE_trueY_var_CH[0]->GetNbinsY();iY++ ){
      if(h2_nuwro_true_CH->GetBinContent(iX+1,iY+1)>0) acc += TMath::Power(
                      h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1) +
                      (h2_trueE_trueY_var_CH[0]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finI +
                      (h2_trueE_trueY_var_CH[1]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finJ +
                      (h2_trueE_trueY_var_CH[2]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finK +
                      (h2_trueE_trueY_var_CH[3]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finII +
                      (h2_trueE_trueY_var_CH[4]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finJJ +
                      (h2_trueE_trueY_var_CH[5]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finKK +
                      (h2_trueE_trueY_var_CH[6]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finIII +
                      (h2_trueE_trueY_var_CH[7]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finJJJ +
                      (h2_trueE_trueY_var_CH[8]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finKKK +
                      (h2_trueE_trueY_var_CH[9]->GetBinContent(iX+1,iY+1)-h2_trueE_trueY_nominal_CH->GetBinContent(iX+1,iY+1))*finIIII
                      - h2_nuwro_true_CH->GetBinContent(iX+1,iY+1),2) / h2_nuwro_true_CH->GetBinContent(iX+1,iY+1) ;
    }
  }

  acc += finI*finI + finJ*finJ + finK*finK + finII*finII + finJJ*finJJ + finKK*finKK
         + finIII*finIII + finJJJ*finJJJ + finKKK*finKKK + finIIII*finIIII;
  cout<<"the CH chi2 is "<<acc<<endl;
  cout<<"final pulls : "<<finI<<" "<<finJ<<" "<<finK<<" "<<finII<<" "<<finJJ<<" "<<finKK<<" "<<finIII<<" "<<finJJJ<<" "<<finKKK<<" "<<finIII<<" \
  "<<endl;


  TCanvas* c11 = new TCanvas();
  c11->Divide(3,4);
  c11->cd(1);
  h2_trueE_trueY_nominal_CH->GetXaxis()->SetTitle("True Ev (GeV)");
  h2_trueE_trueY_nominal_CH->GetYaxis()->SetTitle("True Y ");
  h2_trueE_trueY_nominal_CH->Draw("colz");
  c11->cd(2);
  h2_recoE_recoY_nominal_CH->Draw("colz");
  h2_recoE_recoY_nominal_CH->GetXaxis()->SetTitle("Reco. Ev (GeV)");
  h2_recoE_recoY_nominal_CH->GetYaxis()->SetTitle("Reco. Y ");

  for(Int_t i=0;i<6;i++){
    c11->cd(2*i+3);
    h2_trueE_trueY_var_CH[i]->Draw("colz");
    h2_trueE_trueY_var_CH[i]->GetXaxis()->SetTitle("True Ev (GeV)");
    h2_trueE_trueY_var_CH[i]->GetYaxis()->SetTitle("True Y ");

    c11->cd(2*i+4);
    h2_recoE_recoY_var_CH[i]->Draw("colz");
    h2_recoE_recoY_var_CH[i]->GetXaxis()->SetTitle("Reco. Ev (GeV)");
    h2_recoE_recoY_var_CH[i]->GetYaxis()->SetTitle("Reco. Y ");

  }

  new TCanvas();
  h2_nuwro_true_CH->Draw("colz");
  h2_nuwro_true_CH->GetXaxis()->SetTitle("Reco. Ev (GeV)");
  h2_nuwro_true_CH->GetYaxis()->SetTitle("Reco. Y ") ;

  new TCanvas();
  h2_Ar_diff_CH->Draw("colz");
  h2_Ar_diff_CH->SetTitle("Difference between nuwro and fitted genie on CH");
  h2_Ar_diff_CH->GetXaxis()->SetTitle("True Ev (GeV)");
  h2_Ar_diff_CH->GetYaxis()->SetTitle("True Y ") ;
  h2_Ar_diff_CH->GetZaxis()->SetRangeUser(-1000,1000);
}

