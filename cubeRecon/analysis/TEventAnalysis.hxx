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

#include <TFile.h>
#include <TObject.h>

namespace Cube {
    class TEventAnalysis;
    //class TGUIManager;
    //class TEventChangeManager;
    //class TPlotDigitsHits;
    //class TPlotTimeCharge;
}

class TEveElementList;

class Cube::TEventAnalysis: public TObject {
public:

    TEventAnalysis(TFile* file);
    virtual ~TEventAnalysis();
    static TFile* fEventSource;

private:

    void Run(TFile* file);
    void Init(TFile* file);
    double fEnergyPerCharge;

    void FillEntries(std::vector<std::string>& entries,
                     std::string baseName,
                     Cube::Handle<Cube::AlgorithmResult> current);    


    int ShowReconObjects(const Cube::Handle<Cube::ReconObjectContainer> obj,
                         int index = 0);


    int ShowReconTrack(const Cube::Handle<Cube::ReconTrack> obj,
    		      int index=0) ;

    int ShowReconShower(const Cube::Handle<Cube::ReconShower> obj,
                      int index=0) ;

    int ShowReconCluster(const Cube::Handle<Cube::ReconCluster> obj,
                      int index=0) ;    

};

#endif
