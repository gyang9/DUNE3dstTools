{
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

  //1.48e6 FHC    8.8e5 RHC
  double lownu_oneYear = 8e5; 
  double lownu_yearN = 1;

  double electronMass = 0.5e-3;
  double muonMass     = 0.1057;
  double tauMass      = 1.77686;
  double pipMass      = 0.13957;
  double pi0Mass      = 0.13498;
  double protonMass   = 0.93827;
  double neutronMass  = 0.939565;
  double binding      = 0.068;

  double neutronEff = 1;
  double neutronEffCompare = 0.5;

  double muonSmear = 0.04;
  double pipSmear = 0.1;
  double pi0Smear = 0.1;
  double electronSmear = 0.1;
  double protonSmear = 0.1;
  double neutronSmear = 0.3;

  double muonThreshold = 0.01;
  double pionThreshold = 0.01;
  double neutronThreshold = 0.01;
  double protonThreshold = 0.3;
  double electronThreshold = 0;  

  double StdHepX4[1000][4];
  int StdHepStatus[1000];
  int StdHepPdg[1000];
  int StdHepN;
  double StdHepP4[1000][4];
  double EvtVtx[4];
  double EvtXSec, EvtDXSec;
  double lepE,lepM;
  double nuE;
  double lownu;
  double lownu_reco;
  double lownu_reco_compare;
  double stv_x = 0;
  double stv_y = 0;

  TChain t("gRooTracker");
  t.Add("/home/guang/work/DUNE3dstTools/data/PROD101/full3DST.antineutrino*1*ker.root");
  
  t.SetBranchAddress("StdHepX4",&StdHepX4);
  t.SetBranchAddress("StdHepStatus",&StdHepStatus);
  t.SetBranchAddress("StdHepPdg",&StdHepPdg);
  t.SetBranchAddress("StdHepP4",&StdHepP4);
  t.SetBranchAddress("EvtVtx",&EvtVtx);
  t.SetBranchAddress("EvtXSec",&EvtXSec);
  t.SetBranchAddress("EvtDXSec",&EvtDXSec);
  t.SetBranchAddress("StdHepN",&StdHepN);

  TRandom3 *ran1 = new TRandom3();
  TRandom3 *ran2 = new TRandom3();
  TRandom3 *ran111 = new TRandom3();
  double record1 = 0;
  double record2 = 0;
  double record3 = 0;
  double record4 = 0;

  int nProton = 0;
  int nNeutron = 0;
  int nNeutron_compare = 0;
  int nPip = 0;
  int nPi0 = 0;  
  bool isCC = false;

  TH2F* h1 = new TH2F("","ALL dpt vs. energy transfer; dpt (GeV); #nu (GeV)",100,0,5,100,0,5);
  TH2F* h2 = new TH2F("","0#pi dpt vs. energy transfer; dpt (GeV); #nu (GeV)",100,0,5,100,0,5);
  TH2F* h3 = new TH2F("","1#pi dpt vs. energy transfer; dpt (GeV); #nu (GeV)",100,0,5,100,0,5);
  TH2F* h4 = new TH2F("","multi-#pi dpt vs. energy transfer; dpt (GeV); #nu (GeV)",100,0,5,100,0,5);    
  TH2F* h5 = new TH2F("","ALL neutirno energy vs. energy transfer; E#nu (GeV); #nu (GeV)",100,0,8,100,0,5);
  TH2F* h6 = new TH2F("","0#pi neutrino energy vs. energy transfer; E#nu (GeV); #nu (GeV)",100,0,8,100,0,5);
  TH2F* h7 = new TH2F("","1#pi neutrino energy vs. energy transfer; E#nu (GeV); #nu (GeV)",100,0,8,100,0,5);
  TH2F* h8 = new TH2F("","multi-#pi neutrino energy vs. energy transfer; E#nu (GeV); #nu (GeV)",100,0,8,100,0,5);

  TH1F* hh1 = new TH1F("","0#pi neutirno energy; E#nu (GeV); Counts",100,0,8);
  TH1F* hh2 = new TH1F("","0#pi neutirno energy; E#nu (GeV); Counts",100,0,8);
  TH1F* hh3 = new TH1F("","0#pi neutirno energy; E#nu (GeV); Counts",100,0,8);  

  for(Int_t i =0; i< t.GetEntries(); i++){

    t.GetEntry(i);    
    
    lepE = 0; nuE = 0;
    lownu = 0;
    lepM = 0;
    lownu_reco = 0;
    lownu_reco_compare = 0;
    nProton =0;
    nNeutron =0;
    nNeutron_compare = 0;
    nPip = 0;
    nPi0 = 0;
    stv_x = 0;
    stv_y = 0;
    isCC = false;

    for(Int_t j=0;j<StdHepN;j++){
      //cout<<StdHepPdg[j]<<" "<<StdHepStatus[j]<<endl;
      if(abs(StdHepPdg[j])==13 && StdHepStatus[j]==1 && lepE == 0){
	isCC = true;
        lepE = StdHepP4[j][3];
	lepM = TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+StdHepP4[j][2]*StdHepP4[j][2]);
	
	stv_x += StdHepP4[j][0];
	stv_y += StdHepP4[j][1];
        //cout<<lepE<<" "<<lepM<<endl;
	//break;
      }

      else if(abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1  && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> pionThreshold){
      //else if (abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1 ){
        ran1->SetSeed(j * i* 34002);
        double momSmear = ran1->Gaus(1,pipSmear);
        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
        lownu_reco_compare +=  TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
        stv_x += StdHepP4[j][0];
	stv_y += StdHepP4[j][1];
	nPip ++;
      }
      else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1 && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> pionThreshold){
      //else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1){
        ran1->SetSeed(j *i*  10002);
        double momSmear = ran1->Gaus(1,pi0Smear);
        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
	lownu_reco_compare += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
        stv_x += StdHepP4[j][0];
        stv_y += StdHepP4[j][1];
	nPi0 ++;
      }
      /*
      //else if(abs(StdHepPdg[j])== 11 && StdHepStatus[j]==1 && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> electronThreshold){
      else if(abs(StdHepPdg[j])== 11 && StdHepStatus[j]==1){
        ran1->SetSeed(j * 10002);
        double momSmear = ran1->Gaus(1,electronSmear);
        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(electronMass, 2) );
      }
      */
      else if(abs(StdHepPdg[j])== 2212 && StdHepStatus[j]==1 && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> protonThreshold){
      //else if(abs(StdHepPdg[j])== 2212 && StdHepStatus[j]==1){
        ran1->SetSeed(j *i*  10002);
        double momSmear = ran1->Gaus(1,protonSmear);
        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(protonMass, 2) );
	lownu_reco_compare += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(protonMass, 2) );
        stv_x += StdHepP4[j][0];
        stv_y += StdHepP4[j][1];
	nProton ++;
      }
      
      //else if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> neutronThreshold){
      double rndN = gRandom->Uniform(0,1);
      //cout<<rndN<<endl;
      ran1->SetSeed(j * i * 11002);
      double momSmear = ran1->Gaus(1, neutronSmear);
      if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && rndN<neutronEff){

      	stv_x += StdHepP4[j][0];
        stv_y += StdHepP4[j][1];      

        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(neutronMass, 2) ) ;
        nNeutron ++;
      }
      if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && rndN<neutronEffCompare){
        lownu_reco_compare += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(neutronMass, 2) ) ;
        nNeutron_compare ++;
      }
    }
    nuE = StdHepP4[0][3];
    lownu = nuE - lepE;
    lownu_reco -= protonMass* nProton;
    lownu_reco -= neutronMass*nNeutron;
    lownu_reco_compare -= neutronMass * nNeutron_compare;
    h1->Fill(sqrt(stv_x*stv_x + stv_y*stv_y), lownu);
    if ( isCC && nPip == 0 && nPi0 == 0)
      h2->Fill(sqrt(stv_x*stv_x + stv_y*stv_y), lownu);
    if ( isCC && nPip + nPi0 == 1)
      h3->Fill(sqrt(stv_x*stv_x + stv_y*stv_y), lownu);
    if ( isCC && nPip + nPi0 > 1)
      h4->Fill(sqrt(stv_x*stv_x + stv_y*stv_y), lownu);

    h5->Fill(nuE, lownu);
    if ( isCC && nPip + nPi0 == 0){
      h6->Fill(nuE, lownu);
      hh1 -> Fill(nuE);
    }  
    if ( isCC && nPip + nPi0 == 1){
      h7->Fill(nuE, lownu);
      hh2->Fill(nuE);
    }  
    if ( isCC && nPip + nPi0 > 1){
      h8->Fill(nuE, lownu);   
      hh3->Fill(nuE); 
    }  
  }
  TCanvas* c1 = new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  h1->Draw("colz");
  c1->cd(2);
  h2->Draw("colz");
  c1->cd(3);
  h3->Draw("colz");
  c1->cd(4);
  h4->Draw("colz");
  
  TCanvas* c2 = new TCanvas();
  c2->Divide(2,2);
  c2->cd(1);
  h5->Draw("colz");
  c2->cd(2);
  h6->Draw("colz");
  c2->cd(3);
  h7->Draw("colz");
  c2->cd(4);
  h8->Draw("colz");

  new TCanvas();
  hh1->SetLineColor(1);
  hh2->SetLineColor(2);
  hh3->SetLineColor(4);
  hh1->Draw();
  hh2->Draw("same");
  hh3->Draw("same");
}
