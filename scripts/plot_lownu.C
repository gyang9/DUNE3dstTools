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

  TH1D* h1 = new TH1D("","",50,0,5);
  TH1D* h_trueE = new TH1D("","",50,0,10);
  TH1D* h_recoE = new TH1D("","",50,0,10);
  TH1D* h_recoEd = new TH1D("","",50,0,10);
  TH1D* tempDraw1 = new TH1D("","",50,0,10);
  TH1D* h_recoE_compare = new TH1D("","",50,0,10);
  TH1D* h_recoEd_compare = new TH1D("","",50,0,10);
  TH2D* h2_E = new TH2D("","",50,0,10,50,0,10);

  TH1D* h_trueEw[5];
  TH1D* h_recoEw[5];
  for(int i=0;i<5;i++){
    h_trueEw[i] = new TH1D("","",50,0,10);
    h_recoEw[i] = new TH1D("","",50,0,10);
  }

  //TH1D* h2 = new TH1D("","",100,0,100);
  //TH1D* h3 = new TH1D("","",100,0,100);

  //TH1D* h4 = new TH1D("","",100,0,100);
  //TH1D* h5 = new TH1D("","",100,0,100);

  TH1D* h2[50];
  TH1D* h3[50];
  TH1D* h4[50];
  TH1D* h5[50];
  TH1D* h6[50];
  TH1D* h7[50];
  int nProton = 0;
  int nNeutron = 0;
  int nNeutron_compare = 0;
  int nPip = 0;
  int nPi0 = 0;

  for(Int_t i=0;i<50;i++){
    h2[i] = new TH1D("","",100,0,100);
    h3[i] = new TH1D("","",100,0,100);
    h4[i] = new TH1D("","",100,0,100);
    h5[i] = new TH1D("","",100,0,100);
    h6[i] = new TH1D("","",100,0,100);
    h7[i] = new TH1D("","",100,0,100);
  }

  TH1D* hh1 = new TH1D("","",10,0,10);
  TH1D* hh2 = new TH1D("","",10,0,10);
  TH1D* hh3 = new TH1D("","",10,0,10);
  TH1D* hh4 = new TH1D("","",10,0,10);
  TH1D* hh5 = new TH1D("","",10,0,10);
  TH1D* hh6 = new TH1D("","",10,0,10);

  TH2D* h2D1 = new TH2D("","",50,0,10,50,0,10);
  TH2D* h2D2 = new TH2D("","",50,0,10,50,0,10);
  TH2D* h2D_lownu = new TH2D("","",100,0,10,100,0,10);

  // energy binning 2-3, 3-4, .... 7-9, 9-12, 12-15, 15-18, 18-22, 22-26, 26-30, 30-36, 36-42, 42-50
  double minervaBin[15] = {2.5, 3.5, 4.5, 5.5, 6.5, 8, 10.5, 13.5, 16.5, 20, 24, 28, 32, 39, 46};
  double minerva_FHC_phi[15]={76.046, 77.528, 29.776, 12.243, 7.908, 10.435, 9.780, 6.115, 3.477, 2.620, 1.331, 0.751, 0.726, 0.497, 0.452};
  double minerva_FHC_unc[15]={3.262, 2.176, 0.672, 0.295, 0.234, 0.302, 0.240, 0.153, 0.085, 0.064, 0.031, 0.017, 0.018, 0.012, 0.013};
  double minerva_RHC_phi[15]={3.344, 3.496, 3.161, 2.817, 2.497, 4.256, 4.017, 2.287, 1.17, 0.838, 0.380, 0.179, 0.145, 0.081, 0.054};
  double minerva_RHC_unc[15]={0.310, 0.208, 0.135, 0.064, 0.044, 0.057, 0.048, 0.034, 0.020, 0.014, 0.007, 0.003, 0.003, 0.001, 0.001};

  TGraph* gFHC = new TGraph(15);
  TGraph* gRHC = new TGraph(15);
  for(Int_t i=0;i<15;i++){
    gFHC->SetPoint(i, minervaBin[i], minerva_FHC_unc[i]/minerva_FHC_phi[i]);
    gRHC->SetPoint(i, minervaBin[i], minerva_RHC_unc[i]/minerva_RHC_phi[i]);
  }

  new TCanvas();
  gRHC->SetLineWidth(3);
  gRHC->Draw();
  gRHC->GetXaxis()->SetTitle("energy (GeV)");
  gRHC->GetYaxis()->SetTitle("Fractional error");

  TFile shift("flux_shifts.root");
  gDirectory->cd("syst0");
  TH1D* FD_numubar_RHC1 = (TH1D*)gDirectory->Get("FD_numubar_RHC");
  gDirectory->cd("../syst1");
  TH1D* FD_numubar_RHC2 = (TH1D*)gDirectory->Get("FD_numubar_RHC");
  gDirectory->cd("../syst2");
  TH1D* FD_numubar_RHC3 = (TH1D*)gDirectory->Get("FD_numubar_RHC");
  gDirectory->cd("../syst3");
  TH1D* FD_numubar_RHC4 = (TH1D*)gDirectory->Get("FD_numubar_RHC");
  gDirectory->cd("../syst4");
  TH1D* FD_numubar_RHC5 = (TH1D*)gDirectory->Get("FD_numubar_RHC");

  TCanvas* c11 = new TCanvas();
  c11->Divide(2,3);
  c11->cd(1);
  FD_numubar_RHC1->Draw();
  FD_numubar_RHC1->GetXaxis()->SetTitle("Energy");
  FD_numubar_RHC1->GetYaxis()->SetTitle("shift \%");  
  c11->cd(2);
  FD_numubar_RHC2->Draw();
  FD_numubar_RHC2->GetXaxis()->SetTitle("Energy");
  FD_numubar_RHC2->GetYaxis()->SetTitle("shift \%");
  c11->cd(3);
  FD_numubar_RHC3->Draw();
  FD_numubar_RHC3->GetXaxis()->SetTitle("Energy");
  FD_numubar_RHC3->GetYaxis()->SetTitle("shift \%");
  c11->cd(4);
  FD_numubar_RHC4->Draw();
  FD_numubar_RHC4->GetXaxis()->SetTitle("Energy");
  FD_numubar_RHC4->GetYaxis()->SetTitle("shift \%");  
  c11->cd(5);
  FD_numubar_RHC5->Draw();
  FD_numubar_RHC5->GetXaxis()->SetTitle("Energy");
  FD_numubar_RHC5->GetYaxis()->SetTitle("shift \%");  

  TGraph* g1 = new TGraph(FD_numubar_RHC1->GetNbinsX());
  TGraph* g2 = new TGraph(FD_numubar_RHC1->GetNbinsX());
  TGraph* g3 = new TGraph(FD_numubar_RHC1->GetNbinsX());
  TGraph* g4 = new TGraph(FD_numubar_RHC1->GetNbinsX());
  TGraph* g5 = new TGraph(FD_numubar_RHC1->GetNbinsX());

  for(Int_t i=0;i<FD_numubar_RHC1->GetNbinsX();i++){
    g1->SetPoint(i,FD_numubar_RHC1->GetBinCenter(i+1), FD_numubar_RHC1->GetBinContent(i+1));
    g2->SetPoint(i,FD_numubar_RHC2->GetBinCenter(i+1), FD_numubar_RHC2->GetBinContent(i+1));
    g3->SetPoint(i,FD_numubar_RHC3->GetBinCenter(i+1), FD_numubar_RHC3->GetBinContent(i+1));
    g4->SetPoint(i,FD_numubar_RHC4->GetBinCenter(i+1), FD_numubar_RHC4->GetBinContent(i+1));
    g5->SetPoint(i,FD_numubar_RHC5->GetBinCenter(i+1), FD_numubar_RHC5->GetBinContent(i+1));    
  }

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

    for(Int_t j=0;j<StdHepN;j++){
      //cout<<StdHepPdg[j]<<" "<<StdHepStatus[j]<<endl;
      if(abs(StdHepPdg[j])==13 && StdHepStatus[j]==1 && lepE == 0){
        lepE = StdHepP4[j][3];
	lepM = TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+StdHepP4[j][2]*StdHepP4[j][2]);
	
        //cout<<lepE<<" "<<lepM<<endl;
	//break;
      }

      else if(abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1  && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> pionThreshold){
      //else if (abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1 ){
        ran1->SetSeed(j * i* 34002);
        double momSmear = ran1->Gaus(1,pipSmear);
        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
        lownu_reco_compare +=  TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
	nPip ++;
      }
      else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1 && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> pionThreshold){
      //else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1){
        ran1->SetSeed(j *i*  10002);
        double momSmear = ran1->Gaus(1,pi0Smear);
        lownu_reco += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
	lownu_reco_compare += TMath::Sqrt(TMath::Power(TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0]+StdHepP4[j][1]*StdHepP4[j][1]+ StdHepP4[j][2]*StdHepP4[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
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
	nProton ++;
      }
      
      //else if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && TMath::Sqrt(StdHepP4[j][0]*StdHepP4[j][0] + StdHepP4[j][1]*StdHepP4[j][1] + StdHepP4[j][2]*StdHepP4[j][2])> neutronThreshold){
      double rndN = gRandom->Uniform(0,1);
      //cout<<rndN<<endl;
      ran1->SetSeed(j * i * 11002);
      double momSmear = ran1->Gaus(1, neutronSmear);
      if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && rndN<neutronEff){
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
    /*
    lownu_reco -= (nPip-1)*pipMass;
    if(nPip>0)
     lownu_reco -= (nPi0)*pi0Mass;
    else
     lownu_reco -= (nPi0-1)*pi0Mass;
    */
    //lownu_reco = nuE - lownu_reco;
    h2D_lownu->Fill(lownu, lownu_reco);

    h1->Fill(lownu);
    if(lepM > 0 && nuE > lepE){
      h2D1->Fill(nuE, lepE);
      h2D2->Fill(nuE, lepM);
    }
    if(lownu_reco<0.2 ) {
      record1 ++;
      double tempReco = lownu_reco + TMath::Sqrt(TMath::Power(lepM*gRandom->Gaus(1, lepM*muonSmear),2) + TMath::Power(muonMass,2)) ;
      h_trueE -> Fill(nuE);
      h_recoE -> Fill(tempReco );
      h_recoEd -> Fill(tempReco );

      h_trueEw[0] ->Fill(nuE, 1+ g1->Eval(nuE));
      h_trueEw[1] ->Fill(nuE, 1+ g2->Eval(nuE));
      h_trueEw[2] ->Fill(nuE, 1+ g3->Eval(nuE));
      h_trueEw[3] ->Fill(nuE, 1+ g4->Eval(nuE));
      h_trueEw[4] ->Fill(nuE, 1+ g5->Eval(nuE));

      h_recoEw[0] ->Fill(tempReco, 1+ g1->Eval(nuE));
      h_recoEw[1] ->Fill(tempReco, 1+ g2->Eval(nuE));
      h_recoEw[2] ->Fill(tempReco, 1+ g3->Eval(nuE));
      h_recoEw[3] ->Fill(tempReco, 1+ g4->Eval(nuE));
      h_recoEw[4] ->Fill(tempReco, 1+ g5->Eval(nuE));

      h2_E -> Fill(nuE, tempReco);
    }

    if(lownu_reco_compare < 0.2){
      double tempReco_compare = lownu_reco_compare + TMath::Sqrt(TMath::Power(lepM*gRandom->Gaus(1, lepM*muonSmear),2) + TMath::Power(muonMass,2)) ;
      h_recoE_compare -> Fill(tempReco_compare );
      h_recoEd_compare -> Fill(tempReco_compare );
    }

    if(lownu_reco<0.2 && lownu<0.2) record2 ++;
    if(lownu_reco<0.1 ) record3 ++;
    if(lownu_reco<0.1 && lownu<0.1) record4 ++;    

    int tempX1 = nuE;
    //cout<<StdHepP4[0][3]<<" "<<tempX1<<endl;
    int tempX2 = tempX1;
    int tempX3 = tempX1;
    int tempX4 = tempX1;
    int tempX5 = tempX1;
    int tempX6 = tempX1;

    if(lownu>0 && nuE< 50){
      h2[tempX1]->Fill(EvtXSec);
      h3[tempX2]->Fill(EvtDXSec);
    }
    if(lownu>0 && lownu<0.2 && nuE<50){
      h4[tempX3]->Fill(EvtXSec);
      h5[tempX4]->Fill(EvtDXSec);
    }
    if(lownu>0 && lownu<0.1 && nuE<50){
      h6[tempX5]->Fill(EvtXSec);
      h7[tempX6]->Fill(EvtDXSec);
      //cout<<tempX1<<" "<<tempX2<< " "<<lownu<<" "<<EvtXSec<<" "<<EvtDXSec<<endl;
    }
    
  }

  //h2->Scale(h4->Integral()/h2->Integral());
  //h3->Scale(h5->Integral()/h3->Integral());
  
  for(Int_t i=0;i<hh1->GetNbinsX();i++){
    hh1->SetBinContent(i+1,h2[i]->GetMean());
    hh2->SetBinContent(i+1,h3[i]->GetMean());
    hh3->SetBinContent(i+1,h4[i]->GetMean());
    hh4->SetBinContent(i+1,h5[i]->GetMean());
    cout<<h6[i]->GetMean()<<" "<<h7[i]->GetMean()<<endl;
    hh5->SetBinContent(i+1,h6[i]->GetMean());
    hh6->SetBinContent(i+1,h7[i]->GetMean());
  }
	
  new TCanvas();
  h1->Draw();

  new TCanvas();
  hh1->SetLineColor(1);
  hh3->SetLineColor(2);
  hh5->SetLineColor(4);
  hh1->Draw();
  hh1->GetXaxis()->SetTitle("Energy (GeV)");
  hh1->GetYaxis()->SetTitle("Total Xsec.");
  hh3->Draw("same hist");
  hh5->Draw("same hist");

  new TCanvas();
  hh2->SetLineColor(1);
  hh4->SetLineColor(2);
  hh2->Draw();
  hh2->GetXaxis()->SetTitle("Energy (GeV)");
  hh2->GetYaxis()->SetTitle("Differential Xsec. (A.U)");  
  hh4->Scale(hh2->Integral()/hh4->Integral());
  hh6->Scale(hh2->Integral()/hh6->Integral());
  hh4->Draw("same hist");
  hh6->SetLineColor(4);
  hh6->Draw("same hist");
  TLegend* leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hh2 ,"no cuts","l");
  leg->AddEntry(hh4 ,"#nu < 0.2 GeV","l");
  leg->AddEntry(hh6 ,"#nu < 0.1 GeV","l");
  leg->SetBorderSize(2);
  leg->SetTextFont(62);
  leg->SetFillColor(1);
  leg->SetLineColor(1);
  leg->SetShadowColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->Draw();


  new TCanvas();
  h2D1->Draw("colz");
  h2D1->GetXaxis()->SetTitle("Neutrino energy (GeV)");
  h2D1->GetYaxis()->SetTitle("Muon energy (GeV)");
  
  new TCanvas();
  h2D2->Draw("colz");
  h2D2->GetXaxis()->SetTitle("Neutrino energy (GeV)");
  h2D2->GetYaxis()->SetTitle("Muon momentum (GeV)");  

  new TCanvas();
  h2D_lownu->GetXaxis()->SetTitle("True #nu (GeV)");
  h2D_lownu->GetYaxis()->SetTitle("Reco #nu (GeV)");
  h2D_lownu->Draw("colz");

  std::cout<<"ratios "<<record2/record1<<" "<<record4/record3<<std::endl;

  new TCanvas();
  h_recoE->SetLineColor(2);
  h_trueE->SetLineColor(4);
  h_recoE->SetLineWidth(3);
  h_trueE->SetLineWidth(3);
  h_recoE->Draw("");
  h_trueE->Draw("same");
  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(h_recoE ,"reco E","l");
  leg->AddEntry(h_trueE ,"true E","l");
  leg->SetBorderSize(2);
  leg->SetTextFont(62);
  leg->SetFillColor(1);
  leg->SetLineColor(1);
  leg->SetShadowColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->Draw();

  new TCanvas();
  h2_E->GetXaxis()->SetTitle("true E");
  h2_E->GetYaxis()->SetTitle("reco E");
  h2_E->Draw("colz");

      
  for(int i=0;i<5;i++){
    h_recoEw[i]->Scale(lownu_oneYear*lownu_yearN/h_recoEw[i]->Integral());
    h_trueEw[i]->Scale(lownu_oneYear*lownu_yearN/h_trueEw[i]->Integral());  
  }
  h_recoEd->Scale(lownu_oneYear*lownu_yearN/h_recoEd->Integral());
  h_recoEd_compare->Scale(lownu_oneYear*lownu_yearN/h_recoEd_compare->Integral());

  double pull[5]={};
  double pull2[5]={};
  double pull3[5]={};

  for(int j=0;j<5;j++){
    for(int i=0;i<h_recoEw[0]->GetNbinsX();i++){
      double currUnc = h_recoEw[j]->GetBinContent(i+1) ;
      double currUnc2 = h_recoEw[j]->GetBinContent(i+1) + TMath::Power( ( h_recoEw[j]->GetBinContent(i+1) * gRHC->Eval(h_recoEw[j]->GetBinCenter(i+1)) ),2) ;
      double currUnc3 = h_recoEw[j]->GetBinContent(i+1) + TMath::Power( ( h_recoEw[j]->GetBinContent(i+1) * gRHC->Eval(h_recoEw[j]->GetBinCenter(i+1)) ),2) + TMath::Power( h_recoEd->GetBinContent(i+1) - h_recoEd_compare->GetBinContent(i+1) , 2);

      pull[j] += TMath::Power(h_recoEw[j]->GetBinContent(i+1) - h_recoEd->GetBinContent(i+1),2) / currUnc ;
      pull2[j] += TMath::Power(h_recoEw[j]->GetBinContent(i+1) - h_recoEd->GetBinContent(i+1),2) / currUnc2 ;
      pull3[j] += TMath::Power(h_recoEw[j]->GetBinContent(i+1) - h_recoEd->GetBinContent(i+1),2) / currUnc3 ;

    }
    std::cout<<"pull with stat.                "<<j<<" is "<<sqrt(pull[j])<<std::endl;
    std::cout<<"pull with stat. + model        "<<j<<" is "<<sqrt(pull2[j])<<std::endl;
    std::cout<<"pull with stat. + model + eff. "<<j<<" is "<<sqrt(pull3[j])<<std::endl;
  }

  for(Int_t i=0;i<h_recoEd->GetNbinsX(); i++){
    tempDraw1->SetBinContent(i+1, (h_recoEd->GetBinContent(i+1) - h_recoEd_compare->GetBinContent(i+1)) / h_recoEd->GetBinContent(i+1));
  }

  TCanvas* c100 = new TCanvas();
  c100->Divide(1,2);
  c100->cd(1);
  h_recoEd->SetLineColor(2);
  h_recoEd->SetLineWidth(3);
  h_recoEd_compare->SetLineColor(2);
  h_recoEd_compare->SetLineWidth(3);
  h_recoEd->Draw("hist");
  h_recoEd->GetXaxis()->SetTitle("reconstructed energy (GeV)");
  h_recoEd->GetYaxis()->SetTitle("Event rate");
  h_recoEd_compare->Draw("same");
  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(h_recoEd ,"100\% neutron detection eff.","l");
  leg->AddEntry(h_recoEd_compare ,"50\% neutron detection eff.","l");
  leg->SetBorderSize(2);
  leg->SetTextFont(62);
  leg->SetFillColor(1);
  leg->SetLineColor(1);
  leg->SetShadowColor(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(2);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->Draw();
  c100->cd(2);
  tempDraw1->SetLineColor(1);
  tempDraw1->SetLineWidth(3);
  tempDraw1->GetXaxis()->SetTitle("reconstructed energy (GeV)");
  tempDraw1->GetYaxis()->SetTitle("#frac{100\% neutron - x \% neutron}{100\% neutron}");
  tempDraw1->Draw("hist");
  TF1* tf1 = new TF1("tf1","0",0,100);
  tf1->SetLineStyle(2);
  tf1->Draw("same");

  TCanvas* c12 = new TCanvas();
  c12->Divide(2,3);
  c12->cd(1);
  h_recoEw[0]->SetLineColor(2);
  h_recoEd->SetLineColor(4);
  h_recoEw[0]->SetLineWidth(3);
  h_recoEd->SetLineWidth(3);
  h_recoEw[0]->Draw();
  h_recoEd->Draw("same");
  h_recoEw[0]->GetXaxis()->SetTitle("Energy (GeV)");
  h_recoEw[0]->GetYaxis()->SetTitle("Event rate");

  c12->cd(2);
  h_recoEw[1]->SetLineColor(2);
  h_recoEd->SetLineColor(4);
  h_recoEw[1]->SetLineWidth(3);
  h_recoEd->SetLineWidth(3);
  h_recoEw[1]->Draw();
  h_recoEd->Draw("same");
  h_recoEw[1]->GetXaxis()->SetTitle("Energy (GeV)");
  h_recoEw[1]->GetYaxis()->SetTitle("Event rate");

  c12->cd(3);
  h_recoEw[2]->SetLineColor(2);
  h_recoEd->SetLineColor(4);
  h_recoEw[2]->SetLineWidth(3);
  h_recoEd->SetLineWidth(3);
  h_recoEw[2]->Draw();
  h_recoEd->Draw("same");
  h_recoEw[2]->GetXaxis()->SetTitle("Energy (GeV)");
  h_recoEw[2]->GetYaxis()->SetTitle("Event rate");  

  c12->cd(4);
  h_recoEw[3]->SetLineColor(2);
  h_recoEd->SetLineColor(4);
  h_recoEw[3]->SetLineWidth(3);
  h_recoEd->SetLineWidth(3);
  h_recoEw[3]->Draw();
  h_recoEd->Draw("same");
  h_recoEw[3]->GetXaxis()->SetTitle("Energy (GeV)");
  h_recoEw[3]->GetYaxis()->SetTitle("Event rate");

  c12->cd(5);
  h_recoEw[4]->SetLineColor(2);
  h_recoEd->SetLineColor(4);
  h_recoEw[4]->SetLineWidth(3);
  h_recoEd->SetLineWidth(3);
  h_recoEw[4]->Draw();
  h_recoEd->Draw("same");
  h_recoEw[4]->GetXaxis()->SetTitle("Energy (GeV)");
  h_recoEw[4]->GetYaxis()->SetTitle("Event rate");
}
