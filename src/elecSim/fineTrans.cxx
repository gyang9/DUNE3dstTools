#include "fineTrans.hxx"
#include "TTree.h"

using namespace std;

void fineTrans::doFineTrans( int inputF, int ident){

//Double_t E,startX,startY,startZ,stopX,stopY,stopZ,startT,stopT;
Int_t eventN;
//std::string det;
//Int_t iii=0;

//constants for energy calibration
const double CBIRKS = 0.00208; // mm/MeV
const double EdepToPhotConv_FGD = 70.8; // CLHEP::MeV; // contains both collection in fiber and edep->gamma conversion 
const double DistMPPCscint_FGD = 41; //*CLHEP::mm;
const double LongCompFrac_FGD = 0.816;
const double LongAtt_FGD = 11926.; //*CLHEP::mm;
const double ShortAtt_FGD = 312.; //*CLHEP::mm;
const double DecayLength_FGD = 0.0858; // CLHEP::mm;
const double Lbar_FGD = 1864.3; //* CLHEP::mm;
const double TransTimeInFiber = 1./28. *10.; //mm/ns
// SuperFGD constants
const double MPPCEff_SuperFGD = 0.38;

// Approximate collection factors from PDG2016 (Detectors and accelerators section)
//const double CollFactor_SingleClad = 0.06;
//const double CollFactor_DoubleClad = 0.054; // from Licciardi's thesis  
const double CollFactor_DoubleClad = 0.10;

const double Pedestal = 0;//145;  // pedeltal of ADC counts
const double Gain = 10;  // Gain ADC counts of high gain channel
const double LowGain  = 1;  // Gain ADC counts of low gain channel
const double ElecNoise = 1.7;  // sigma of high gain electronics noise
const double LowElecNoise = 1.2;  // sigma of low gain electronics noise
//const double PixelGainVari = 0.031;  // gain variation among pixels

double a=0.;        // long attenuation component fraction
double d=0.;        // distance MPPC-scint outside the bar
double LongAtt=0.;  // long attenuation length
double ShortAtt=0.; // short attenuation length
double Ldecay=0.;   // decay length
Ldecay = Ldecay;
double Lbar=0.;     // bar length
Lbar = Lbar;
 
double hitLocation[3000][3]={},hitPE[3000][3]={},hitT[3000][3]={};
double adc_tmp[3000][3]={},loadc_tmp[3000][3]={},Q[3000][3]={},loQ[3000][3]={},adc[3000][3]={};
double loadc[3000][3]={};
loadc[0][0] = loadc[0][0];
Int_t prim[3000],PDG[3000];
double ener[3000];
double trueMom=0,trueLen=0;
trueMom = trueMom;
trueLen = trueLen;
double true3Mom[3]={};
true3Mom[0] = true3Mom[0];
double true4Mom[100][4]={};
double trueCos[100]={};
double Enu;
int Mode;
int nupdg;
Int_t if3DST[3000]={};
Int_t ifTPC[3000]={};
double contrib[3000]={};
double vtxPoint[4] = {};
Int_t NHits = 0;
Int_t hitPE_m[3000][3]={};
double startPoint[30][3]={};
double trjStart[200][3]={};
double trjPDG[200]={};
double trjId[200]={};
double trjParentId[200]={};
double trjMom[200][3]={};

//TFile* outFile = TFile::Open(Form("/dune/app/users/gyang/elecSim/full3DST.neutrino.eleSim.CCRES.file%d.patch%d.root", inputF, ident),"RECREATE");
TFile* outFile = TFile::Open("elecSim_output.root","RECREATE");
TTree* c = new TTree("EDepSimTree","EDepSimTree");
c->Branch("event",&eventN,"event/I");
c->Branch("nhits", &NHits, "nhits/I");
c->Branch("hitLocation",&hitLocation,"hitLocation[nhits][3]/D");
c->Branch("hitPE_mean",&hitPE,"hitPE_mean[nhits][3]/D");
c->Branch("hitPE_measure",&hitPE_m,"hitPE_measure[nhits][3]/I");
c->Branch("hitT",&hitT,"hitT[nhits][3]/D");
c->Branch("hitADC",&adc,"hitADC[nhits][3]/D");
c->Branch("hitQ",&Q,"hitQ[nhits][3]/D");
c->Branch("hitPrim",&prim,"hitPrim[nhits]/I");
c->Branch("hitPDG",&PDG,"hitPDG[nhits]/I");
c->Branch("hitE",&ener,"hitE[nhits]/D");
c->Branch("trueCos",&trueCos,"trueCos[100]/D");
c->Branch("true4Mom",&true4Mom,"true4Mom[100][4]/D");
c->Branch("if3DST",&if3DST,"if3DST[nhits]/I");
//c->Branch("startPoint",&startPoint,"startPoint[30][3]/D");
//c->Branch("trackId",&contrib,"contrib[nhits]/D");
//c->Branch("trjStart",&trjStart,"trjStart[200][3]/D");
//c->Branch("trjPDG",&trjPDG,"trjPDG[200]/D");
//c->Branch("trjId",&trjId,"trjId[200]/D");
//c->Branch("trjParentId",&trjParentId,"trjParentId[200]/D");
//c->Branch("trjMom",&trjMom,"trjMom[200][3]/D");

c->Branch("ifTPC",&ifTPC,"ifTPC[nhits]/I");
c->Branch("vtxPoint",&vtxPoint,"vtxPoint[4]/D");
c->Branch("Mode",&Mode,"Mode/I");
c->Branch("Enu",&Enu,"Enu/D");
c->Branch("nuPDG",& nupdg,"nuPDG/I");
//c->Branch("trueLen",&trueLen,"trueLen/D");
//c->Branch("trueMom",&trueMom,"trueMom/D");
//c->Branch("hitLowQ",&loQ,"hitLowQ[3]/D");
//c->Branch("hitLowADC",&loadc,"hitLowADC[3]/D");

//TFile g(Form("/pnfs/dune/persistent/users/gyang/3DST/edep/fullGeo/standardGeo10/PROD_CCRES/full3DST.neutrino.%d.edepsim.root",inputF));
TFile g("/home/guang/work/DUNE3dstTools/build/full3DST.antineutrino.99.edepsim.root");
TTree* events = (TTree*) g.Get("EDepSimEvents");

TG4Event* event=NULL;
events->SetBranchAddress("Event",&event);
Int_t nevent = events->GetEntries();

Int_t StdHepPdgb[10000];
Int_t StdHepStatusb[10000];
Int_t StdHepN;
Double_t vtxb[4]={};
Double_t ivtxb[10000][4]={};
Double_t imomb[10000][4]={};
//Bool_t flagb=false;
//Bool_t wflagb=false;
//Int_t rightSignb=0,wrongSignb=0;
double nuenergy[10000]={};
int interactionMode[10000]={};
int nuPDG[10000]={};
double vtxin[10000][3]={};
TRandom3* random1 = new TRandom3();
TRandom3* random2 = new TRandom3();
random2->SetSeed(6666);

//TFile f1b(Form("/pnfs/dune/persistent/users/gyang/3DST/genie/fullGeo/standardGeo10/PROD_CCRES/full3DST.neutrino.%d.rootracker.root",inputF));
TFile f1b(Form("/home/guang/work/DUNE3dstTools/build/full3DST.antineutrino.99.rootracker.root"));
TTree* h1b = (TTree*) f1b.Get("gRooTracker");

h1b->SetBranchAddress("StdHepPdg", &StdHepPdgb);
h1b->SetBranchAddress("StdHepStatus", &StdHepStatusb);
h1b->SetBranchAddress("EvtVtx", &vtxb);
h1b->SetBranchAddress("StdHepX4", &ivtxb);
h1b->SetBranchAddress("StdHepP4", &imomb);
h1b->SetBranchAddress("StdHepN", &StdHepN);

//Int_t nentriesb = (Int_t) h1b->GetEntries();

for(Int_t ib=nevent*ident; ib<nevent*(ident+1) ; ib++) {

  h1b->GetEntry(ib);

  vtxin[ib][0] = vtxb[0];
  vtxin[ib][1] = vtxb[1];
  vtxin[ib][2] = vtxb[2];
  vtxin[ib][3] = vtxb[3];
  
  //std::cout<<"neutrino energy "<<imomb[0][3]<<" vertex "<<vtxin[ib][0]<< std::endl;
  for(Int_t iib=0;iib<3;iib++){
    if(StdHepPdgb[iib]==14){
      nuPDG[ib] = 14;
      nuenergy[ib] = imomb[iib][3]; break;
    }
    if(StdHepPdgb[iib]==-14){
      nuPDG[ib] = -14;
      nuenergy[ib] = imomb[iib][3]; break;
    }
    if(StdHepPdgb[iib]==12){
      nuPDG[ib] = 12;
      nuenergy[ib] = imomb[iib][3]; break;
    }
    if(StdHepPdgb[iib]==-12){
      nuPDG[ib] = -12;
      nuenergy[ib] = imomb[iib][3]; break;
    }
  }
  int cPi = 0; int zPi = 0;
  for(Int_t iib=2; iib<20; iib++){
    if(abs(StdHepPdgb[iib])>=2000000000)  break;
    if(TMath::Abs(StdHepPdgb[iib])==211 && StdHepStatusb[iib]==1){
      cPi ++;
    }
    if(TMath::Abs(StdHepPdgb[iib])==111 && StdHepStatusb[iib]==1){
      zPi ++;
    }
  }
  if(cPi==0 && zPi==0) interactionMode[ib] = 1;
  else if(cPi>0 && zPi==0) interactionMode[ib] = 2;
  else if(cPi==0 && zPi>0) interactionMode[ib] = 3;
  else if(cPi>0 && zPi>0) interactionMode[ib] = 4;  
}

/////////////////////////////////////////////////////////////////////////////////////

for(Int_t ii=nevent*ident;ii<nevent*(ident+1);ii++){

  events->GetEntry(ii);
  std::cout<<"event number "<<ii<<"----------------- number of prim. particle "<<event->Primaries[0].Particles.size()<<std::endl;

  //double randomNumber = random1->Gaus(0,0.03);
  eventN = ii;
  Enu = nuenergy[ii];
  Mode = interactionMode[ii];
  nupdg = nuPDG[ii];
  vtxPoint[0] = vtxin[ii][0];
  vtxPoint[1] = vtxin[ii][1];
  vtxPoint[2] = vtxin[ii][2]-4.5;
  vtxPoint[3] = vtxin[ii][3];
  //std::cout<<"re-check neutrino energy "<<Enu<<" and vertex "<<vtxin[ii][0]<<" "<<vtxPoint[0]<<std::endl;

  NHits = 0;

  for (Int_t ccloop1 = 0;ccloop1< 3000 ; ccloop1++){
    prim[ccloop1] = -1;
    PDG[ccloop1] = -1;
    ener[ccloop1] = -1;
    if3DST[ccloop1] = -1;
    ifTPC[ccloop1] = -1;
    contrib[ccloop1] = -1;
    if (ccloop1 < 30){
      trueCos[ccloop1]=-1;  
    }
    for(Int_t ccloop2 = 0; ccloop2<3; ccloop2++){
      hitLocation[ccloop1][ccloop2]=-1;
      hitPE[ccloop1][ccloop2]=-1;
      hitPE_m[ccloop1][ccloop2]=-1;
      hitT[ccloop1][ccloop2]=-1;
      adc[ccloop1][ccloop2]=-1;
      Q[ccloop1][ccloop2]=-1;
    }
  }

  for (Int_t ccloop1 = 0;ccloop1< 100 ; ccloop1++){
    for(Int_t ccloop2 = 0; ccloop2<4; ccloop2++){
      true4Mom[ccloop1][ccloop2]=-1;
    }
  }

  for (Int_t ccloop1 = 0;ccloop1< 100 ; ccloop1++){
    for(Int_t ccloop2 = 0; ccloop2<3; ccloop2++){
      trjStart[ccloop1][ccloop2]=-1;
      trjMom[ccloop1][ccloop2]=-1;
    }
    trjPDG[ccloop1]=-1;
    trjId[ccloop1]=-1;
    trjParentId[ccloop1]=-1;
  }

for(auto sd : event->Trajectories)
{
  for(int iTrj=0; iTrj< (int)event->Trajectories.size(); iTrj++){
    if(iTrj>99) break;
    trjStart[iTrj][0] = event->Trajectories[iTrj].Points[0].Position.X();
    trjStart[iTrj][1] = event->Trajectories[iTrj].Points[0].Position.Y();
    trjStart[iTrj][2] = event->Trajectories[iTrj].Points[0].Position.Z();

    trjId[iTrj] = event->Trajectories[iTrj].TrackId;
    trjParentId[iTrj] = event->Trajectories[iTrj].ParentId;
    trjPDG[iTrj] = event->Trajectories[iTrj].PDGCode;
    trjMom[iTrj][0] = event->Trajectories[iTrj].InitialMomentum.Px();
    trjMom[iTrj][1] = event->Trajectories[iTrj].InitialMomentum.Py();
    trjMom[iTrj][2] = event->Trajectories[iTrj].InitialMomentum.Pz();
  }
}

for(auto sd : event->SegmentDetectors)
{
  for(Int_t i=0;i<(int)sd.second.size();i++){

  /*  T2K upgrade numbers
  --- Cut levels --------
  < highlandCorrections.mom_corrections.sigma_x = 0.800 >   // minimum accum level to save the event
  < highlandCorrections.mom_corrections.B = 0.2 >   // minimum accum level to save the event


  --- Event Weights ------------

  Enable/disable configurations with a single systematic (when EnableSingleWeightSystConfigurations = 1)
  and enable systematics in the "all_syst" configuration (when EnableAllSystematics = 1)

  < highlandCorrections.mom_corrections.x0 = 115.103 > 
  */
    //std::cout<<sd.first<<std::endl;
    TString det = sd.first;

    if( det.Contains("TPC") ){
      if(sd.second[i].TrackLength>0 && NHits<3000){

        ifTPC[NHits] = 1;

	// point resolution for T2K TPC 0.7 um : https://arxiv.org/pdf/1012.0865.pdf
        double xlocation = random2->Gaus((sd.second[i].Stop.X()+sd.second[i].Start.X())/2.,0.7);
        double ylocation = random2->Gaus((sd.second[i].Stop.Y()+sd.second[i].Start.Y())/2.,0.7);
        double zlocation = random2->Gaus((sd.second[i].Stop.Z()+sd.second[i].Start.Z())/2.-4500. ,0.7);

        prim[NHits] = sd.second[i].PrimaryId;
        PDG[NHits] = event->Primaries[0].Particles[prim[NHits]].PDGCode;

        trueMom = event->Primaries[0].Particles[prim[NHits]].Momentum.Energy();
        trueLen = 0;
        true3Mom[0]=event->Primaries[0].Particles[prim[NHits]].Momentum.Px();
        true3Mom[1]=event->Primaries[0].Particles[prim[NHits]].Momentum.Py();
        true3Mom[2]=event->Primaries[0].Particles[prim[NHits]].Momentum.Pz();

        int primTemp = prim[NHits];
        if(primTemp < 30){

          true4Mom[primTemp][0] = event->Primaries[0].Particles[prim[NHits]].Momentum.Px();
          true4Mom[primTemp][1] = event->Primaries[0].Particles[prim[NHits]].Momentum.Py();
          true4Mom[primTemp][2] = event->Primaries[0].Particles[prim[NHits]].Momentum.Pz();
          true4Mom[primTemp][3] = event->Primaries[0].Particles[prim[NHits]].Momentum.Energy();
          trueCos[primTemp] = event->Primaries[0].Particles[prim[NHits]].Momentum.CosTheta();
        }

        hitLocation[NHits][0]=xlocation;
        hitLocation[NHits][1]=ylocation;
        hitLocation[NHits][2]=zlocation;

        ener[NHits] = sd.second[i].EnergyDeposit;
        NHits++;
      }
    }

    //////////////////////////////////////////////////////////////////////////////////

    else if( det.Contains("Cube") ){
      if(sd.second[i].TrackLength>0 && NHits<3000){

        if3DST[NHits] = 1;

        int aveX= ((sd.second[i].Stop.X()+sd.second[i].Start.X())/2.)/10 ;
        int aveY= ((sd.second[i].Stop.Y()+sd.second[i].Start.Y())/2.)/10 ;
        int aveZ= ((sd.second[i].Stop.Z()+sd.second[i].Start.Z())/2.)/10 ;

        double xlocation = aveX*10. + 5 + 0.;
        double ylocation = aveY*10. + 5 + 0.;
        double zlocation = aveZ*10. + 5 - 4500.;

        prim[NHits] = sd.second[i].PrimaryId;
	contrib[NHits] = sd.second[i].Contrib[0];       
 
        PDG[NHits] = event->Primaries[0].Particles[prim[NHits]].PDGCode; 

        trueMom = event->Primaries[0].Particles[prim[NHits]].Momentum.Energy();
        trueLen = 0;
	true3Mom[0]=event->Primaries[0].Particles[prim[NHits]].Momentum.Px();
	true3Mom[1]=event->Primaries[0].Particles[prim[NHits]].Momentum.Py();
	true3Mom[2]=event->Primaries[0].Particles[prim[NHits]].Momentum.Pz();
/*
        for(int iTrj=0; iTrj< event->Trajectories.size(); iTrj++){
	  if(iTrj>99) break;

          trjStart[iTrj][0] = event->Trajectories[iTrj].Points[0].Position.X();
	  trjStart[iTrj][1] = event->Trajectories[iTrj].Points[0].Position.Y();
          trjStart[iTrj][2] = event->Trajectories[iTrj].Points[0].Position.Z();

	  trjId[iTrj] = event->Trajectories[iTrj].TrackId;
  	  trjParentId[iTrj] = event->Trajectories[iTrj].ParentId;
	  trjPDG[iTrj] = event->Trajectories[iTrj].PDGCode;
	  trjMom[iTrj][0] = event->Trajectories[iTrj].InitialMomentum.Px();
          trjMom[iTrj][1] = event->Trajectories[iTrj].InitialMomentum.Py();
          trjMom[iTrj][2] = event->Trajectories[iTrj].InitialMomentum.Pz();
	  
          std::cout<<"check point -----------------------------------------iTrj, traj. z-mom, pdg, id, parentId, start-z, hit prim, hit pdg, hit contrib"<<std::endl;
          std::cout<<iTrj<<" "<<event->Trajectories[iTrj].InitialMomentum.Pz()<<" "<<
	  event->Trajectories[iTrj].PDGCode<<" "<<event->Trajectories[iTrj].TrackId<<" "<<std::endl;
	  
	  std::cout<<event->Trajectories[iTrj].ParentId<<" "<<event->Trajectories[iTrj].Points[0].Position.Z()<<" "<<std::endl;
	  std::cout<<sd.second[i].PrimaryId <<" "<< event->Primaries[0].Particles[prim[NHits]].TrackId <<std::endl; 
	  std::cout<<sd.second[i].Contrib[0] <<std::endl;
	  if(sd.second[i].Contrib[0] != event->Primaries[0].Particles[prim[NHits]].TrackId || sd.second[i].Contrib[0] != sd.second[i].PrimaryId ) { std::cout<<"shoot"<<std::endl; exit(1); }
	}
*/
	int primTemp = prim[NHits];
	if(primTemp < 30){
          startPoint[primTemp][0]= event->Trajectories[prim[NHits]].Points[0].Position.X()  ;
          startPoint[primTemp][1]= event->Trajectories[prim[NHits]].Points[0].Position.Y()  ;
          startPoint[primTemp][2]= event->Trajectories[prim[NHits]].Points[0].Position.Z() - 4500 ;

	  true4Mom[primTemp][0] = event->Primaries[0].Particles[prim[NHits]].Momentum.Px();
	  true4Mom[primTemp][1] = event->Primaries[0].Particles[prim[NHits]].Momentum.Py();
	  true4Mom[primTemp][2] = event->Primaries[0].Particles[prim[NHits]].Momentum.Pz();
	  true4Mom[primTemp][3] = event->Primaries[0].Particles[prim[NHits]].Momentum.Energy();
	  trueCos[primTemp] = event->Primaries[0].Particles[prim[NHits]].Momentum.CosTheta();
	}

	hitLocation[NHits][0]=xlocation;
	hitLocation[NHits][1]=ylocation;
	hitLocation[NHits][2]=zlocation;

	ener[NHits] = sd.second[i].EnergyDeposit;

	Double_t dedx = sd.second[i].EnergyDeposit/sd.second[i].TrackLength;
	Double_t edep= sd.second[i].EnergyDeposit/(1. + CBIRKS*dedx);

        // Account for the 3 fibers in the same scintillator cube
        double collfact = CollFactor_DoubleClad;
        double fact_fib1 = collfact;
        double fact_fib2 = (1-fact_fib1)*collfact;
        double fact_fib3 = (1-fact_fib2)*collfact;
        double CollFactAve = (fact_fib1+fact_fib2+fact_fib3)/3.;
        double NormShadowLight = CollFactAve / collfact; // fraction 
        double Nphot = edep * EdepToPhotConv_FGD * NormShadowLight;

        a = LongCompFrac_FGD;
        d = DistMPPCscint_FGD;
        LongAtt = LongAtt_FGD;
        ShortAtt = ShortAtt_FGD;
        Ldecay= DecayLength_FGD;
        Lbar = Lbar_FGD;

  	double xx = 2400 - xlocation;
  	double yy = 2400 - ylocation;
  	double zz = 2000 - zlocation;  
  	double NphotXY = Nphot * ( a*TMath::Exp((-zz-d)/LongAtt) + (1-a)*TMath::Exp((-zz-d)/ShortAtt) ) * (1/3.);
  	double NphotXZ = Nphot * ( a*TMath::Exp((-yy-d)/LongAtt) + (1-a)*TMath::Exp((-yy-d)/ShortAtt) ) * (1/3.);
  	double NphotYZ = Nphot * ( a*TMath::Exp((-xx-d)/LongAtt) + (1-a)*TMath::Exp((-xx-d)/ShortAtt) ) * (1/3.);

  	double TimeDelayXY =  sd.second[i].Start.T()+TransTimeInFiber * zz;
  	double TimeDelayXZ =  sd.second[i].Start.T()+TransTimeInFiber * yy;
  	double TimeDelayYZ =  sd.second[i].Start.T()+TransTimeInFiber * xx;

  	double peXY = NphotXY * MPPCEff_SuperFGD;
  	double peXZ = NphotXZ * MPPCEff_SuperFGD;
  	double peYZ = NphotYZ * MPPCEff_SuperFGD;

	random1->SetSeed(NHits*30);
  	hitT[NHits][0]=TimeDelayXY + (double)random1->Gaus(0,0.5);
	random1->SetSeed(NHits*31);
  	hitT[NHits][1]=TimeDelayXZ + (double)random1->Gaus(0,0.5);
	random1->SetSeed(NHits*32);
  	hitT[NHits][2]=TimeDelayYZ + (double)random1->Gaus(0,0.5);

  	hitPE[NHits][0]=peXY;
  	hitPE[NHits][1]=peXZ;
  	hitPE[NHits][2]=peYZ;

  	random1->SetSeed(NHits*10);
  	if(peXY>0)
    	  hitPE_m[NHits][0]= (int)random1->Poisson(peXY) ;
  	random1->SetSeed(NHits*11);
  	if(peXZ>0)
    	  hitPE_m[NHits][1]= (int)random1->Poisson(peXZ) ;
  	random1->SetSeed(NHits*12);
  	if(peYZ>0)
    	  hitPE_m[NHits][2]= (int)random1->Poisson(peYZ) ;

  	for(Int_t dim =0;dim<3;dim++){
  	  //PE to ADC
  	  adc_tmp[NHits][dim] = Pedestal + (hitPE[NHits][dim])*Gain;
  	  loadc_tmp[NHits][dim] = Pedestal + (hitPE[NHits][dim])*LowGain*14.29/13.55;

  	  //Electronics noise
  	  adc_tmp[NHits][dim] = random1->Gaus(adc_tmp[NHits][dim],ElecNoise);
  	  loadc_tmp[NHits][dim] = random1->Gaus(loadc_tmp[NHits][dim],LowElecNoise);

  	  //ADC to Charge
  	  //Q=(adc_tmp+53)/217;
  	  //loQ=(loadc_tmp+82)/26;
  	  Q[NHits][dim]=(adc_tmp[NHits][dim])/135.5;
  	  loQ[NHits][dim]=(loadc_tmp[NHits][dim])/14.29;

  	  //Non linearlity of high gain ADC
          if(Q[NHits][dim]<0.65) adc[NHits][dim]=135.5*Q[NHits][dim];
  	  else if(Q[NHits][dim]<3.2)  adc[NHits][dim]=217*Q[NHits][dim]-53;
  	  else if(Q[NHits][dim]<4.2)  adc[NHits][dim]=158.6*Q[NHits][dim]+133.9;
  	  else if(Q[NHits][dim]<14)  adc[NHits][dim]=5.1*Q[NHits][dim]+778.6;
  	  else  adc[NHits][dim]=850;

  	  //Non linearlity of low gain ADC
  	  if(loQ[NHits][dim]<7)  loadc[NHits][dim]=14.29*loQ[NHits][dim];
  	  else if(loQ[NHits][dim]<27)  loadc[NHits][dim]=26*loQ[NHits][dim]-82;
  	  else if(loQ[NHits][dim]<35.5)  loadc[NHits][dim]=21.12*loQ[NHits][dim]+48.24;
  	  else if(loQ[NHits][dim]<178.4)  loadc[NHits][dim]=0.7*loQ[NHits][dim]+775.1;
 	  else  loadc[NHits][dim]=900;
  	}	

  	NHits++;
      }
    }

    ///////////////////////////////////////////////////////////////////////////
    else{

      if(sd.second[i].TrackLength>0 && NHits<3000){

        ifTPC[NHits] = 0;
	if3DST[NHits] = 0;

        double xlocation = random2->Gaus((sd.second[i].Stop.X()+sd.second[i].Start.X())/2.,0.);
        double ylocation = random2->Gaus((sd.second[i].Stop.Y()+sd.second[i].Start.Y())/2.,0.);
        double zlocation = random2->Gaus((sd.second[i].Stop.Z()+sd.second[i].Start.Z())/2.-5000. ,0.);

        prim[NHits] = sd.second[i].PrimaryId;
        PDG[NHits] = event->Primaries[0].Particles[prim[NHits]].PDGCode;

        trueMom = event->Primaries[0].Particles[prim[NHits]].Momentum.Energy();
        trueLen = 0;
        true3Mom[0]=event->Primaries[0].Particles[prim[NHits]].Momentum.Px();
        true3Mom[1]=event->Primaries[0].Particles[prim[NHits]].Momentum.Py();
        true3Mom[2]=event->Primaries[0].Particles[prim[NHits]].Momentum.Pz();

        int primTemp = prim[NHits];
        if(primTemp < 30){

          true4Mom[primTemp][0] = event->Primaries[0].Particles[prim[NHits]].Momentum.Px();
          true4Mom[primTemp][1] = event->Primaries[0].Particles[prim[NHits]].Momentum.Py();
          true4Mom[primTemp][2] = event->Primaries[0].Particles[prim[NHits]].Momentum.Pz();
          true4Mom[primTemp][3] = event->Primaries[0].Particles[prim[NHits]].Momentum.Energy();
          trueCos[primTemp] = event->Primaries[0].Particles[prim[NHits]].Momentum.CosTheta();
        }

        hitLocation[NHits][0]=xlocation;
        hitLocation[NHits][1]=ylocation;
        hitLocation[NHits][2]=zlocation;

        ener[NHits] = sd.second[i].EnergyDeposit;
        NHits++;
      }
    }

  }
}
c->Fill();

}
outFile->Write();
outFile->Close();
}



