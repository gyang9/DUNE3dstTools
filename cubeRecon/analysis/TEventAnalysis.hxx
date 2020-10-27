#ifndef TEventAnalysis_hxx_seen
#define TEventAnalysis_hxx_seen

#include "TEventManager.hxx"
#include "TReconTrackElement.hxx"
#include "TReconShowerElement.hxx"
#include "TReconClusterElement.hxx"

#include <CubeReconObject.hxx>
#include <CubeReconCluster.hxx>
#include <CubeReconShower.hxx>
#include <CubeReconTrack.hxx>
#include <CubeReconVertex.hxx>
#include <CubeHandle.hxx>
#include <CubeReconNode.hxx>
#include <CubeLog.hxx>
#include <CubeAlgorithmResult.hxx>

#include <TUnitsTable.hxx>

#include <TGeoManager.h>
#include <TGeoShape.h>
#include <TGeoEltu.h>
#include <TGeoSphere.h>
#include <TGeoMatrix.h>

#include <ToolPrimaryId.hxx>
#include <ToolG4Hits.hxx>
#include <ToolMainTrajectory.hxx>
#include <ToolTrueDirection.hxx>

#include <TFile.h>
#include <TObject.h>

namespace Cube {
    class TEventAnalysis;
}

class TEveElementList;

class Cube::TEventAnalysis: public TObject {
public:

    TEventAnalysis(TFile* file);
    virtual ~TEventAnalysis();
    static TFile* fEventSource;

    struct infoList{
      double x;
      double y;
      double z;
      double t;
      double px;
      double py;
      double pz;
      double e;
      double l;
      double xt;
      double yt;
      double zt;
      double pxt;
      double pyt;
      double pzt;
      double et;
      double lt;
      double tt;
      int pdg;
    };

    static const struct infoList EmptyStruct;

    int eventCounter = 0;

private:

    void Run(TFile* file);
    void Init(TFile* file);
    double fEnergyPerCharge;

    void FillEntries(std::vector<std::string>& entries,
                     std::string baseName,
                     Cube::Handle<Cube::AlgorithmResult> current);    


    int ShowReconObjects(const Cube::Handle<Cube::ReconObjectContainer> obj,
                         int index = 0);

    int ShowReconObjects(const Cube::Handle<Cube::ReconObjectContainer> obj, std::vector<double> clusterResultList, int index = 0);

    std::vector<Cube::TEventAnalysis::infoList> ShowReconObjects(const Cube::Handle<Cube::ReconObjectContainer> obj, std::vector<Cube::TEventAnalysis::infoList> allResultList, int index = 0);    

    //int ShowReconTrack(const Cube::Handle<Cube::ReconTrack> obj,
    //		      int index=0) ;

    int ShowReconShower(const Cube::Handle<Cube::ReconShower> obj,
                      int index=0) ;

    //int ShowReconCluster(const Cube::Handle<Cube::ReconCluster> obj,
    //                  int index=0) ; 

    Cube::TEventAnalysis::infoList ShowReconCluster(const Cube::Handle<Cube::ReconCluster> obj, int index=0 ) ;     

    Cube::TEventAnalysis::infoList ShowReconTrack(const Cube::Handle<Cube::ReconTrack> obj, int index=0 ) ;

    double reco_x[1000];
    double reco_y[1000];
    double reco_z[1000];
    double reco_t[1000];
    double reco_px[1000];
    double reco_py[1000];
    double reco_pz[1000];
    double reco_e[1000];
    double reco_l[1000];
    double true_x[1000];
    double true_y[1000];
    double true_z[1000];
    double true_t[1000];
    double true_px[1000];
    double true_py[1000];
    double true_pz[1000];
    double true_e[1000];
    double true_l[1000];
    int true_pdg[1000];
    
    int event_number;
    TFile* hfile;
    TTree* htree;

    void setupTree(std::string filename){
      hfile = TFile::Open(Form("%s.root",filename.c_str()) ,"RECREATE");
      htree = new TTree("tree","tree");
      htree->Branch("event_number",&event_number,"event_number/I");
      htree->Branch("reco_x",&reco_x,"reco_x[1000]/D");
      htree->Branch("reco_y",&reco_y,"reco_y[1000]/D");
      htree->Branch("reco_z",&reco_z,"reco_z[1000]/D");
      htree->Branch("reco_t",&reco_t,"reco_t[1000]/D");
      htree->Branch("reco_px",&reco_px,"reco_px[1000]/D");
      htree->Branch("reco_py",&reco_py,"reco_py[1000]/D");
      htree->Branch("reco_pz",&reco_pz,"reco_pz[1000]/D");
      htree->Branch("reco_energy",&reco_e,"reco_energy[1000]/D");
      htree->Branch("reco_length",&reco_l,"reco_length[1000]/D");

      htree->Branch("true_x",&true_x,"true_x[1000]/D");
      htree->Branch("true_y",&true_y,"true_y[1000]/D");
      htree->Branch("true_z",&true_z,"true_z[1000]/D");
      htree->Branch("true_t",&true_t,"true_t[1000]/D");
      htree->Branch("true_px",&true_px,"true_x[1000]/D");
      htree->Branch("true_py",&true_py,"true_x[1000]/D");
      htree->Branch("true_pz",&true_pz,"true_x[1000]/D");
      htree->Branch("true_energy",&true_e,"true_energy[1000]/D");
      htree->Branch("true_length",&true_l,"true_length[1000]/D");
      htree->Branch("pdg",&true_pdg,"pdg[1000]/I");
    }

    void fillTree(){
      htree->Fill();
      //std::cout<<"------------------------ tree filled with "<<reco_x<<" "<<event_number<<std::endl;
    }


};

#endif
