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

TFile f1("FHC_numu_CCRES_Carbon_1x10e5.root");
TFile f2("FHC_numu_CCRES_Hydrogen_1x10e5.root");
TFile f3("FHC_numu_CCRES_scintillator.root");
TTree* h1 = (TTree*) f1.Get("gRooTracker");
TTree* h2 = (TTree*) f2.Get("gRooTracker");
TTree* h3 = (TTree*) f3.Get("gRooTracker");

Int_t StdHepPdg[1000];
Int_t StdHepStatus[1000];
Double_t vtx[4]={};
Double_t ivtx[1000][4]={};
Double_t imom[1000][4]={};
Bool_t flag=false;
Bool_t wflag=false;
Int_t rightSign=0,wrongSign=0;

 h1->SetBranchAddress("StdHepPdg", &StdHepPdg);
 h1->SetBranchAddress("StdHepStatus", &StdHepStatus);
 h1->SetBranchAddress("EvtVtx", &vtx);
 h1->SetBranchAddress("StdHepX4", &ivtx);
 h1->SetBranchAddress("StdHepP4", &imom); 

 h2->SetBranchAddress("StdHepPdg", &StdHepPdg);
 h2->SetBranchAddress("StdHepStatus", &StdHepStatus);
 h2->SetBranchAddress("EvtVtx", &vtx);
 h2->SetBranchAddress("StdHepX4", &ivtx);
 h2->SetBranchAddress("StdHepP4", &imom);

 h3->SetBranchAddress("StdHepPdg", &StdHepPdg);
 h3->SetBranchAddress("StdHepStatus", &StdHepStatus);
 h3->SetBranchAddress("EvtVtx", &vtx);
 h3->SetBranchAddress("StdHepX4", &ivtx);
 h3->SetBranchAddress("StdHepP4", &imom);

TH1D* hCarbon = new TH1D("Carbon","Area normalized",40,-1,1);
TH1D* hHydrogen = new TH1D("Hydrogen","Hydrogen",40,-1,1);
TH1D* hCarbon2 = new TH1D("Carbon2","Area normalized",40,-1,1);
TH1D* hHydrogen2 = new TH1D("Hydrogen2","Hydrogen2",40,-1,1);
TH1D* hScintillator = new TH1D("Scintillator","Scintillator",40,-1,1);

TVector3* vecMuon2;
TVector3 vecMuonT;
TVector3* vecOther2;
TVector3* vecNu;

TRandom *ran1 = new TRandom();
TRandom *ran2 = new TRandom();

double signn = 0;
bool willDo1 = false;
bool willDo2 = false;
double totalTrans=0;
double vecMuon[3]={};
double vecOther[3]={};
double angleSmear =0;
double momSmear = 0;

Int_t nentries =  (Int_t) h1->GetEntries();
Int_t nentries2 = (Int_t) h2->GetEntries();
Int_t nentries3 = (Int_t) h3->GetEntries();

//cout<<nentries <<endl;
 for(Int_t i=0; i<nentries ; i++) {

    h1->GetEntry(i);

ran1->SetSeed(i* 100);
ran2->SetSeed(i* 111+5);

//STT: 2mrad angular and 5% energy; 3DST: 20 mrad and 20% energy
angleSmear = ran1->Gaus(0,0.02);
momSmear   = ran1->Gaus(1,0.2);

//cout<<i<<"............"<<endl;
for(Int_t j=2;j<12;j++){
  //  cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(StdHepPdg[j]== 13 && StdHepStatus[j]==1){
vecMuon[0] = imom[j][0];
vecMuon[1] = imom[j][1];
vecMuon[2] = imom[j][2];
vecNu = new TVector3(imom[0][0],imom[0][1],imom[0][2]);
vecMuon2= new TVector3(imom[j][0],imom[j][1],imom[j][2]);
vecMuonT = vecMuon2->Cross(*vecNu);
}
if(StdHepPdg[j]==211 && StdHepStatus[j]==1){willDo1 = true;}
if(StdHepPdg[j]==2212 && StdHepStatus[j]==1){willDo2 = true;}

}

for(Int_t j=2;j<30;j++){
 //   cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(TMath::Abs(StdHepPdg[j])!= 13 && StdHepStatus[j]==1){
vecOther[0] = imom[j][0];
vecOther[1] = imom[j][1];
vecOther[2] = imom[j][2];

vecOther2= new TVector3(imom[j][0],imom[j][1],0);

double tempAng = TMath::Cos(vecOther2->Angle(vecMuonT)+angleSmear);
double tempAdd = tempAng * (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]))*momSmear;
totalTrans += tempAdd;


/*
double tempAng = TMath::Sin(TMath::ACos((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1]))));
double tempAdd = tempAng * (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]));
//totalTrans += tempAdd;
if (TMath::ACos((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1])))>1.57) totalTrans += tempAdd;
else totalTrans += -tempAdd;
}
}
//cout<<totalTrans<<endl;
hCarbon->Fill(totalTrans);
totalTrans=0;
*/
}
}
//cout<<totalTrans<<endl;
if(willDo1 && willDo2) hCarbon->Fill(totalTrans);
totalTrans=0;
willDo1 = false;
willDo2 = false;
for(int i=0;i<3;i++){
vecOther[i]=0;
vecMuon[i]=0;
}
vecMuon2 = new TVector3(0,0,0);
vecOther2 = new TVector3(0,0,0);
vecMuonT.Delete(); //= new TVector3(0,0,0);
vecNu = new TVector3(0,0,0);
}

cout<<"starting hydrogen.."<<endl;
cout<<endl;
 for(Int_t i=0; i<nentries2 ; i++) {

    h2->GetEntry(i);

cout<<i<<"............"<<endl;
for(Int_t j=2;j<6;j++){
    cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(StdHepPdg[j]== 13 && StdHepStatus[j]==1){
vecMuon[0] = imom[j][0];
vecMuon[1] = imom[j][1];
vecMuon[2] = imom[j][2];
vecNu = new TVector3(imom[0][0],imom[0][1],imom[0][2]);
vecMuon2= new TVector3(imom[j][0],imom[j][1],imom[j][2]);
vecMuonT = vecMuon2->Cross(*vecNu);
}

if(StdHepPdg[j]==211 && StdHepStatus[j]==1){willDo1 = true;}
if(StdHepPdg[j]==2212 && StdHepStatus[j]==1){willDo2 = true;}
}

for(Int_t j=2;j<6;j++){
 //   cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(TMath::Abs(StdHepPdg[j])!= 13 && StdHepStatus[j]==1){
vecOther[0] = imom[j][0];
vecOther[1] = imom[j][1];
vecOther[2] = imom[j][2];
vecOther2= new TVector3(imom[j][0],imom[j][1],0);

//if((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1]))>0){signn = 1;}
//else {signn = 0;}

double tempAng = TMath::Cos(vecOther2->Angle(vecMuonT)+angleSmear); //TMath::Sin(TMath::ACos((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1]))));
//cout<<TMath::ACos((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1])))<<endl;
//cout<<tempAng<<endl;
double tempAdd = tempAng * (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]))* momSmear;
//cout<<tempAng<<" "<<tempAdd<<endl;
//cout<<endl;
/*if(signn ==1)*/ 
totalTrans += tempAdd;
//if (TMath::ACos((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1])))>1.57) totalTrans += tempAdd;
//else totalTrans += -tempAdd;
cout<<TMath::ACos((vecOther[0]*vecMuon[0] + vecOther[1]*vecMuon[1]) / (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]) * TMath::Sqrt(vecMuon[0]*vecMuon[0] + vecMuon[1]*vecMuon[1])))<<" "<<tempAng<<" "<<tempAdd<<" "<<totalTrans<<endl;
//cout<<endl;
}
}
cout<<totalTrans<<endl;
if(willDo1 && willDo2) hHydrogen->Fill(totalTrans);
totalTrans=0;
willDo1 = false;
willDo2 = false;
for(int i=0;i<3;i++){
vecOther[i]=0;
vecMuon[i]=0;
}
vecMuon2 = new TVector3(0,0,0);
vecOther2 = new TVector3(0,0,0);
vecMuonT.Delete(); //= new TVector3(0,0,0);
vecNu = new TVector3(0,0,0);
}

cout<<"starting scintillator.."<<endl;
cout<<endl;
int hInteraction=0;
int cInteraction=0;

 for(Int_t i=0; i<nentries3 ; i++) {

    h3->GetEntry(i);

for(Int_t j=2;j<10;j++){
    //cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(StdHepPdg[j]== 13 && StdHepStatus[j]==1){
vecMuon[0] = imom[j][0];
vecMuon[1] = imom[j][1];
vecMuon[2] = imom[j][2];
vecNu = new TVector3(imom[0][0],imom[0][1],imom[0][2]);
vecMuon2= new TVector3(imom[j][0],imom[j][1],imom[j][2]);
vecMuonT = vecMuon2->Cross(*vecNu);
}
if(StdHepPdg[j]==211 && StdHepStatus[j]==1){willDo1 = true;}
if(StdHepPdg[j]==2212 && StdHepStatus[j]==1){willDo2 = true;}

}
if(StdHepPdg[1]>10000){
cInteraction++;
for(Int_t j=0;j<30;j++){
    cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(TMath::Abs(StdHepPdg[j])!= 13 && StdHepStatus[j]==1){
vecOther[0] = imom[j][0];
vecOther[1] = imom[j][1];
vecOther[2] = imom[j][2];

vecOther2= new TVector3(imom[j][0],imom[j][1],0);

double tempAng = TMath::Cos(vecOther2->Angle(vecMuonT));
double tempAdd = tempAng * (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]));
totalTrans += tempAdd;

}
}
if(willDo1 && willDo2) hCarbon2->Fill(totalTrans);
}
else{
hInteraction++;
for(Int_t j=2;j<6;j++){
 //   cout<<i<<" "<<StdHepStatus[j]<<" "<<StdHepPdg[j]<<" "<<imom[j][0]<<" "<<imom[j][1]<<" "<<imom[j][2]<<" "<<imom[j][3]<<endl;

if(TMath::Abs(StdHepPdg[j])!= 13 && StdHepStatus[j]==1){
vecOther[0] = imom[j][0];
vecOther[1] = imom[j][1];
vecOther[2] = imom[j][2];

vecOther2= new TVector3(imom[j][0],imom[j][1],0);

double tempAng = TMath::Cos(vecOther2->Angle(vecMuonT)+angleSmear);
double tempAdd = tempAng * (TMath::Sqrt(vecOther[0]*vecOther[0] + vecOther[1]*vecOther[1]))*momSmear;
totalTrans += tempAdd;

}
}
if(willDo1 && willDo2) hHydrogen2->Fill(totalTrans);
}
cout<<totalTrans<<endl;
if(willDo1 && willDo2) hScintillator->Fill(totalTrans);
totalTrans=0;
willDo1 = false;
willDo2 = false;
for(int i=0;i<3;i++){
vecOther[i]=0;
vecMuon[i]=0;
}
vecMuon2 = new TVector3(0,0,0);
vecOther2 = new TVector3(0,0,0);
vecMuonT.Delete(); //= new TVector3(0,0,0);
vecNu = new TVector3(0,0,0);

}

THStack* hs1= new THStack("hs","#delta P_{T} (GeV)");
hCarbon2->SetFillColor(kBlack);
hHydrogen2->SetFillColor(kRed);
hs1->Add(hCarbon2);
hs1->Add(hHydrogen2);


TCanvas* c0 =new TCanvas();
hCarbon->Scale(hScintillator->Integral()/hCarbon->Integral());
hHydrogen->Scale(hScintillator->Integral()/hHydrogen->Integral());
hCarbon->SetLineColor(1);
hHydrogen->SetLineColor(2);
hScintillator->SetLineColor(4);
hCarbon->Draw("hist");
hCarbon->GetXaxis()->SetTitle("#delta P_{T} (GeV)");
hCarbon->GetYaxis()->SetTitle("Events");
hHydrogen->Draw("same");
hScintillator->Draw("same");

  TLegend* leg = new TLegend(0.6,0.68,0.9,0.9,NULL,"brNDC");
  leg->AddEntry(hCarbon ,"hCarbon","l");
  leg->AddEntry(hHydrogen ,"hHydrogen","l");
  leg->AddEntry(hScintillator ,"hScintillator","l");
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

TCanvas* c1 = new TCanvas();
//hs1->GetXaxis()->SetTitle("#delta P_{T} (GeV)");
//hs1->GetYaxis()->SetTitle("Events");
//hs1->GetXaxis()->SetTitle("#delta P_{T} (GeV)");
//hs1->GetYaxis()->SetTitle("Events");
hs1->Draw();

cout<<"interacitons in hydrogen and carbon: "<<hInteraction<<" "<<cInteraction<<endl;

}
