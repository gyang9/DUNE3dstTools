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


TChain t("tree");
t.Add("FHC_*.root");

double piMass = 139.57;
double muMass = 105.7;
//cm/ns
double lightSpeed = 30;

float vtx[3];
float lepMom[4];
float piDeath[4];
float lepDeath[4];
float muonExitPt[4];
float mu3DSTLen;
float mu3DSTEnergy;
float pionExitPt[4];
float pionExitMom[3];
float muGArLen;
float pionMom[4];
float pi3DSTLen;
float pi3DSTEnergy;
float piGArLen;
int fsPdg[100];
int nFS;
float fsPx[100];
float fsPy[100];
float fsPz[100];
float fsE[100];
float mu3DSTElayer[1000];
float pi3DSTElayer[1000];
float muECALFarYZ,muECALFar;
float piECALFarYZ,piECALFar;
float muECALEnergy, piECALEnergy;
float muECALexit[1000]={};
float muECALenter[1000]={};
float piECALenter[1000]={};
float muECALLen;
float piECALexit[1000]={};
float piECALLen;
float NuEnergy;

t.SetBranchAddress("vtx",&vtx);
t.SetBranchAddress("lepMom",&lepMom);
t.SetBranchAddress("piDeath",&piDeath);
t.SetBranchAddress("lepDeath",&lepDeath);
t.SetBranchAddress("muonExitPt",&muonExitPt);
t.SetBranchAddress("mu3DSTLen",&mu3DSTLen);
t.SetBranchAddress("mu3DSTEnergy",&mu3DSTEnergy);
t.SetBranchAddress("pionExitPt",&pionExitPt);
t.SetBranchAddress("pionExitMom",&pionExitMom);
t.SetBranchAddress("muGArLen",&muGArLen);
t.SetBranchAddress("pionMom",&pionMom);
t.SetBranchAddress("pi3DSTLen",&pi3DSTLen);
t.SetBranchAddress("pi3DSTEnergy",&pi3DSTEnergy);
t.SetBranchAddress("piGArLen",&piGArLen);
t.SetBranchAddress("fsPdg",&fsPdg);
t.SetBranchAddress("nFS",&nFS);
t.SetBranchAddress("fsPx",&fsPx);
t.SetBranchAddress("fsPy",&fsPy);
t.SetBranchAddress("fsPz",&fsPz);
t.SetBranchAddress("fsE",&fsE);
t.SetBranchAddress("mu3DSTElayer",&mu3DSTElayer);
t.SetBranchAddress("pi3DSTElayer",&pi3DSTElayer);
t.SetBranchAddress("muECALFarYZ",&muECALFarYZ);
t.SetBranchAddress("muECALFar",&muECALFar);
t.SetBranchAddress("piECALFarYZ",&piECALFarYZ);
t.SetBranchAddress("piECALFar",&piECALFar);
t.SetBranchAddress("muECALEnergy",&muECALEnergy);
t.SetBranchAddress("piECALEnergy",&piECALEnergy);
t.SetBranchAddress("muECALexit",&muECALexit);
t.SetBranchAddress("muECALenter",&muECALenter);
t.SetBranchAddress("piECALenter",&piECALenter);
t.SetBranchAddress("muECALLen",&muECALLen);
t.SetBranchAddress("piECALexit",&piECALexit);
t.SetBranchAddress("piECALLen",&piECALLen);
t.SetBranchAddress("nuEnergy",&NuEnergy);

TGraph* g1 = new TGraph();
TGraph* g2 = new TGraph();
double cc_tot=0;
double cc_qe=0;
double cc_res=0;
double cc_dis=0;
double nc_tot=0;
double nc_1pip=0;
double nc_npip=0;
double nc_1pip0pi0=0;
double nc_1pipnpi0=0;


TH2F* h1_mu = new TH2F("","CC edepVSlength;length;edep",40,0,200,40,0,400);
TH2F* h2_mu = new TH2F("","CC timeVSlength;time;edep",40,0,10,40,0,400);
TH2F* h1_pi = new TH2F("","NC edepVSlength;length;edep",40,0,200,40,0,400);
TH2F* h2_pi = new TH2F("","NC timeVSlength;time;edep",40,0,10,40,0,400);

TH1F* massRes_mu = new TH1F("","mass resolution muon; dm/m; counts",40,50,200);
TH1F* massRes_pi = new TH1F("","mass resolution pion; dm/m; counts",40,50,200);

TH2F* dedxECAL_mu = new TH2F("","muon dEdX in ECAL; length; Energy; counts",40,0,300,40,0,10);
TH2F* dedxECAL_pi = new TH2F("","pion dEdX in ECAL; length; Energy; counts",40,0,300,40,0,10);

TH1F* deECAL_mu = new TH1F("","muon energy in ECAL; Energy; counts",100,0,10);
TH1F* deECAL_pi = new TH1F("","pion energy in ECAL; Energy; counts",100,0,10);
TH1F* dxECAL_mu = new TH1F("","muon length in ECAL; Length; counts",100,100,300);
TH1F* dxECAL_pi = new TH1F("","pion length in ECAL; Length; counts",100,100,300);

TH1F* h_compare_pi = new TH1F("","pi dedx compare; energy ratio; counts",100,0,4);
TH1F* h_compare_mu = new TH1F("","mu dedx compare; energy ratio; counts",100,0,4);

TH2F* ecal_mu1 = new TH2F("","muon death; death distance; Energy; counts",40,0,400,40,0,20);
TH2F* ecal_pi1 = new TH2F("","pion death; death distance; Energy; counts",40,0,400,40,0,20);
TH2F* ecal_mu2 = new TH2F("","muon far; farYZ; Energy; counts",40,0,400,40,0,20);
TH2F* ecal_pi2 = new TH2F("","pion far; farYZ; Energy; counts",40,0,400,40,0,20);

TH1F* nu_spec_CC = new TH1F("","neutrino spectrum with CC ; Neutrino Energy (GeV); Counts", 100,0,10);
TH1F* nu_spec_NC = new TH1F("","neutrino spectrum with NC charge pi ; Neutrino Energy (GeV); Counts", 100,0,10);
TH1F* pi_spec_NC = new TH1F("","pion spectrum with NC charge pi ; charged pi energy (MeV); Counts", 100,0,4000);
TH1F* mu_spec_CC = new TH1F("","muon spectrum with CC ; charged #mu energy (MeV); Counts", 100,0,4000);

TH2F* nc_death = new TH2F("","NC charge pi end point; Z (beam direction); Y (vertical)", 100, -400,600,100,-400,400);
TH2F* cc_death = new TH2F("","CC muon end point; Z (beam direction); Y (vertical)", 100, -400,600,100,-400,400);

TH2F* nc_ecal_deposit = new TH2F("","NC ecal length vs. deposit; ecal travel length; energy deposit in ecal (MeV)", 200,0,100,100,0,600);
TH2F* cc_ecal_deposit = new TH2F("","CC ecal length vs. deposit; ecal travel length; energy deposit in ecal (MeV)", 200,0,100,100,0,600);

cout<<t.GetEntries()<<endl;
int Nentry = t.GetEntries();

int counter1 =0;
int counter2 =0;

double nc_npip_contained=0;
double nc_npip_escape=0;
double nc_npip_ecal=0;
double cc_nlep_contained=0;
double cc_nlep_escape=0;
double cc_nlep_ecal=0;

for(int i=0;i<Nentry;i++){

t.GetEntry(i);
if(i%100 == 0) cout<<i<<endl;

bool isCC=false;
bool isNC=false;
int nPip=0;
int nPi0=0;
int nP=0;
int nN=0;

if(abs(fsPdg[0]) == 13 ) isCC = true;
if(abs(fsPdg[0]) == 12 || abs(fsPdg[0]) == 14) isNC = true;

for(int j=0;j<nFS;j++){
  if(fsPdg[j]==2112) nN++;
  if(fsPdg[j]==2212) nP++;
  if(fsPdg[j]==211) nPip++;
  if(fsPdg[j]==111) nPi0++; 
}

if(isNC ) nc_tot++;

if(nPip == 0) isNC = false;

// 3DST size for Geo13: x: 126 y: 118 z: -150 to 50

if(isNC && pi3DSTLen>0 ){
nc_npip++;

if(abs(piDeath[0])<124 && abs(piDeath[1])<116 && piDeath[2]>-148 && piDeath[2]<48){
  nc_npip_contained ++;
}
//else if(abs(pow(piDeath[1],2)+pow(piDeath[2],2))>223 || abs(piDeath[0])>180.5+23/2. ){
else if(sqrt(pow(piDeath[1],2)+pow(piDeath[2],2))>250 || abs(piDeath[0])>220 ){
  nc_npip_escape ++;
}
else{
  nc_npip_ecal ++;
}
nc_death->Fill(piDeath[2],piDeath[1]);

nu_spec_NC->Fill(NuEnergy);
pi_spec_NC->Fill(sqrt(pow(pionMom[0],2)+pow(pionMom[1],2)+pow(pionMom[2],2)+ piMass*piMass)- piMass);	

g1->SetPoint(counter1, sqrt(pow(pionMom[0],2)+pow(pionMom[1],2)+pow(pionMom[2],2)), (pionExitPt[3]-pionMom[3])/pi3DSTLen);
cout<<"NC "<<sqrt(pow(pionMom[0],2)+pow(pionMom[1],2)+pow(pionMom[2],2))<<" "<<pionExitPt[3]<<" "<<pionMom[3]<<" "<<(pionExitPt[3]-pionMom[3])<<" "<<pi3DSTEnergy/pi3DSTLen<<endl;
counter1++;

nc_ecal_deposit->Fill(sqrt(pow(piECALexit[0]-piECALenter[0],2)+pow(piECALexit[1]-piECALenter[1],2)+pow(piECALexit[2]-piECALenter[2],2)), piECALEnergy);

double ke = sqrt(pow(pionMom[0],2)+pow(pionMom[1],2)+pow(pionMom[2],2) + piMass*piMass ) - piMass;
double gamma = ke/piMass+1;
cout<<"pion gamma "<<gamma<<endl;
double duration = pi3DSTLen/ sqrt((1- (1/gamma)*(1/gamma)) * lightSpeed*lightSpeed);
cout<<"pion duration "<<duration<<endl;

h1_pi->Fill(pi3DSTLen, pi3DSTEnergy);
h2_pi->Fill(duration, pi3DSTEnergy );
//massRes_pi->Fill(  gRandom->Gaus(piMass, piMass*(gamma*( (1.4/sqrt(12))/pi3DSTLen + 1.4*0.5/pionExitPt[3] ) ) ));
massRes_pi->Fill(  gRandom->Gaus(piMass, piMass*(0.14 + gamma*gamma*( (1.4*0.01/duration) ) ) ));

if( abs(piDeath[2]+50)<98 && abs(piDeath[1])<118 && abs(piDeath[0])<118){
  double dedxCompare = -1;
  for(int jj=0;jj<1000;jj++){
    if(pi3DSTElayer[jj]<0.00001) break;
    dedxCompare = pi3DSTElayer[jj]/pi3DSTElayer[0];
    cout<<jj<<" --------------------  "<<pi3DSTElayer[jj]<<endl;
  }
  h_compare_pi->Fill(dedxCompare);
}

if(piECALEnergy>0){
  dedxECAL_pi -> Fill(piECALFar,piECALEnergy);
  ecal_pi1->Fill(sqrt(piDeath[0]*piDeath[0]+piDeath[1]*piDeath[1]+piDeath[2]*piDeath[2]), piECALEnergy );
  ecal_pi2->Fill(piECALFarYZ, piECALEnergy);  
  deECAL_pi->Fill(piECALEnergy);
  dxECAL_pi->Fill(piECALFarYZ);
}	
}

///////////////////////////////////////////////////////////////// CC starts

if(isCC && mu3DSTLen>0 ){
cc_tot++;

if(abs(lepDeath[0])<124 && abs(lepDeath[1])<116 && lepDeath[2]>-148 && lepDeath[2]<48){
  cc_nlep_contained ++;
}
//else if(abs(pow(lepDeath[1],2)+pow(lepDeath[2],2))>223 || abs(lepDeath[0])>180.5+23/2. ){
else if(sqrt(pow(lepDeath[1],2)+pow(lepDeath[2],2))>250 || abs(lepDeath[0])>220 ){
  cc_nlep_escape ++;
}
else{
  cc_nlep_ecal ++;
}

cc_death->Fill(lepDeath[2],lepDeath[1]);
nu_spec_CC->Fill(NuEnergy);
mu_spec_CC->Fill(sqrt(pow(lepMom[0],2)+pow(lepMom[1],2)+pow(lepMom[2],2) + muMass*muMass)-muMass);

g2->SetPoint(counter2, sqrt(pow(lepMom[0],2)+pow(lepMom[1],2)+pow(lepMom[2],2)),(muonExitPt[3]-lepMom[3])/mu3DSTLen);
cout<<"CC "<<sqrt(pow(lepMom[0],2)+pow(lepMom[1],2)+pow(lepMom[2],2))<<" "<<(muonExitPt[3]-lepMom[3])<<" "<<mu3DSTEnergy/mu3DSTLen<<endl;
counter2++;
double ke = sqrt(pow(lepMom[0],2)+pow(lepMom[1],2)+pow(lepMom[2],2) + muMass*muMass ) - muMass;
double gamma = ke/muMass+1;
cout<<"muon gamma "<<gamma<<endl;
double duration = mu3DSTLen/ sqrt((1- (1/gamma)*(1/gamma)) * lightSpeed*lightSpeed);
cout<<"muon duration "<<duration<<endl;

cc_ecal_deposit->Fill(sqrt(pow(muECALexit[0]-muECALenter[0],2)+pow(muECALexit[1]-muECALenter[1],2)+pow(muECALexit[2]-muECALenter[2],2)), muECALEnergy);

h1_mu->Fill(mu3DSTLen, mu3DSTEnergy);
h2_mu->Fill(duration,mu3DSTEnergy );
//massRes_mu->Fill(  gRandom->Gaus(muMass, muMass*(gamma*( (1.4/sqrt(12))/mu3DSTLen + 1.4*0.5/muonExitPt[3] ) ) ));
massRes_mu->Fill(  gRandom->Gaus(muMass, muMass*(0.14 + gamma*gamma*( (1.4*0.01/duration)) ) ));

if( abs(lepDeath[2]+50)<98 && abs(lepDeath[1])<118 && abs(lepDeath[0])<118){
  double dedxCompare = -1;
  for(int jj=0;jj<1000;jj++){
    if(mu3DSTElayer[jj]<0.00001) break;
    dedxCompare = mu3DSTElayer[jj]/mu3DSTElayer[0];
  }
  h_compare_mu->Fill(dedxCompare);
}

if(muECALEnergy>0){
  dedxECAL_mu -> Fill(muECALFar,muECALEnergy);
  ecal_mu1->Fill(sqrt(lepDeath[0]*lepDeath[0]+lepDeath[1]*lepDeath[1]+lepDeath[2]*lepDeath[2]), muECALEnergy );
  ecal_mu2->Fill(muECALFarYZ, muECALEnergy);
  deECAL_mu->Fill(muECALEnergy);
  dxECAL_mu->Fill(muECALFarYZ);
}
}
}
cout<<"total nc, cc and ncnpip : "<<nc_tot<<" "<<cc_tot<<" "<<nc_npip<<endl;
cout<<"cc total, escape, contained and ecal fraction : "<<cc_tot<<" "<<cc_nlep_contained/cc_tot<<" "<<cc_nlep_escape/cc_tot<<" "<<cc_nlep_ecal/cc_tot<<endl;
cout<<"Nc total, escape, contained and ecal fraction : "<<nc_npip<<" "<<nc_npip_contained/nc_npip<<" "<<nc_npip_escape/nc_npip<<" "<<nc_npip_ecal/nc_npip<<endl;

new TCanvas();
nu_spec_NC->Draw();
new TCanvas();
nu_spec_CC->Draw();
new TCanvas();
mu_spec_CC->Draw();
new TCanvas();
pi_spec_NC->Draw();
new TCanvas();
cc_death->Draw("colz");
new TCanvas();
nc_death->Draw("colz");

new TCanvas();
nc_ecal_deposit->Draw("colz");
new TCanvas();
cc_ecal_deposit->Draw("colz");
/*
new TCanvas();
g1->SetMarkerSize(2);
g1->SetMarkerStyle(4);
g1->SetMarkerColor(2);
g1->Draw("AP");
g2->SetMarkerSize(2);
g2->SetMarkerStyle(4);
g2->SetMarkerColor(4);
g2->Draw("same AP");

new TCanvas();
h1_pi->Draw("colz");
new TCanvas();
h1_mu->Draw("colz");
new TCanvas();
h2_pi->Draw("colz");
new TCanvas();
h2_mu->Draw("colz");

new TCanvas();
massRes_pi->SetLineColor(2);
massRes_pi->SetLineWidth(3);
massRes_mu->SetLineColor(4);
massRes_mu->SetLineWidth(3);
massRes_mu->Scale(massRes_pi->Integral()/massRes_mu->Integral());
massRes_pi->Draw("hist");
massRes_mu->Draw("hist same");

new TCanvas();
//dedxECAL_mu->SetLineWidth(3);
//dedxECAL_mu->SetLineColor(2);
//dedxECAL_pi->SetLineWidth(3);
//dedxECAL_pi->SetLineColor(4);
dedxECAL_mu->Draw("colz");

new TCanvas();
dedxECAL_pi->Draw("colz");

new TCanvas();
deECAL_mu->SetLineWidth(3);
deECAL_mu->SetLineColor(2);
deECAL_pi->SetLineWidth(3);
deECAL_pi->SetLineColor(4);
deECAL_pi->Draw("");
deECAL_mu->Draw("same");

new TCanvas();
dxECAL_mu->SetLineWidth(3);
dxECAL_mu->SetLineColor(2);
dxECAL_pi->SetLineWidth(3);
dxECAL_pi->SetLineColor(4);
dxECAL_pi->Draw("");
dxECAL_mu->Draw("same");

new TCanvas();
h_compare_mu->SetLineWidth(3);
h_compare_mu->SetLineColor(2);
h_compare_pi->SetLineWidth(3);
h_compare_pi->SetLineColor(4);
h_compare_pi->Draw("");
h_compare_mu->Draw("same");

new TCanvas();
ecal_mu1->Draw("colz");
new TCanvas();
ecal_mu2->Draw("colz");
new TCanvas();
ecal_pi1->Draw("colz");
new TCanvas();
ecal_pi2->Draw("colz");
*/
}
