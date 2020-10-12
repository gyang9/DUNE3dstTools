#include "TEventAnalysis.hxx"

#include <TEveManager.h>
#include <TColor.h>
#include <TGLViewer.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include <chrono>
#include <thread>

//ClassImp(Cube::TEventAnalysis)

TTree* Cube::gCubeReconTree = NULL;
Cube::Event* Cube::gEvent = NULL;
Cube::AlgorithmResult* Cube::gAlgorithm = NULL;
int Cube::gCubeReconEntryNumber = 0;

Cube::TEventAnalysis::TEventAnalysis(TFile* file) { Init(file); }

void Cube::TEventAnalysis::Init(TFile* file) {

    // This is accessed through the GUI() method.
    //fGUIManager = new TGUIManager();

    // Create the event analysis manager.  This needs the GUI, so it has to be
    // done after TGUIManager is created.
    //fEventChangeManager = new TEventChangeManager();
    //fEventChangeManager->AddUpdateHandler(new TFindResultsHandler());
    // fEventChangeManager->AddUpdateHandler(new TTrajectoryChangeHandler());
    //fEventChangeManager->AddUpdateHandler(new TG4HitChangeHandler());
    //fEventChangeManager->AddUpdateHandler(new THitChangeHandler());
    //fEventChangeManager->AddUpdateHandler(new TFitChangeHandler());

    Run(file);
    std::cout << "Event analysis constructed" << std::endl;


}

void Cube::TEventAnalysis::Run(TFile* eventSource){

    Cube::gCubeReconTree = (TTree*) eventSource->Get("CubeEvents");

    if (!gCubeReconTree) {
        std::cout << "Missing the event tree" << std::endl;
        return;
    }

    Cube::gCubeReconTree->SetBranchAddress("Event",&Cube::gEvent);
    Cube::gCubeReconEntryNumber = 0;

    std::ofstream outstream;
    outstream.open ("testResult.txt", std::ofstream::out | std::ofstream::app);

    std::cout<<"total number of events : "<<gCubeReconTree->GetEntries()<<std::endl;
    for (Int_t i =0; i< gCubeReconTree->GetEntries(); i++){

	outstream << "111111"<<" "<<i<<std::endl;
	std::cout<<"event start number -------------------------------------- "<< i <<std::endl;
    	//gCubeReconTree->GetEntry(Cube::gCubeReconEntryNumber);
        gCubeReconTree->GetEntry(i);

        Cube::Handle<Cube::AlgorithmResult> topResult(Cube::gEvent,false);
        std::cout << "resulted foraged . "<<std::endl;

        std::vector<std::string> existingEntries;
        std::string baseName;

        FillEntries(existingEntries,baseName,topResult);

        for (std::vector<std::string>::iterator e = existingEntries.begin();
            e != existingEntries.end(); ++e) {
            std::cout << "list entry " << *e << std::endl;
        }
	std::cout<<"event end number -------------------------------------- "<< i <<std::endl;
	std::cout<<"--------------------------------------------------------------"<<std::endl;
    }
}

void Cube::TEventAnalysis::FillEntries(
    std::vector<std::string>& entries,
    std::string baseName,
    Cube::Handle<Cube::AlgorithmResult> current) {

    int index = 0;

    baseName += std::string(current->GetName()) + "/";
    for (Cube::AlgorithmResult::ReconObjects::reverse_iterator o
             = current->GetObjectContainers().rbegin();
         o != current->GetObjectContainers().rend(); ++o) {
        Cube::Handle<Cube::ReconObjectContainer> objects
            = gEvent->GetObjectContainer((*o)->GetName());
	
	index = ShowReconObjects(objects,index);

	entries.push_back(baseName + (*o)->GetName());
    }
    std::cout<<"::::::::::::::::::::::::: and the end of ReconObjects , # of objects is :::::::::::::::::: "<<index<<std::endl;
    // Add the daughter results to the stack
    //for (Cube::AlgorithmResult::AlgorithmResults::reverse_iterator r
    //         = current->GetResultsContainer().rbegin();
    //     r !=  current->GetResultsContainer().rend(); ++r) {
    //    FillEntries(entries,baseName,*r);
    //}
}

int Cube::TEventAnalysis::ShowReconObjects(
    Cube::Handle<Cube::ReconObjectContainer> objects,
    int index) {

    for (Cube::ReconObjectContainer::iterator obj = objects->begin();
        obj != objects->end(); ++obj) {
	//std::cout<<"showing the object ! "<<std::endl;
    	Cube::Handle<Cube::ReconTrack> track = (*obj);
	index = ShowReconTrack(track, index);
	std::cout<<":::::::::::::: index for the track : "<<index<<std::endl;

	Cube::Handle<Cube::ReconCluster> cluster = (*obj);
	index = ShowReconCluster(cluster, index);
	std::cout<<":::::::::::::: index for the cluster : "<<index<<std::endl;

	Cube::Handle<Cube::ReconShower> shower = (*obj);
        index = ShowReconShower(shower, index);
	std::cout<<":::::::::::::: index for the shower : "<<index<<std::endl;
    }
    return index;
}	

int Cube::TEventAnalysis::ShowReconTrack(
    Cube::Handle<Cube::ReconTrack> obj,
    int index) {
	
    if (!obj) return index;
    Cube::Handle<Cube::TrackState> frontState = obj->GetState();
    if (!frontState) {
        std::cout << "TrackState is missing!" << std::endl;
	return index;
    }

    ++index;

    std::cout<<"let's output things.. track. "<<std::endl;
    std::unique_ptr<TReconTrackElement> eveTrack(
        new TReconTrackElement(*obj));
	   
    return index;	
}

int Cube::TEventAnalysis::ShowReconShower(
    Cube::Handle<Cube::ReconShower> obj,
    int index) {

    if (!obj) return index;
    Cube::Handle<Cube::ShowerState> frontState = obj->GetState();
    if (!frontState) {
        std::cout << "ShowerState is missing!" << std::endl;
        return index;
    }

    ++index;

    std::cout<<"let's output things.. shower. "<<std::endl;
    Cube::TReconShowerElement *eveShower
        = new Cube::TReconShowerElement(*obj);

    return index;
}

int Cube::TEventAnalysis::ShowReconCluster(
    Cube::Handle<Cube::ReconCluster> obj,
    int index) {

    if (!obj) return index;
    Cube::Handle<Cube::ClusterState> frontState = obj->GetState();
    if (!frontState) {
        std::cout << "ClusterState is missing!" << std::endl;
        return index;
    }

    ++index;

    std::cout<<"let's output things.. cluster. "<<std::endl;    
    Cube::TReconClusterElement *eveCluster
        = new Cube::TReconClusterElement(*obj);

    return index;
}


Cube::TEventAnalysis::~TEventAnalysis() {
    std::cout << "Event analysis deconstructed" << std::endl;
}

// Local Variables:
// mode:c++
// c-basic-offset:4
// compile-command:"$(git rev-parse --show-toplevel)/build/cube-build.sh force"
// End:
