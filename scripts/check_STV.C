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
  gStyle->SetTitleOffset(1.2,"y");

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
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(000000);


  TH1D* hCCQERight_mom = new TH1D("CCQE","CCQE",100,0,10);
  TH1D* hCCQERight_e = new TH1D("CCQE","CCQE",100,0,10);
  TH1D* hCCQERight_nu = new TH1D("CCQE","CCQE",100,0,10);
  TH1D* hCCQEWrong_mom = new TH1D("CCQE","CCQE",100,0,10);
  TH1D* hCCQEWrong_e = new TH1D("CCQE","CCQE",100,0,10);
  TH1D* hCCQEWrong_nu = new TH1D("CCQE","CCQE",100,0,10);

  TH1D* flux[4];
  for(Int_t i=0;i<4;i++) flux[i] = new TH1D("flux","flux",100,0,8);

  //TFile f1("FHC_numu_CCRES_Carbon_1x10e5.root");
  //TTree* h1 = (TTree*) f1.Get("gRooTracker");

  TChain h1("gRooTracker");
  h1.Add("/home/guang/work/DUNE3dstTools/data/PROD101/full3DST.antineutrino.*ker.root");

  Int_t StdHepPdg[1000];
  Int_t StdHepStatus[1000];
  Double_t vtx[4]={};
  Double_t ivtx[1000][4]={};
  Double_t imom[1000][4]={};
  Bool_t flag=false;
  Bool_t wflag=false;
  Int_t rightSign=0,wrongSign=0;
  int StdHepN;

  h1.SetBranchAddress("StdHepPdg", &StdHepPdg);
  h1.SetBranchAddress("StdHepStatus", &StdHepStatus);
  h1.SetBranchAddress("EvtVtx", &vtx);
  h1.SetBranchAddress("StdHepX4", &ivtx);
  h1.SetBranchAddress("StdHepP4", &imom); 
  h1.SetBranchAddress("StdHepN", &StdHepN);

  TH1D* hCarbon = new TH1D("Carbon","Area normalized",200,-1,1);
  TH1D* hHydrogen = new TH1D("Hydrogen","Hydrogen",40,-1,1);
  TH1D* hCarbon2 = new TH1D("Carbon2","Area normalized",200,-1,1);
  TH1D* hCarbon3 = new TH1D("Carbon2","Area normalized",200,-1,1);
  TH1D* hCarbon4 = new TH1D("Carbon2","Area normalized",200,-1,1);

  TH1D* hCarbon_noPi = new TH1D("Carbon_noPi","Area normalized",200,-1,1);
  TH1D* hCarbon2_noPi = new TH1D("Carbon2_noPi","Area normalized",200,-1,1);
  TH1D* hCarbon3_noPi = new TH1D("Carbon2_noPi","Area normalized",200,-1,1);
  TH1D* hCarbon4_noPi = new TH1D("Carbon2_noPi","Area normalized",200,-1,1);

  TH1D* hCarbon_1Pip = new TH1D("Carbon_1Pip","Area normalized",200,-1,1);
  TH1D* hCarbon2_1Pip = new TH1D("Carbon2_1Pip","Area normalized",200,-1,1);
  TH1D* hCarbon3_1Pip = new TH1D("Carbon2_1Pip","Area normalized",200,-1,1);
  TH1D* hCarbon4_1Pip = new TH1D("Carbon2_1Pip","Area normalized",200,-1,1);

  TH1D* hCarbon_1Pi0 = new TH1D("Carbon_1Pi0","Area normalized",200,-1,1);
  TH1D* hCarbon2_1Pi0 = new TH1D("Carbon2_1Pi0","Area normalized",200,-1,1);
  TH1D* hCarbon3_1Pi0 = new TH1D("Carbon2_1Pi0","Area normalized",200,-1,1);
  TH1D* hCarbon4_1Pi0 = new TH1D("Carbon2_1Pi0","Area normalized",200,-1,1);

  TH1D* hCarbon_mPi = new TH1D("Carbon_mPi","Area normalized",200,-1,1);
  TH1D* hCarbon2_mPi = new TH1D("Carbon2_mPi","Area normalized",200,-1,1);
  TH1D* hCarbon3_mPi = new TH1D("Carbon2_mPi","Area normalized",200,-1,1);
  TH1D* hCarbon4_mPi = new TH1D("Carbon2_mPi","Area normalized",200,-1,1);

  TH1D* hC_noPi = new TH1D("C_noPi","Area normalized",200,-1,1);
  TH1D* hC_1Pip = new TH1D("C_1Pip","Area normalized",200,-1,1);
  TH1D* hC_1Pi0 = new TH1D("C_1Pi0","Area normalized",200,-1,1);
  TH1D* hC_mPi = new TH1D("C_mPi","Area normalized",200,-1,1);

  TH1D* hH_noPi = new TH1D("H_noPi","Area normalized",200,-1,1);
  TH1D* hH_1Pip = new TH1D("H_1Pip","Area normalized",200,-1,1);
  TH1D* hH_1Pi0 = new TH1D("H_1Pi0","Area normalized",200,-1,1);
  TH1D* hH_mPi = new TH1D("H_mPi","Area normalized",200,-1,1);

  TH1D* hCarbon_m = new TH1D("Carbon_minus","Area normalized",200,-0.5,0.5);
  TH1D* hCarbon2_m = new TH1D("Carbon2_minus","Area normalized",200,-0.5,0.5);
  TH1D* hCarbon3_m = new TH1D("Carbon2_minus","Area normalized",200,-0.5,0.5);
  TH1D* hCarbon4_m = new TH1D("Carbon2_minus","Area normalized",200,-0.5,0.5);

  TH1D* hHydrogen2 = new TH1D("Hydrogen2","Hydrogen2",40,-1,1);
  TH1D* hScintillator = new TH1D("Scintillator","Scintillator",40,-1,1);

  TH2D* h2D[10];
  TH2D* h2D_noPi[10];
  TH2D* h2D_1Pip[10];
  TH2D* h2D_1Pi0[10];
  TH2D* h2D_mPi[10];
  for(Int_t i=0;i<10;i++){
    h2D[i] = new TH2D("","",40,0,10,40,0,10);
    h2D_noPi[i] = new TH2D("","",40,0,10,40,0,10);
    h2D_1Pi0[i] = new TH2D("","",40,0,10,40,0,10);
    h2D_1Pip[i] = new TH2D("","",40,0,10,40,0,10);
    h2D_mPi[i] = new TH2D("","",40,0,10,40,0,10);
  }

  TH2D* part1 = new TH2D("PDGvsStatus","PDGvsStatus",10,0,10,10,0,10);
  TH2D* tail = new TH2D("PDGvsStatus","PDGvsStatus",10,0,10,10,0,10);
  TH2D* tail_noPi = new TH2D("PDGvsStatus_noPi","PDGvsStatus_noPi",10,0,10,10,0,10);
  TH2D* tail_1Pi0 = new TH2D("PDGvsStatus_1Pi0","PDGvsStatus_1Pi0",10,0,10,10,0,10);
  TH2D* tail_1Pip = new TH2D("PDGvsStatus_1Pip","PDGvsStatus_1Pip",10,0,10,10,0,10);
  TH2D* tail_mPi = new TH2D("PDGvsStatus_mPi","PDGvsStatus_mPi",10,0,10,10,0,10);

  TH1D* tail1d = new TH1D("PDG_FS","PDG_FS",10,0,10);
  TH1D* tail1d_noPi = new TH1D("PDG_FS_noPi","PDG_FS_noPi",10,0,10);
  TH1D* tail1d_1Pi0 = new TH1D("PDG_FS_1Pi0","PDG_FS_1Pi0",10,0,10);
  TH1D* tail1d_1Pip = new TH1D("PDG_FS_1Pip","PDG_FS_1Pip",10,0,10);
  TH1D* tail1d_mPi = new TH1D("PDG_FS_mPi","PDG_FS_mPi",10,0,10);

  TH2D* part3[10];

  for(int tt=0;tt<10;tt++){
    part3[tt] = new TH2D("","",10,0,10,200,-1,1);
  }

  const char* pdgs[10] = {"mu+","mu-","pi+","pi-","pi0","proton","neutron","gamma","electron","others"};
  const char* stg[10] = {"IS", "FS", "Inter", "Dcy","Tgt", "DIS-pre", "RES-pre", "InNs", "rmnt", "cl.tgt."};

  TH1D* part2 = new TH1D("PDG_FS","PDG_FS",10,0,10);

  TVector3* vecMuon2;
  TVector3 vecMuonT;
  TVector3* vecOther2;
  TVector3* vecNu;

  TRandom *ran1 = new TRandom();
  TRandom *ran2 = new TRandom();

  double signn = 0;
  bool willDo1 = false;
  bool willDo2 = false;
  double totalTrans = 0;
  double vecMuon[3] = {};
  double vecOther[3] = {};
  double angleSmear = 0;
  double momSmear = 0;
  double totMom  = 0;
  double totMom2 = 0;
  double totMom3 = 0;
  double totMom4 = 0;
  double totMom_m  = 0;
  double totMom2_m = 0;
  double totMom3_m = 0;
  double totMom4_m = 0;
  double transX = 0;
  double transY = 0;

  double totRate = 5e6;

  double STVcut1 = 0.10000;
  double STVcut2 = 0.05000;
  double STVcut3 = 0.02000;  

  double muonThreshold = 0.1;
  //double pionThreshold = 0.1; 
  double pionThreshold = 0.01;
  double neutronThreshold = 0.01;
  //double protonThreshold = 0.3;
  double protonThreshold = 0.03;
  double electronThreshold = 0;

  double muonSmear = 0.04;
  double pipSmear = 0.10;
  double pi0Smear = 0.1;
  double electronSmear = 0.1;
  double protonSmear = 0.1;
  double neutronSmear = 0.2;

  int parHead0 = 0;
  int parHead  = 0;
  int parHead2 = 0;
  int parHead3 = 0;
  int parHead4 = 0;

  double electronMass = 0.5e-3;
  double muonMass     = 0.1057;
  double tauMass      = 1.77686;
  double pipMass      = 0.13957;
  double pi0Mass      = 0.13498;
  double protonMass   = 0.93827;
  double neutronMass  = 0.939565;
  double binding      = 0.068;
  //double binding      = 0;

  double counter1=0,counter2=0,counter3=0,counter4=0,counter5=0,counter6=0,counter7=0,counter8=0;
  double counter1_0Pi=0,counter2_0Pi=0,counter3_0Pi=0,counter4_0Pi=0,counter5_0Pi=0,counter6_0Pi=0,counter7_0Pi=0,counter8_0Pi=0;
  double counter1_1Pip=0,counter2_1Pip=0,counter3_1Pip=0,counter4_1Pip=0,counter5_1Pip=0,counter6_1Pip=0,counter7_1Pip=0,counter8_1Pip=0;
  double counter1_1Pi0=0,counter2_1Pi0=0,counter3_1Pi0=0,counter4_1Pi0=0,counter5_1Pi0=0,counter6_1Pi0=0,counter7_1Pi0=0,counter8_1Pi0=0;
  double counter1_mPi=0,counter2_mPi=0,counter3_mPi=0,counter4_mPi=0,counter5_mPi=0,counter6_mPi=0,counter7_mPi=0,counter8_mPi=0;
  double counterTail=0, counterTail_0Pi=0, counterTail_1Pip=0, counterTail_1Pi0=0,counterTail_mPi=0;

  Int_t nentries =  (Int_t) h1.GetEntries();
  int isCC = 0;

  //cout<<nentries <<endl;
  for(Int_t i=0; i< nentries ; i++) {

    h1.GetEntry(i);

    isCC = 0;
    for(Int_t j=0;j<5;j++){
      if(abs(StdHepPdg[j])== 13) isCC = 1;
    }

    if (isCC == 0) continue;

    if( vtx[0]>-1.1 && vtx[0]<1.1 && vtx[1]>-1.1 && vtx[1]<1.1 && vtx[2]>4.1 && vtx[2]<5.9){
    totMom     = 0;
    totMom2    = 0;
    totMom3    = 0;
    totMom4    = 0;
    totMom_m   = 0;
    totMom2_m  = 0;
    totMom3_m  = 0;
    totMom4_m  = 0;
    momSmear   = 0;
    angleSmear = 0;
    transX     = 0;
    transY     = 0;

    ran1->SetSeed(i* 100);
    ran2->SetSeed(i* 111+5);

    //STT: 2mrad angular and 5% energy; 3DST: 20 mrad and 20% energy
    angleSmear = ran1->Gaus(0,0.02);
    momSmear   = ran1->Gaus(1,0.0400);

    bool acpi = false;
    bool api0 = false;
    bool triggered = false;
    bool triggered2 = false;
    bool triggered3 = false;
    bool triggered4 = false;

    bool multiTag = false;

    int neutronN = 0;
    int pi0N = 0;
    int pipN = 0;
    int protonN = 0;

    std::cout<<"*********************** target is "<<StdHepPdg[1]<<std::endl;
    //cout<<i<<"............"<<endl;
    for(Int_t j=2;j<StdHepN;j++){

      if(abs(StdHepPdg[j])>=2000000000)  break;

      //cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;
      // proton 2212   neutron 2112
      //if( (abs(StdHepPdg[j])== 13 || abs(StdHepPdg[j])== 11 || abs(StdHepPdg[j])== 211 || abs(StdHepPdg[j])== 111 || abs(StdHepPdg[j])== 2212)  && StdHepStatus[j]==1){
      //if (abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1){
      //if (parHead0 > 3) break;
      if (StdHepPdg[0]== -14 && (abs(StdHepPdg[j])== 13 && StdHepStatus[j]==1) && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> muonThreshold){
        double currAng = TMath::ATan(imom[j][1]/imom[j][0])+gRandom->Gaus(0,0.02);
	double addedAng = TMath::Tan(currAng) * imom[j][0];
        transX += imom[j][0] * gRandom->Gaus(1,muonSmear);
	transY += addedAng * gRandom->Gaus(1,muonSmear);  
	//transY += imom[j][1];
	parHead0 ++;
      }

      if (StdHepPdg[0]== -14 && (abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1) && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])>pionThreshold ){
        double currAng = TMath::ATan(imom[j][1]/imom[j][0])+gRandom->Gaus(0,0.02);
        double addedAng = TMath::Tan(currAng) * imom[j][0];
        transX += imom[j][0] * gRandom->Gaus(1, pipSmear);
        transY += addedAng * gRandom->Gaus(1, pipSmear);
        //transY += imom[j][1];
        parHead0 ++;
	pipN ++;
      }

      if (StdHepPdg[0]== -14 && (abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1) && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])>pionThreshold ){
        transX += imom[j][0] * gRandom->Gaus(1,pi0Smear);
        transY += imom[j][1] * gRandom->Gaus(1,pi0Smear);
        parHead0 ++;
	pi0N ++;
      }

      if (StdHepPdg[0]== -14 && (abs(StdHepPdg[j])== 2112 && StdHepStatus[j]== 1) && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])>neutronThreshold ){
        //if(neutronN>0 || protonN>0){}
	//else{
          transX += imom[j][0]* gRandom->Gaus(1,neutronSmear);
          transY += imom[j][1]* gRandom->Gaus(1,neutronSmear);
	//}
	parHead0 ++;
	neutronN ++;
      }

      if (StdHepPdg[0]== -14 && (abs(StdHepPdg[j])== 2212 && StdHepStatus[j]== 1) && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> protonThreshold ){
	//if(neutronN>0 || protonN>0){}
	//else{
          transX += imom[j][0]* gRandom->Gaus(1,protonSmear);
          transY += imom[j][1]* gRandom->Gaus(1,protonSmear);
	//}
        parHead0 ++;
        if(imom[j][3]-protonMass > 5)
          protonN ++;
      }

      if (abs(StdHepPdg[j]) == 211 && StdHepStatus[j]== 1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])>pionThreshold ){ 
	acpi = true;
      }
      if (abs(StdHepPdg[j]) == 111 && StdHepStatus[j]== 1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])>pionThreshold ){ 
	api0 = true;
      }
    }

    if( neutronN == 1 && protonN == 0) multiTag = false;
    else multiTag = true;
    std::cout<<"transverse momentum is : "<<sqrt(transX*transX + transY*transY)<<std::endl;
    double transTot = transX*transX + transY*transY;
    
    bool cutType = false;
    if (pipN+pi0N == 0) cutType = true;
    cutType = true;

    int neutronN1 = 0;
    int pi0N1 = 0;
    int pipN1 = 0;
    int protonN1 = 0;

    double muonMom1 = 0; 
    double muonE1 = 0;
    double muonAng = 0.;
    //if(multiTag == false){

    if( StdHepPdg[0]== -14 && sqrt(transX*transX + transY*transY) < 10000000 && transTot > 0 && cutType && multiTag== false){

      std::cout<<"before energy loss : "<<imom[0][3]<<std::endl;
      totMom_m = imom[0][3];
      counter1++;
      triggered = true;

      cout<<"-----------------------------------------"<<endl;
      for(Int_t j=2;j<StdHepN;j++){
        if (parHead > 20 ) break;

        cout<<"order of particle "<<j<<" "
        <<"particle pdg "<<StdHepPdg[j]<<" "
        <<"particle status "<<StdHepStatus[j]<<endl;

        if(abs(StdHepPdg[j])== 2112&& StdHepStatus[j]==1){
	  counter2++; 
          totMom_m -= (imom[j][3]-neutronMass);
        }

	if(abs(StdHepPdg[j])>=2000000000)  break;
     
        int thisPDG = 0;
        if(StdHepPdg[j] == 13) thisPDG = 0;
        else if(StdHepPdg[j] == -13) thisPDG = 1;
        else if(StdHepPdg[j] == 211) thisPDG = 2;
        else if(StdHepPdg[j] == -211) thisPDG = 3;
        else if(StdHepPdg[j] == 111) thisPDG = 4;
        else if(StdHepPdg[j] == 2212) thisPDG = 5;
        else if(StdHepPdg[j] == 2112) thisPDG = 6;
        else if(StdHepPdg[j] == 22) thisPDG = 7;
        else if(abs(StdHepPdg[j]) == 11) thisPDG = 8;
        else  thisPDG = 9;

        int thisStatus = 0;
        if(StdHepStatus[j] == 0) thisStatus = 0;
        else if(StdHepStatus[j] == 1) thisStatus = 1;
        else if(StdHepStatus[j] == 2) thisStatus = 2;
        else if(StdHepStatus[j] == 3) thisStatus = 3;
        else if(StdHepStatus[j] == 11) thisStatus = 4;
        else if(StdHepStatus[j] == 12) thisStatus = 5;
        else if(StdHepStatus[j] == 13) thisStatus = 6;
        else if(StdHepStatus[j] == 14) thisStatus = 7;
        else if(StdHepStatus[j] == 15) thisStatus = 8;
        else if(StdHepStatus[j] == 16) thisStatus = 9;

        part1->Fill(thisPDG, thisStatus);

        if (StdHepStatus[j] == 1)
          part2->Fill(thisPDG);


        if(abs(StdHepPdg[j])== 13 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> muonThreshold){
          ran1->SetSeed(j * 10002);
          momSmear = ran1->Gaus(1,muonSmear);
	  muonMom1 = sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear;
	  muonE1 = sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(muonMass, 2) );
	  muonAng = imom[j][2] /( sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear); 
          totMom += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(muonMass, 2) );     
          //std::cout<<"muon "<<std::endl;
	  parHead ++;
	}

        else if(abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1  && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 34002);
          momSmear = ran1->Gaus(1,pipSmear);
          totMom += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
	  //std::cout<<"charged pion "<<std::endl;
	  parHead ++;
	  pipN1 ++;
        }
        else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 10002);
          momSmear = ran1->Gaus(1,pi0Smear);
	  //if(pi0N1 > 0)
	  //  totMom += 0;
	  //else
          totMom += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
	  //std::cout<<"pi0 "<<std::endl;
	  parHead ++;
	  pi0N1 ++;
        }
        else if(abs(StdHepPdg[j])== 11 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> electronThreshold){
          ran1->SetSeed(j * 10002);
          momSmear = ran1->Gaus(1,electronSmear);
          totMom += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(electronMass, 2) );
	  parHead ++;
        }
        else if(abs(StdHepPdg[j])== 2212 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> protonThreshold){
          ran1->SetSeed(j * 10002);
          momSmear = ran1->Gaus(1,protonSmear);
          if(protonN1 > 0 || neutronN1 > 0)
            totMom += 0; //sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) );
	  else 
            totMom += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(protonMass, 2) );
	  parHead ++;
	  protonN1 ++;
        }

        else if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> neutronThreshold){
          ran1->SetSeed(j * 11002);
          momSmear = ran1->Gaus(1,neutronSmear);
	  if(neutronN1 > 0 || protonN1 > 0)
            totMom += 0; // sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) ) ;
	  else
            totMom += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(neutronMass, 2) ) ;

	  neutronN1 ++;
	  totMom -= imom[j][3]-neutronMass;

	  //std::cout<<"neutron "<<std::endl;
	  //break;
	  parHead ++;
        }
      }

      if(pi0N1 == 0 && pipN1 == 0) counter1_0Pi ++;
      if(pi0N1 == 1 && pipN1 == 0) counter1_1Pi0 ++;
      if(pi0N1 == 0 && pipN1 == 1) counter1_1Pip ++;
      if((pi0N1 == 1 && pipN1 == 1) || pi0N1 >1 || pipN1 >1) counter1_mPi ++;

      totMom -= protonMass ;
      //if(protonN) totMom -= protonMass;
      totMom += binding;
      //if (parHead == 2 ) totMom -= neutronMass;
      ran1->SetSeed(i * 10002);
      momSmear = ran1->Gaus(1,muonSmear);
      //cout<<"smearing "<<momSmear<<endl;
      //std::cout<<"after energy loss : "<<totMom_m<<std::endl;
      totMom_m *= momSmear;
      //std::cout<<"after smearing : "<<totMom_m<<std::endl;
      h2D[0]->Fill(totMom, imom[0][3]);

      //if(pi0N1 == 0 && pipN1 == 0 ){
      //  totMom = (protonMass*protonMass - neutronMass * neutronMass - muonMass * muonMass + 2 * neutronMass*muonE1)/(2* (neutronMass - muonE1+ muonMom1 * muonAng) );
      //}

      if((totMom - imom[0][3]) / imom[0][3]<-0.2){

	counterTail++;
        if(pi0N1 == 0 && pipN1 == 0) counterTail_0Pi ++;
        if(pi0N1 == 1 && pipN1 == 0) counterTail_1Pi0 ++;
        if(pi0N1 == 0 && pipN1 == 1) counterTail_1Pip ++;
        if((pi0N1 == 1 && pipN1 == 1) || pi0N1 >1 || pipN1 >1) counterTail_mPi ++;

        for(Int_t aj=2;aj<StdHepN;aj++){

          if(abs(StdHepPdg[aj])>=2000000000)  break;

          int thisPDG = 0;
          if(StdHepPdg[aj] == 13) thisPDG = 0;
          else if(StdHepPdg[aj] == -13) thisPDG = 1;
          else if(StdHepPdg[aj] == 211) thisPDG = 2;
          else if(StdHepPdg[aj] == -211) thisPDG = 3;
          else if(StdHepPdg[aj] == 111) thisPDG = 4;
          else if(StdHepPdg[aj] == 2212) thisPDG = 5;
          else if(StdHepPdg[aj] == 2112) thisPDG = 6;
          else if(StdHepPdg[aj] == 22) thisPDG = 7;
          else if(abs(StdHepPdg[aj]) == 11) thisPDG = 8;
          else  thisPDG = 9;

          int thisStatus = 0;
          if(StdHepStatus[aj] == 0) thisStatus = 0;
          else if(StdHepStatus[aj] == 1) thisStatus = 1;
          else if(StdHepStatus[aj] == 2) thisStatus = 2;
          else if(StdHepStatus[aj] == 3) thisStatus = 3;
          else if(StdHepStatus[aj] == 11) thisStatus = 4;
          else if(StdHepStatus[aj] == 12) thisStatus = 5;
          else if(StdHepStatus[aj] == 13) thisStatus = 6;
          else if(StdHepStatus[aj] == 14) thisStatus = 7;
          else if(StdHepStatus[aj] == 15) thisStatus = 8;
          else if(StdHepStatus[aj] == 16) thisStatus = 9;

          tail->Fill(thisPDG, thisStatus);
	  tail1d->Fill(thisPDG);
          if(pi0N1 == 0 && pipN1 == 0) {
	    tail_noPi->Fill(thisPDG, thisStatus);
	    tail1d_noPi->Fill(thisPDG);
	  }
          if(pi0N1 == 1 && pipN1 == 0) {
	    tail_1Pi0->Fill(thisPDG, thisStatus);
            tail1d_1Pi0->Fill(thisPDG);
	  }
          if(pi0N1 == 0 && pipN1 == 1) {
	    tail_1Pip->Fill(thisPDG, thisStatus);
            tail1d_1Pip->Fill(thisPDG);
	  }
          if((pi0N1 == 1 && pipN1 == 1) || pi0N1 >1 || pipN1 >1) {
	    tail_mPi->Fill(thisPDG, thisStatus);
            tail1d_mPi->Fill(thisPDG);
	  }
        }
      }
    }

//************************************************************************************************************
////************************************************************************************************************

    int neutronN2 = 0;
    int pi0N2 = 0;
    int pipN2 = 0;
    int protonN2 = 0;

    if( StdHepPdg[0]== -14 && sqrt(transX*transX + transY*transY) < STVcut1 && transTot > 0 && cutType && multiTag == false){
      totMom2_m = imom[0][3];
      counter3++;
      triggered2 = true;

      for(Int_t j=2;j<StdHepN;j++){
        if (parHead2 > 20 ) break;
	if(abs(StdHepPdg[j])== 2112&& StdHepStatus[j]==1){
	  counter4++;
	  totMom2_m -= (imom[j][3]-neutronMass);
	}

        if(abs(StdHepPdg[j])>=2000000000)  break;

        if(abs(StdHepPdg[j])== 13 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> muonThreshold){
          ran1->SetSeed(j * 1002);
          momSmear = ran1->Gaus(1,muonSmear);
          totMom2 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(muonMass, 2) );
	  parHead2 ++;
        }
        else if(abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 1002);
          momSmear = ran1->Gaus(1,pipSmear);
          totMom2 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
	  pipN2 ++;
	  parHead2 ++;
        }
        else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 1002);
          momSmear = ran1->Gaus(1,pi0Smear);
          totMom2 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
	  parHead2 ++;
	  pi0N2 ++;
        }
        else if(abs(StdHepPdg[j])== 11 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> electronThreshold){
          ran1->SetSeed(j * 1002);
          momSmear = ran1->Gaus(1,electronSmear);
          totMom2 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(electronMass, 2) );
	  parHead2 ++;
        }
        else if(abs(StdHepPdg[j])== 2212 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> protonThreshold){
          ran1->SetSeed(j * 1002);
          momSmear = ran1->Gaus(1,protonSmear);
	  if (protonN2 > 0 || neutronN2 > 0)
	    totMom2 += 0;
	  else
            totMom2 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(protonMass, 2) );
	  parHead2 ++;
	  protonN2 ++;
        }
        else if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> neutronThreshold){
          ran1->SetSeed(j * 11002);
          momSmear = ran1->Gaus(1,neutronSmear);
	  if (protonN2>0 || neutronN2>0)
	    totMom2 += 0;
	  else
            totMom2 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(neutronMass, 2) );
	  parHead2 ++;
	  neutronN2 ++;
        }
      }

      if(pi0N2 == 0 && pipN2 == 0) counter3_0Pi ++;
      if(pi0N2 == 1 && pipN2 == 0) counter3_1Pi0 ++;
      if(pi0N2 == 0 && pipN2 == 1) counter3_1Pip ++;
      if((pi0N2 == 1 && pipN2 == 1) || pi0N2 >1 || pipN2 >1) counter3_mPi ++;

      totMom2 -= protonMass;
      totMom2 += binding;
      //if(parHead2 == 2 ) totMom2 -= neutronMass;
      ran1->SetSeed(i * 1002);
      momSmear = ran1->Gaus(1,muonSmear);
      totMom2_m *= momSmear;
      h2D[1]->Fill(totMom2, imom[0][3]);
    }

//************************************************************************************************************
//************************************************************************************************************

    int neutronN3 = 0;
    int pi0N3 = 0;
    int pipN3 = 0;
    int protonN3 = 0;

    if( StdHepPdg[0]== -14 && sqrt(transX*transX + transY*transY) < STVcut2 && transTot > 0 && cutType && multiTag == false){
      counter5++;
      totMom3_m = imom[0][3];
      triggered3 = true;

      for(Int_t j=2;j<StdHepN;j++){
        if (parHead3 > 20 ) break;
        if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1){
	  counter6++;
          totMom3_m -= (imom[j][3]-neutronMass);
        }

        if(abs(StdHepPdg[j])>=2000000000)  break;

        if(abs(StdHepPdg[j])== 13 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> muonThreshold){
          ran1->SetSeed(j * 102);
          momSmear = ran1->Gaus(1,muonSmear);
          totMom3 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(muonMass, 2) );
	  parHead3 ++;
        }
        else if(abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 102);
          momSmear = ran1->Gaus(1,pipSmear);
          totMom3 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
	  pipN3 ++;
	  parHead3 ++;
        }
        else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 102);
          momSmear = ran1->Gaus(1,pi0Smear);
          totMom3 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
	  pi0N3 ++;
	  parHead3 ++;
        }
        else if(abs(StdHepPdg[j])== 11 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> electronThreshold){
          ran1->SetSeed(j * 102);
          momSmear = ran1->Gaus(1,electronSmear);
          totMom3 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(electronMass, 2) );
	  parHead3 ++;
        }
        else if(abs(StdHepPdg[j])== 2212 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> protonThreshold){
          ran1->SetSeed(j * 102);
          momSmear = ran1->Gaus(1,protonSmear);
          if (protonN3>0 || neutronN3>0)
            totMom3 += 0;
          else
            totMom3 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(protonMass, 2) );
	  parHead3 ++;
	  protonN3 ++;
        }

        else if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> neutronThreshold){
          ran1->SetSeed(j * 11002);
          momSmear = ran1->Gaus(1,neutronSmear);
          if (protonN3>0 || neutronN3>0)
            totMom3 += 0;
          else
            totMom3 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(neutronMass, 2) );
	  parHead3 ++;
	  neutronN3 ++;
        }
      }
      if(pi0N3 == 0 && pipN3 == 0) counter5_0Pi ++;
      if(pi0N3 == 1 && pipN3 == 0) counter5_1Pi0 ++;
      if(pi0N3 == 0 && pipN3 == 1) counter5_1Pip ++;
      if((pi0N3 == 1 && pipN3 == 1) || pi0N3 >1 || pipN3 >1) counter5_mPi ++;

      totMom3 -= protonMass;
      totMom3 += binding;
      ran1->SetSeed(i * 102);
      momSmear = ran1->Gaus(1,muonSmear);
      totMom3_m *= momSmear;
      h2D[2]->Fill(totMom3, imom[0][3]);

      if( StdHepPdg[1]> 10000 ) 
	hC_noPi->Fill((totMom3  - imom[0][3]) / imom[0][3]);
      if( StdHepPdg[1]== 2212 || StdHepPdg[1] == 2112 )
        hH_noPi->Fill((totMom3  - imom[0][3]) / imom[0][3]);
    }

//*******************************************************************************************************
//*******************************************************************************************************

    int neutronN4 = 0;
    int pi0N4 = 0;
    int pipN4 = 0;
    int protonN4 = 0;

    if( StdHepPdg[0]== -14 && sqrt(transX*transX + transY*transY) < STVcut3 && transTot > 0 && cutType && multiTag == false){
      counter7++;
      totMom4_m = imom[0][3];
      triggered4 = true;

      for(Int_t j=2;j<StdHepN;j++){
	if (parHead4 > 20) break;
        if(abs(StdHepPdg[j])== 2112&& StdHepStatus[j]==1){
	  counter8++;
          totMom4_m -= (imom[j][3]-neutronMass);
	  //std::cout<<"neutron energy loss is : "<<totMom4_m<<std::endl;
        }

        if(abs(StdHepPdg[j])>=2000000000)  break;

        if(abs(StdHepPdg[j])== 13 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> muonThreshold){
          ran1->SetSeed(j * 12);
          momSmear = ran1->Gaus(1,muonSmear);
          totMom4 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(muonMass, 2) );
	  parHead4 ++;
        }

        else if(abs(StdHepPdg[j])== 211 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 12);
          momSmear = ran1->Gaus(1,pipSmear);
          totMom4 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pipMass, 2) );
	  pipN4 ++;
	  parHead4 ++;
        }
        else if(abs(StdHepPdg[j])== 111 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> pionThreshold){
          ran1->SetSeed(j * 12);
          momSmear = ran1->Gaus(1,pi0Smear);
          totMom4 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(pi0Mass, 2) );
	  pi0N4 ++;
	  parHead4 ++;
        }
        else if(abs(StdHepPdg[j])== 11 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> electronThreshold){
          ran1->SetSeed(j * 12);
          momSmear = ran1->Gaus(1,electronSmear);
          totMom4 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(electronMass, 2) );
	  parHead4 ++;
        }

        else if(abs(StdHepPdg[j])== 2212 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> protonThreshold){
          ran1->SetSeed(j * 12);
          momSmear = ran1->Gaus(1,protonSmear);
          if (protonN4>0 || neutronN4>0)
            totMom4 += 0;
          else
            totMom4 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(protonMass, 2) );
	  protonN4 ++;
	  parHead4 ++;
        }

        else if(abs(StdHepPdg[j])== 2112 && StdHepStatus[j]==1 && sqrt(imom[j][0]*imom[j][0] + imom[j][1]*imom[j][1] + imom[j][2]*imom[j][2])> neutronThreshold){
          ran1->SetSeed(j * 11002);
          momSmear = ran1->Gaus(1,neutronSmear);
          if (protonN4>0 || neutronN4>0)
            totMom4 += 0;
          else
            totMom4 += sqrt(TMath::Power(sqrt(imom[j][0]*imom[j][0]+imom[j][1]*imom[j][1]+ imom[j][2]*imom[j][2]) * momSmear,2) + TMath::Power(neutronMass, 2) );
	  neutronN4 ++;
	  parHead4 ++;
        }
      }
      if(pi0N4 == 0 && pipN4 == 0) counter7_0Pi ++;
      if(pi0N4 == 1 && pipN4 == 0) counter7_1Pi0 ++;
      if(pi0N4 == 0 && pipN4 == 1) counter7_1Pip ++;
      if((pi0N4 == 1 && pipN4 == 1) || pi0N4 >1 || pipN4 >1) counter7_mPi ++;

      totMom4 -= protonMass;
      totMom4 += binding;
      ran1->SetSeed(i * 12);
      momSmear = ran1->Gaus(1,0.0400);
      totMom4_m *= momSmear;
      h2D[3]->Fill(totMom4, imom[0][3]);
    }

    parHead0 = 0;
    parHead  = 0;
    parHead2 = 0;
    parHead3 = 0;
    parHead4 = 0;

    if(triggered == true ){
    if(pi0N1 == 0 && pipN1 == 0){
      h2D_noPi[0]->Fill(totMom, imom[0][3]);
      hCarbon_noPi  -> Fill((totMom  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N2 == 0 && pipN2 == 0 && triggered2 == true && multiTag == false){
      h2D_noPi[1]->Fill(totMom2, imom[0][3]);
      hCarbon2_noPi  -> Fill((totMom2  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N3 == 0 && pipN3 == 0 && triggered3 == true && multiTag == false){
      h2D_noPi[2]->Fill(totMom3, imom[0][3]);
      hCarbon3_noPi  -> Fill((totMom3  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N4 == 0 && pipN4 == 0 && triggered4 == true && multiTag == false){
      h2D_noPi[3]->Fill(totMom4, imom[0][3]);
      hCarbon4_noPi  -> Fill((totMom4  - imom[0][3]) / imom[0][3]);
    }

    if(pi0N1 == 1 && pipN1 == 0){
      h2D_1Pi0[0]->Fill(totMom, imom[0][3]);
      hCarbon_1Pi0  -> Fill((totMom  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N2 == 1 && pipN2 == 0 && multiTag == false){
      h2D_1Pi0[1]->Fill(totMom2, imom[0][3]);
      hCarbon2_1Pi0  -> Fill((totMom2  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N3 == 1 && pipN3 == 0 && multiTag == false){
      h2D_1Pi0[2]->Fill(totMom3, imom[0][3]);
      hCarbon3_1Pi0  -> Fill((totMom3  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N4 == 1 && pipN4 == 0 && multiTag == false){
      h2D_1Pi0[3]->Fill(totMom4, imom[0][3]);    
      hCarbon4_1Pi0  -> Fill((totMom4  - imom[0][3]) / imom[0][3]);
    }

    if(pi0N1 == 0 && pipN1 == 1){
      h2D_1Pip[0]->Fill(totMom, imom[0][3]);
      hCarbon_1Pip  -> Fill((totMom  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N2 == 0 && pipN2 == 1 && multiTag == false){
      h2D_1Pip[1]->Fill(totMom2, imom[0][3]);
      hCarbon2_1Pip  -> Fill((totMom2  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N3 == 0 && pipN3 == 1 && multiTag == false){
      h2D_1Pip[2]->Fill(totMom3, imom[0][3]);
      hCarbon3_1Pip  -> Fill((totMom3  - imom[0][3]) / imom[0][3]);
    }
    if(pi0N4 == 0 && pipN4 == 1 && multiTag == false){
      h2D_1Pip[3]->Fill(totMom4, imom[0][3]);
      hCarbon4_1Pip  -> Fill((totMom4  - imom[0][3]) / imom[0][3]);
    }

    if((pi0N1 == 1 && pipN1 == 1) || pi0N1 >1 || pipN1 >1){
      h2D_mPi[0]->Fill(totMom, imom[0][3]);
      hCarbon_mPi  -> Fill((totMom  - imom[0][3]) / imom[0][3]);
    }
    if(((pi0N2 == 1 && pipN2 == 1) || pi0N2 >1 || pipN2 >1) && multiTag == false){
      h2D_mPi[1]->Fill(totMom2, imom[0][3]);
      hCarbon2_mPi  -> Fill((totMom2  - imom[0][3]) / imom[0][3]);
    }
    if(((pi0N3 == 1 && pipN3 == 1) || pi0N3 >1 || pipN3 >1) && multiTag == false){
      h2D_mPi[2]->Fill(totMom3, imom[0][3]);
      hCarbon3_mPi  -> Fill((totMom3  - imom[0][3]) / imom[0][3]);
    }
    if(((pi0N4 == 1 && pipN4 == 1) || pi0N4 >1 || pipN4 >1) && multiTag == false){
      h2D_mPi[3]->Fill(totMom4, imom[0][3]);
      hCarbon4_mPi  -> Fill((totMom4  - imom[0][3]) / imom[0][3]);
    }

    if ( (totMom  - imom[0][3]) / imom[0][3]>-1 && (totMom  - imom[0][3]) / imom[0][3]<0.9 ){
      hCarbon  -> Fill((totMom  - imom[0][3]) / imom[0][3]);
      part3[0] -> Fill(neutronN, (totMom  - imom[0][3]) / imom[0][3]);
      part3[1] -> Fill(pipN, (totMom  - imom[0][3]) / imom[0][3]);
      part3[2] -> Fill(pi0N, (totMom  - imom[0][3]) / imom[0][3]);
      part3[3] -> Fill(protonN, (totMom  - imom[0][3]) / imom[0][3]);
    }
    if ( (totMom2  - imom[0][3]) / imom[0][3]>-1 && (totMom2  - imom[0][3]) / imom[0][3]<0.9 && multiTag == false)
      hCarbon2 -> Fill((totMom2 - imom[0][3]) / imom[0][3]);
    if ( (totMom3  - imom[0][3]) / imom[0][3]>-1 && (totMom3  - imom[0][3]) / imom[0][3]<0.9 && multiTag == false)
      hCarbon3 -> Fill((totMom3 - imom[0][3]) / imom[0][3]);
    if ( (totMom4  - imom[0][3]) / imom[0][3]>-1 && (totMom4  - imom[0][3]) / imom[0][3]<0.9 && multiTag == false)
      hCarbon4 -> Fill((totMom4 - imom[0][3]) / imom[0][3]);    

    hCarbon_m  -> Fill((totMom_m  - imom[0][3]) / imom[0][3]);
    hCarbon2_m -> Fill((totMom2_m - imom[0][3]) / imom[0][3]);
    hCarbon3_m -> Fill((totMom3_m - imom[0][3]) / imom[0][3]);
    hCarbon4_m -> Fill((totMom4_m - imom[0][3]) / imom[0][3]);
    }
  //}
  }
  }
  //THStack* hs1= new THStack("hs","#delta P_{T} (GeV)");
  //hCarbon2->SetFillColor(kBlack);
  //hHydrogen2->SetFillColor(kRed);
  //hs1->Add(hCarbon2);
  //hs1->Add(hHydrogen2);

  cout<<"total number of events is "<<nentries<<endl;
  cout<<"events that pass STV cut 1, 2, 3 and 4 are : "<<counter1<<" "<<counter3<<" "<<counter5<<" "<<counter7<<" "<<endl;
  cout<<"events that pass STV cut 1, 2, 3 and 4 and having neutron energy loss are : "<<counter2<<" "<<counter4<<" "<<counter6<<" "<<counter8<<" "<<endl;

  cout<<"integrated 2D "<<h2D[0]->Integral()<<" "<<h2D[1]->Integral()<<" "<<h2D[2]->Integral()<<" "<<h2D[3]->Integral()<<" "<<endl;
  //hCarbon2->Scale(hCarbon->Integral(50,150)/hCarbon2->Integral(50,150));
  //hCarbon3->Scale(hCarbon->Integral(50,150)/hCarbon3->Integral(50,150));
  //hCarbon4->Scale(hCarbon->Integral(50,150)/hCarbon4->Integral(50,150));

  hCarbon2_m->Scale(hCarbon_m->Integral(50,150)/hCarbon2_m->Integral(50,150));
  hCarbon3_m->Scale(hCarbon_m->Integral(50,150)/hCarbon3_m->Integral(50,150));
  hCarbon4_m->Scale(hCarbon_m->Integral(50,150)/hCarbon4_m->Integral(50,150));

  //hCarbon->Scale(13.6e6*0.3*0.45/hCarbon->Integral(50,150));
  //hCarbon2->Scale(13.6e6*0.3*0.45/hCarbon2->Integral(50,150));
  //hCarbon3->Scale(13.6e6*0.3*0.45/hCarbon3->Integral(50,150));
  //hCarbon4->Scale(13.6e6*0.3*0.45/hCarbon4->Integral(50,150));

  hCarbon->Scale(1./hCarbon->Integral(50,150));
  hCarbon2->Scale(1./hCarbon2->Integral(50,150));
  hCarbon3->Scale(1./hCarbon3->Integral(50,150));
  hCarbon4->Scale(1./hCarbon4->Integral(50,150));
  hCarbon_noPi->Scale(1./hCarbon_noPi->Integral(50,150));
  hCarbon2_noPi->Scale(1./hCarbon2_noPi->Integral(50,150));
  hCarbon3_noPi->Scale(1./hCarbon3_noPi->Integral(50,150));
  hCarbon4_noPi->Scale(1./hCarbon4_noPi->Integral(50,150));
  hCarbon_1Pip->Scale(1./hCarbon_1Pip->Integral(50,150));
  hCarbon2_1Pip->Scale(1./hCarbon2_1Pip->Integral(50,150));
  hCarbon3_1Pip->Scale(1./hCarbon3_1Pip->Integral(50,150));
  hCarbon4_1Pip->Scale(1./hCarbon4_1Pip->Integral(50,150));
  hCarbon_1Pi0->Scale(1./hCarbon_1Pi0->Integral(50,150));
  hCarbon2_1Pi0->Scale(1./hCarbon2_1Pi0->Integral(50,150));
  hCarbon3_1Pi0->Scale(1./hCarbon3_1Pi0->Integral(50,150));
  hCarbon4_1Pi0->Scale(1./hCarbon4_1Pi0->Integral(50,150));
  hCarbon_mPi->Scale(1./hCarbon_mPi->Integral(50,150));
  hCarbon2_mPi->Scale(1./hCarbon2_mPi->Integral(50,150));
  hCarbon3_mPi->Scale(1./hCarbon3_mPi->Integral(50,150));
  hCarbon4_mPi->Scale(1./hCarbon4_mPi->Integral(50,150));

  cout<<"RMS values : "<<hCarbon->GetRMS()<<" "<<hCarbon2->GetRMS()<<" "<<hCarbon3->GetRMS()<<" "<<hCarbon4->GetRMS()<<endl;
  cout<<"RMS values noPi : "<<hCarbon_noPi->GetRMS()<<" "<<hCarbon2_noPi->GetRMS()<<" "<<hCarbon3_noPi->GetRMS()<<" "<<hCarbon4_noPi->GetRMS()<<endl;
  cout<<"RMS values 1Pip : "<<hCarbon_1Pip->GetRMS()<<" "<<hCarbon2_1Pip->GetRMS()<<" "<<hCarbon3_1Pip->GetRMS()<<" "<<hCarbon4_1Pip->GetRMS()<<endl;
  cout<<"RMS values 1Pi0 : "<<hCarbon_1Pi0->GetRMS()<<" "<<hCarbon2_1Pi0->GetRMS()<<" "<<hCarbon3_1Pi0->GetRMS()<<" "<<hCarbon4_1Pi0->GetRMS()<<endl;
  cout<<"RMS values mPi  : "<<hCarbon_mPi->GetRMS()<<" "<<hCarbon2_mPi->GetRMS()<<" "<<hCarbon3_mPi->GetRMS()<<" "<<hCarbon4_mPi->GetRMS()<<endl;

  cout<<"---------------------------------- checking the event rate ------------------------------------------"<<endl;
  cout<<counter1<<" "<<counter3<<" "<<counter5<<" "<<counter7<<endl;
  cout<<counter1_0Pi<<" "<<counter3_0Pi<<" "<<counter5_0Pi<<" "<<counter7_0Pi<<endl;
  cout<<counter1_1Pip<<" "<<counter3_1Pip<<" "<<counter5_1Pip<<" "<<counter7_1Pip<<endl;
  cout<<counter1_1Pi0<<" "<<counter3_1Pi0<<" "<<counter5_1Pi0<<" "<<counter7_1Pi0<<endl;
  cout<<counter1_mPi<<" "<<counter3_mPi<<" "<<counter5_mPi<<" "<<counter7_mPi<<endl;

  h2D[0]->Scale(totRate*0.9*0.45* (1/8.7) *(counter1/counter1)/h2D[0]->Integral());
  h2D[1]->Scale(totRate*0.9*0.45* (1/8.7) * (13960/23370.) * (counter3/counter1)/h2D[1]->Integral());
  h2D[2]->Scale(totRate*0.9*0.45* (1/8.7) * (3745/6277.) * (counter5/counter1)/h2D[2]->Integral());
  h2D[3]->Scale(totRate*0.9*0.45* (1/8.7) * (646/1114.) * (counter7/counter1)/h2D[3]->Integral());

  h2D_noPi[0]->Scale(totRate*0.9*0.45* (1/8.7) * (counter1_0Pi/counter1)/h2D_noPi[0]->Integral());
  h2D_noPi[1]->Scale(totRate*0.9*0.45* (1/8.7) * (9578./16267.) *(counter3_0Pi/counter1)/h2D_noPi[1]->Integral());
  h2D_noPi[2]->Scale(totRate*0.9*0.45* (1/8.7) * (2624./4424.) *(counter5_0Pi/counter1)/h2D_noPi[2]->Integral());
  h2D_noPi[3]->Scale(totRate*0.9*0.45* (1/8.7) * (460./821.) *(counter7_0Pi/counter1)/h2D_noPi[3]->Integral());

  h2D_1Pip[0]->Scale(totRate*0.9*0.45* (1/8.7) *(counter1_1Pip/counter1)/h2D_1Pip[0]->Integral());
  h2D_1Pip[1]->Scale(totRate*0.9*0.45* (1/8.7) * (3133./5129.) *(counter3_1Pip/counter1)/h2D_1Pip[1]->Integral());
  h2D_1Pip[2]->Scale(totRate*0.9*0.45* (1/8.7) * (806./1337.) *(counter5_1Pip/counter1)/h2D_1Pip[2]->Integral());
  h2D_1Pip[3]->Scale(totRate*0.9*0.45* (1/8.7) * (125./200.) *(counter7_1Pip/counter1)/h2D_1Pip[3]->Integral());

  h2D_1Pi0[0]->Scale(totRate*0.9*0.45* (1/8.7) *(counter1_1Pi0/counter1)/h2D_1Pi0[0]->Integral());
  h2D_1Pi0[1]->Scale(totRate*0.9*0.45* (1/8.7) * (955./1421.) *(counter3_1Pi0/counter1)/h2D_1Pi0[1]->Integral());
  h2D_1Pi0[2]->Scale(totRate*0.9*0.45* (1/8.7) * (240./376.) *(counter5_1Pi0/counter1)/h2D_1Pi0[2]->Integral());
  h2D_1Pi0[3]->Scale(totRate*0.9*0.45* (1/8.7) * (52./71.) *(counter7_1Pi0/counter1)/h2D_1Pi0[3]->Integral());

  h2D_mPi[0]->Scale(totRate*0.9*0.45* (1/8.7) *(counter1_mPi/counter1)/h2D_mPi[0]->Integral());
  h2D_mPi[1]->Scale(totRate*0.9*0.45* (1/8.7) * (294./553.) *(counter3_mPi/counter1)/h2D_mPi[1]->Integral());
  h2D_mPi[2]->Scale(totRate*0.9*0.45* (1/8.7) * (75./140.) *(counter5_mPi/counter1)/h2D_mPi[2]->Integral());
  h2D_mPi[3]->Scale(totRate*0.9*0.45* (1/8.7) * (9./22.) *(counter7_mPi/counter1)/h2D_mPi[3]->Integral());

  cout<<"********************* event rates:"<<endl;
  cout<<totRate*0.9*0.45* (1/8.7) *(counter1/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (13960/23370.) * (counter3/counter1)<<" "<<
  totRate*0.9*0.45* (1/8.7) * (3745/6277.) * (counter5/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (646/1114.) * (counter7/counter1)<<endl;
  cout<<totRate*0.9*0.45* (1/8.7) * (counter1_0Pi/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (9578./16267.) *(counter3_0Pi/counter1)<<" "<<
  totRate*0.9*0.45* (1/8.7) * (2624./4424.) *(counter5_0Pi/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (460./821.) *(counter7_0Pi/counter1)<<endl;
  cout<<totRate*0.9*0.45* (1/8.7) *(counter1_1Pip/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (3133./5129.) *(counter3_1Pip/counter1)<<" "<<
  totRate*0.9*0.45* (1/8.7) * (806./1337.) *(counter5_1Pip/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (125./200.) *(counter7_1Pip/counter1)<<endl;
  cout<<totRate*0.9*0.45* (1/8.7) *(counter1_1Pi0/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (955./1421.) *(counter3_1Pi0/counter1)<<" "<<
  totRate*0.9*0.45* (1/8.7) * (240./376.) *(counter5_1Pi0/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (52./71.) *(counter7_1Pi0/counter1)<<endl;
  cout<<totRate*0.9*0.45* (1/8.7) *(counter1_mPi/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (294./553.) *(counter3_mPi/counter1)<<" "<<
  totRate*0.9*0.45* (1/8.7) * (75./140.) *(counter5_mPi/counter1)<<" "<<totRate*0.9*0.45* (1/8.7) * (9./22.) *(counter7_mPi/counter1)<<endl;

  cout<<"per STV cut "<<endl;
  cout<<h2D[0]->Integral()<<endl;
  cout<<h2D[1]->Integral()<<endl;
  cout<<h2D[2]->Integral()<<endl;
  cout<<h2D[3]->Integral()<<endl;

  TCanvas* c0 =new TCanvas();

  hCarbon ->SetLineColor(1);
  hCarbon2->SetLineColor(2);
  hCarbon3->SetLineColor(3);
  hCarbon4->SetLineColor(4);
  hCarbon->Draw("hist");
  hCarbon->GetXaxis()->SetTitle("(E_{Reco} - E_{True}) / E_{True}");
  hCarbon->GetYaxis()->SetTitle("A.U.");
  hCarbon->GetXaxis()->SetRangeUser(-1,1);
  hCarbon->GetYaxis()->SetRangeUser(0,0.2);
  hCarbon2->Draw("hist same");
  hCarbon3->Draw("hist same");
  //hCarbon4->Draw("hist same");

  TLegend* leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon ,"no STV cut","l");
  leg->AddEntry(hCarbon2 ,"100 MeV STV cut","l");
  leg->AddEntry(hCarbon3 ,"50 MeV STV cut","l");
  //leg->AddEntry(hCarbon4 ,"10 MeV STV cut","l");
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


  TCanvas* c1 =new TCanvas();

  hCarbon_m ->SetLineColor(1);
  hCarbon2_m->SetLineColor(2);
  hCarbon3_m->SetLineColor(3);
  hCarbon4_m->SetLineColor(4);
  hCarbon_m->Draw("hist");
  hCarbon_m->GetXaxis()->SetTitle("(E_{Reco} - E_{True}) / E_{True}");
  hCarbon_m->GetYaxis()->SetTitle("Events");
  //hCarbon2_m->Draw("same");
  hCarbon3_m->Draw("hist same");
  hCarbon4_m->Draw("hist same");
  hCarbon_m->GetYaxis()->SetRangeUser(0, nentries*0.07);

  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon_m ,"no STV cut","l");
  //leg->AddEntry(hCarbon2_m ,"100 MeV STV cut","l");
  leg->AddEntry(hCarbon3_m ,"50 MeV STV cut","l");
  leg->AddEntry(hCarbon4_m ,"20 MeV STV cut","l");
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

  TCanvas* c1_bd = new TCanvas();
  c1_bd->Divide(2,2);
  c1_bd->cd(1);
  hCarbon_noPi ->SetLineColor(1);
  hCarbon2_noPi->SetLineColor(2);
  hCarbon3_noPi->SetLineColor(3);
  hCarbon4_noPi->SetLineColor(4);
  hCarbon_noPi->Draw("hist");
  hCarbon_noPi->GetXaxis()->SetTitle("(E_{Reco} - E_{True}) / E_{True}");
  hCarbon_noPi->GetYaxis()->SetTitle("A.U.");
  hCarbon_noPi->GetXaxis()->SetRangeUser(-1,1);
  hCarbon_noPi->GetYaxis()->SetRangeUser(0,0.2);
  hCarbon_noPi->SetTitle("CC0#pi");
  hCarbon2_noPi->Draw("hist same");
  hCarbon3_noPi->Draw("hist same");
  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon_noPi ,"no STV cut","l");
  leg->AddEntry(hCarbon2_noPi ,"100 MeV STV cut","l");
  leg->AddEntry(hCarbon3_noPi ,"50 MeV STV cut","l");
  leg->Draw();
  c1_bd->cd(2);
  hCarbon_1Pip ->SetLineColor(1);
  hCarbon2_1Pip->SetLineColor(2);
  hCarbon3_1Pip->SetLineColor(3);
  hCarbon4_1Pip->SetLineColor(4);
  hCarbon_1Pip->Draw("hist");
  hCarbon_1Pip->GetXaxis()->SetTitle("(E_{Reco} - E_{True}) / E_{True}");
  hCarbon_1Pip->GetYaxis()->SetTitle("A.U.");
  hCarbon_1Pip->GetXaxis()->SetRangeUser(-1,1);
  hCarbon_1Pip->GetYaxis()->SetRangeUser(0,0.2);
  hCarbon_1Pip->SetTitle("CC1#pi-");
  hCarbon2_1Pip->Draw("hist same");
  hCarbon3_1Pip->Draw("hist same");
  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon_1Pip ,"no STV cut","l");
  leg->AddEntry(hCarbon2_1Pip ,"100 MeV STV cut","l");
  leg->AddEntry(hCarbon3_1Pip ,"50 MeV STV cut","l");
  leg->Draw();
  c1_bd->cd(3);
  hCarbon_1Pi0 ->SetLineColor(1);
  hCarbon2_1Pi0->SetLineColor(2);
  hCarbon3_1Pi0->SetLineColor(3);
  hCarbon4_1Pi0->SetLineColor(4);
  hCarbon_1Pi0->Draw("hist");
  hCarbon_1Pi0->GetXaxis()->SetTitle("(E_{Reco} - E_{True}) / E_{True}");
  hCarbon_1Pi0->GetYaxis()->SetTitle("A.U.");
  hCarbon_1Pi0->GetXaxis()->SetRangeUser(-1,1);
  hCarbon_1Pi0->GetYaxis()->SetRangeUser(0,0.2);
  hCarbon_1Pi0->SetTitle("CC1#pi0");
  hCarbon2_1Pi0->Draw("hist same");
  hCarbon3_1Pi0->Draw("hist same");
  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon_1Pi0 ,"no STV cut","l");
  leg->AddEntry(hCarbon2_1Pi0 ,"100 MeV STV cut","l");
  leg->AddEntry(hCarbon3_1Pi0 ,"50 MeV STV cut","l");
  leg->Draw();
  c1_bd->cd(4);
  hCarbon_mPi ->SetLineColor(1);
  hCarbon2_mPi->SetLineColor(2);
  hCarbon3_mPi->SetLineColor(3);
  hCarbon4_mPi->SetLineColor(4);
  hCarbon_mPi->Draw("hist");
  hCarbon_mPi->GetXaxis()->SetTitle("(E_{Reco} - E_{True}) / E_{True}");
  hCarbon_mPi->GetYaxis()->SetTitle("A.U.");
  hCarbon_mPi->GetXaxis()->SetRangeUser(-1,1);
  hCarbon_mPi->GetYaxis()->SetRangeUser(0,0.2);
  hCarbon_mPi->SetTitle("CCm#pi");
  hCarbon2_mPi->Draw("hist same");
  hCarbon3_mPi->Draw("hist same");
  leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon_mPi ,"no STV cut","l");
  leg->AddEntry(hCarbon2_mPi ,"100 MeV STV cut","l");
  leg->AddEntry(hCarbon3_mPi ,"50 MeV STV cut","l");
  leg->Draw();


  //TCanvas* c1 = new TCanvas();
  //hs1->GetXaxis()->SetTitle("#delta P_{T} (GeV)");
  //hs1->GetYaxis()->SetTitle("Events");
  //hs1->GetXaxis()->SetTitle("#delta P_{T} (GeV)");
  //hs1->GetYaxis()->SetTitle("Events");
  //hs1->Draw();

  //cout<<"interacitons in hydrogen and carbon: "<<hInteraction<<" "<<cInteraction<<endl;

  TCanvas* c2 = new TCanvas();
  c2->Divide(2,2);
  for(int i=0;i<4;i++){
    c2->cd(i+1);
    h2D[i]->Draw("colz");
    h2D[i]->GetXaxis()->SetTitle("Reconstructed energy ");
    h2D[i]->GetYaxis()->SetTitle("True energy");
  }
  h2D[0]->SetTitle("no STV (one year event rate)");
  h2D[1]->SetTitle("STV 100 MeV (one year event rate)");
  h2D[2]->SetTitle("STV 50 MeV (one year event rate)");
  h2D[3]->SetTitle("STV 20 MeV (one year event rate)");

  TCanvas* c2_0Pi = new TCanvas();
  c2_0Pi->Divide(2,2);
  for(int i=0;i<4;i++){
    c2_0Pi->cd(i+1);
    h2D_noPi[i]->Draw("colz");
    h2D_noPi[i]->GetXaxis()->SetTitle("Reconstructed energy ");
    h2D_noPi[i]->GetYaxis()->SetTitle("True energy");
  }
  h2D_noPi[0]->SetTitle("no STV CC0Pi");
  h2D_noPi[1]->SetTitle("STV 100 MeV CC0Pi");
  h2D_noPi[2]->SetTitle("STV 50 MeV CC0Pi");
  h2D_noPi[3]->SetTitle("STV 20 MeV CC0Pi");


  TCanvas* c2_1Pi0 = new TCanvas();
  c2_1Pi0->Divide(2,2);
  for(int i=0;i<4;i++){
    c2_1Pi0->cd(i+1);
    h2D_1Pi0[i]->Draw("colz");
    h2D_1Pi0[i]->GetXaxis()->SetTitle("Reconstructed energy ");
    h2D_1Pi0[i]->GetYaxis()->SetTitle("True energy");
  }
  h2D_1Pi0[0]->SetTitle("no STV CC1#pi0");
  h2D_1Pi0[1]->SetTitle("STV 100 MeV CC1#pi0");
  h2D_1Pi0[2]->SetTitle("STV 50 MeV CC1#pi0");
  h2D_1Pi0[3]->SetTitle("STV 20 MeV CC1#pi0");


  TCanvas* c2_1Pip = new TCanvas();
  c2_1Pip->Divide(2,2);
  for(int i=0;i<4;i++){
    c2_1Pip->cd(i+1);
    h2D_1Pip[i]->Draw("colz");
    h2D_1Pip[i]->GetXaxis()->SetTitle("Reconstructed energy ");
    h2D_1Pip[i]->GetYaxis()->SetTitle("True energy");
  }
  h2D_1Pip[0]->SetTitle("no STV CC1#pi-");
  h2D_1Pip[1]->SetTitle("STV 100 MeV CC1#pi-");
  h2D_1Pip[2]->SetTitle("STV 50 MeV CC1#pi-");
  h2D_1Pip[3]->SetTitle("STV 20 MeV CC1#pi-");


  TCanvas* c2_mPi = new TCanvas();
  c2_mPi->Divide(2,2);
  for(int i=0;i<4;i++){
    c2_mPi->cd(i+1);
    h2D_mPi[i]->Draw("colz");
    h2D_mPi[i]->GetXaxis()->SetTitle("Reconstructed energy ");
    h2D_mPi[i]->GetYaxis()->SetTitle("True energy");
  }
  h2D_mPi[0]->SetTitle("no STV CCm#pi");
  h2D_mPi[1]->SetTitle("STV 100 MeV CCm#pi");
  h2D_mPi[2]->SetTitle("STV 50 MeV CCm#pi");
  h2D_mPi[3]->SetTitle("STV 20 MeV CCm#pi");

//**************************************************************************************
//**************************************************************************************

  TCanvas* c3 = new TCanvas();
  part1->Draw("colz");
  part1->GetXaxis()->SetTitle("particle type");
  part1->GetYaxis()->SetTitle("status");
  for(int i=0;i<part1->GetNbinsX();i++)
    part1->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  for(int i=0;i<part1->GetNbinsY();i++)
    part1->GetYaxis()->SetBinLabel(i+1,stg[i]);

  TCanvas* c4 = new TCanvas();
  part2->SetTitle("Final State per event");
  part2->GetXaxis()->SetTitle("particle type");
  part2->GetYaxis()->SetTitle("Entries");
  for(int i=0;i<part2->GetNbinsX();i++){
    part2->SetBinContent(i+1,part2->GetBinContent(i+1)/counter1);
    part2->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  }
  part2->Draw("colz");

  TCanvas* c5 = new TCanvas();
  c5->Divide(2,2);
  for(int i=0;i<4;i++){
    c5->cd(i+1);
    part3[i]->Draw("colz");
    part3[i]->GetXaxis()->SetTitle("Reconstructed energy ");
    part3[i]->GetYaxis()->SetTitle("True energy");
  }
  part3[0]->SetTitle("neutron N vs residual");
  part3[1]->SetTitle("pip N vs residual");
  part3[2]->SetTitle("pi0 N vs residual");
  part3[3]->SetTitle("proton N vs residual");

  TCanvas* c6 = new TCanvas();
  c6->Divide(3,2);
  c6->cd(1);
  tail->SetTitle("tail - all no STV ");
  tail->GetXaxis()->SetTitle("particle type");
  tail->GetYaxis()->SetTitle("status");
  tail->Draw("colz");
  for(int i=0;i<tail->GetNbinsX();i++)
    tail->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  for(int i=0;i<tail->GetNbinsY();i++)
    tail->GetYaxis()->SetBinLabel(i+1,stg[i]);
  c6->cd(2);
  tail_noPi->SetTitle("tail - CC0#pi no STV");
  tail_noPi->GetXaxis()->SetTitle("particle type");
  tail_noPi->GetYaxis()->SetTitle("status");
  tail_noPi->Draw("colz");
  for(int i=0;i<tail->GetNbinsX();i++)
    tail_noPi->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  for(int i=0;i<tail->GetNbinsY();i++)
    tail_noPi->GetYaxis()->SetBinLabel(i+1,stg[i]);
  c6->cd(3);
  tail_1Pi0->SetTitle("inclusive - CC1#pi0 no STV");
  tail_1Pi0->GetXaxis()->SetTitle("particle type");
  tail_1Pi0->GetYaxis()->SetTitle("status");
  tail_1Pi0->Draw("colz");
  for(int i=0;i<tail->GetNbinsX();i++)
    tail_1Pi0->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  for(int i=0;i<tail->GetNbinsY();i++)
    tail_1Pi0->GetYaxis()->SetBinLabel(i+1,stg[i]);
  c6->cd(4);
  tail_1Pip->SetTitle("inclusive - CC1#pi- no STV");
  tail_1Pip->GetXaxis()->SetTitle("particle type");
  tail_1Pip->GetYaxis()->SetTitle("status");
  tail_1Pip->Draw("colz");
  for(int i=0;i<tail->GetNbinsX();i++)
    tail_1Pip->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  for(int i=0;i<tail->GetNbinsY();i++)
    tail_1Pip->GetYaxis()->SetBinLabel(i+1,stg[i]);
  c6->cd(5);
  tail_mPi->SetTitle("inclusive - all ");
  tail_mPi->GetXaxis()->SetTitle("particle type");
  tail_mPi->GetYaxis()->SetTitle("status");
  tail_mPi->Draw("colz");
  for(int i=0;i<tail->GetNbinsX();i++)
    tail_mPi->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
  for(int i=0;i<tail->GetNbinsY();i++)
    tail_mPi->GetYaxis()->SetBinLabel(i+1,stg[i]);


  TCanvas* c7 = new TCanvas();
  c7->Divide(3,2);
  c7->cd(1);
  tail1d->SetTitle("tail - all no STV ");
  tail1d->GetXaxis()->SetTitle("particle type");
  tail1d->GetYaxis()->SetTitle("Entries");
  tail1d->Draw("");
  for(int i=0;i<tail1d->GetNbinsX();i++){
    tail1d->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
    tail1d->SetBinContent(i+1,tail1d->GetBinContent(i+1)/counterTail);
  }
  c7->cd(2);
  tail1d_noPi->SetTitle("tail - CC0#pi no STV");
  tail1d_noPi->GetXaxis()->SetTitle("particle type");
  tail1d_noPi->GetYaxis()->SetTitle("Entries");
  tail1d_noPi->Draw("");
  for(int i=0;i<tail1d->GetNbinsX();i++){
    tail1d_noPi->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
    tail1d_noPi->SetBinContent(i+1,tail1d_noPi->GetBinContent(i+1)/counterTail_0Pi);
  }
  c7->cd(3);
  tail1d_1Pi0->SetTitle("inclusive - CC1#pi0 no STV");
  tail1d_1Pi0->GetXaxis()->SetTitle("particle type");
  tail1d_1Pi0->GetYaxis()->SetTitle("Entries");
  tail1d_1Pi0->Draw("");
  for(int i=0;i<tail1d->GetNbinsX();i++){
    tail1d_1Pi0->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
    tail1d_1Pi0->SetBinContent(i+1,tail1d_1Pi0->GetBinContent(i+1)/counterTail_1Pi0);
  }
  c7->cd(4);
  tail1d_1Pip->SetTitle("inclusive - CC1#pi- no STV");
  tail1d_1Pip->GetXaxis()->SetTitle("particle type");
  tail1d_1Pip->GetYaxis()->SetTitle("Entries");
  tail1d_1Pip->Draw("");
  for(int i=0;i<tail1d->GetNbinsX();i++){
    tail1d_1Pip->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
    tail1d_1Pip->SetBinContent(i+1,tail1d_1Pip->GetBinContent(i+1)/counterTail_1Pip);
  }
  c7->cd(5);
  tail1d_mPi->SetTitle("inclusive - all ");
  tail1d_mPi->GetXaxis()->SetTitle("particle type");
  tail1d_mPi->GetYaxis()->SetTitle("Entries");
  tail1d_mPi->Draw("");
  for(int i=0;i<tail1d->GetNbinsX();i++){
    tail1d_mPi->GetXaxis()->SetBinLabel(i+1,pdgs[i]);
    tail1d_mPi->SetBinContent(i+1,tail1d_mPi->GetBinContent(i+1)/counterTail_mPi);
  }

  new TCanvas();
  //THStack *hs = new THStack("hs","");
  //hs->Add(hC_noPi);
  //hs->Add(hH_noPi);
  //hC_noPi->SetFillColor(kRed);
  //hH_noPi->SetFillColor(kBlue);
  hC_noPi->SetLineColor(kRed);
  hH_noPi->SetLineColor(kBlue);
  hC_noPi->Draw("hist");
  hH_noPi->Draw("same");
}
