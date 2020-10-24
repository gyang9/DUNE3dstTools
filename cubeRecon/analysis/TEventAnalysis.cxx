#include "TEventAnalysis.hxx"
#include "TTrajectoryHandler.hxx"

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
int Cube::eventCounter = 0;

Cube::TEventAnalysis::TEventAnalysis(TFile* file) { Init(file); }

void Cube::TEventAnalysis::Init(TFile* file) {

    Run(file);
    std::cout << "Event analysis finished" << std::endl;
    exit(1);
}

void Cube::TEventAnalysis::Run(TFile* eventSource){

    Cube::gCubeReconTree = (TTree*) eventSource->Get("CubeEvents");

    if (!gCubeReconTree) {
        std::cout << "Missing the event tree" << std::endl;
        return;
    }

    Cube::gCubeReconTree->SetBranchAddress("Event",&Cube::gEvent);
    Cube::gCubeReconEntryNumber = 0;

    this->setupTree("test3");

    std::cout<<"total number of events : "<<gCubeReconTree->GetEntries()<<std::endl;
    for (Int_t i = 0; i< gCubeReconTree->GetEntries(); i++){

	std::cout<<"event start number -------------------------------------- "<< i <<std::endl;
    	//gCubeReconTree->GetEntry(Cube::gCubeReconEntryNumber);
        gCubeReconTree->GetEntry(i);

        Cube::Handle<Cube::AlgorithmResult> topResult(Cube::gEvent,false);
        std::cout << "resulted foraged . "<<std::endl;

        std::vector<std::string> existingEntries;
        std::string baseName;

        //for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
        //         = Cube::gEvent->G4Trajectories.begin();
        //     g4Trajectory != Cube::gEvent->G4Trajectories.end();
        //     ++g4Trajectory) {
        //    Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
            //std::cout << gt->GetName() << " .. first :  " << g4Trajectory->first
            //      <<" PDG :  "<<gt->GetPDGCode()<<"  "
            //      << " (" << gt->GetInitialMomentum().E() << " MeV)" << std::endl;
	//}

        FillEntries(existingEntries,baseName,topResult);

	eventCounter++;

        for (std::vector<std::string>::iterator e = existingEntries.begin();
            e != existingEntries.end(); ++e) {
            std::cout << "list entry " << *e << std::endl;
        }
	std::cout<<"event end number -------------------------------------- "<< i <<std::endl;
	std::cout<<"--------------------------------------------------------------"<<std::endl;
    }
    htree->Print();
    htree->Write();
    htree->Delete();
}

void Cube::TEventAnalysis::FillEntries(
    std::vector<std::string>& entries,
    std::string baseName,
    Cube::Handle<Cube::AlgorithmResult> current) {

    int index = 0;
    std::vector<Cube::TEventAnalysis::infoList> allResultList;

    baseName += std::string(current->GetName()) + "/";

    //std::cout<<"::::::::::::::::::: trajectories ::::::::::::::::::::::::"<<std::endl;
    //for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
    //         = Cube::gEvent->G4Trajectories.begin();
    //     g4Trajectory != Cube::gEvent->G4Trajectories.end();
    //     ++g4Trajectory) {
    //    Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
	//std::cout << gt->GetName() << " .. first :  " << g4Trajectory->first
	//      <<" PDG :  "<<gt->GetPDGCode()<<"  "
        //      << " (" << gt->GetInitialMomentum().E() << " MeV)" << std::endl;
    //}    
/*
    for (Cube::Event::G4HitContainer::iterator g4Hit
             = Cube::gEvent->G4Hits.begin();
         g4Hit != Cube::gEvent->G4Hits.end();
         ++g4Hit) {
        Cube::Handle<Cube::G4Hit> gh = g4Hit->second;
    }
*/
    for (Cube::AlgorithmResult::ReconObjects::reverse_iterator o
             = current->GetObjectContainers().rbegin();
         o != current->GetObjectContainers().rend(); ++o) {
        Cube::Handle<Cube::ReconObjectContainer> objects
            = gEvent->GetObjectContainer((*o)->GetName());
	
	allResultList = ShowReconObjects(objects, allResultList, index);
	//std::cout<<" ---------------------------------- testing cluster list result 0 "<<std::endl;

        for(int loop=0;loop<allResultList.size();loop++){

    	    reco_x = allResultList[loop].x;
    	    reco_y = allResultList[loop].y;
    	    reco_z = allResultList[loop].z;
	    
    	    reco_t = allResultList[loop].t;
    	    reco_px = allResultList[loop].px;
    	    reco_py = allResultList[loop].py;
    	    reco_pz = allResultList[loop].pz;
    	    reco_e = allResultList[loop].e;
    	    reco_l = allResultList[loop].l;
	    
    	    true_x = allResultList[loop].xt;
    	    true_y = allResultList[loop].yt;
     	    true_z = allResultList[loop].zt;
    	    true_t = allResultList[loop].tt;
    	    true_px = allResultList[loop].pxt;
    	    true_py = allResultList[loop].pyt;
    	    true_pz = allResultList[loop].pzt;
    	    true_e = allResultList[loop].et;
    	    true_l = allResultList[loop].lt;
    	    true_pdg = allResultList[loop].pdg;
	    
	    event_number = eventCounter;
	    this->fillTree();
	}    

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

std::vector<Cube::TEventAnalysis::infoList> Cube::TEventAnalysis::ShowReconObjects(
    Cube::Handle<Cube::ReconObjectContainer> objects, std::vector<Cube::TEventAnalysis::infoList> allList, int index ) {

    for (Cube::ReconObjectContainer::iterator obj = objects->begin();
        obj != objects->end(); ++obj) {
	//std::cout<<"showing the object ! "<<std::endl;
    	Cube::Handle<Cube::ReconTrack> track = (*obj);
	Cube::TEventAnalysis::infoList tracklist;
	tracklist = ShowReconTrack(track, index);
	allList.push_back(tracklist);
	//std::cout<<":::::::::::::: index for the track : "<<index<<" "<<tracklist.pdg<<std::endl;

	Cube::Handle<Cube::ReconCluster> cluster = (*obj);
	Cube::TEventAnalysis::infoList clusterlist;
	clusterlist = ShowReconCluster(cluster, index);
	allList.push_back(clusterlist);
	//std::cout<<":::::::::::::: index for the cluster : "<<index<<" "<<clusterlist.x<<std::endl;
	//allResultList.assign(1, clusterResultList);

	//std::cout<<"----------------------- check size "<<allResultList.size()<<std::endl;
	//Cube::Handle<Cube::ReiconShower> shower = (*obj);
        //index = ShowReconShower(shower, index);
	//std::cout<<":::::::::::::: index for the shower : "<<index<<std::endl;
    }
    
    return allList;
}	

Cube::TEventAnalysis::infoList Cube::TEventAnalysis::ShowReconTrack(
    Cube::Handle<Cube::ReconTrack> obj,
    int index) {

    Cube::TEventAnalysis::infoList tracklist ;
    if (!obj) return tracklist;

    for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
             = Cube::gEvent->G4Trajectories.begin();
         g4Trajectory != Cube::gEvent->G4Trajectories.end();
         ++g4Trajectory) {
	if(g4Trajectory->first == Cube::Tool::MainTrajectory(*gEvent, *obj)){
            Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
            std::cout << "matched . " << " .. first :  " << g4Trajectory->first
                  <<" PDG :  "<<gt->GetPDGCode()<<"  "
                  << " (" << gt->GetInitialMomentum().E() << " MeV)" << std::endl;

            tracklist.xt = gt->GetInitialPosition().X();
            tracklist.yt = gt->GetInitialPosition().Y();
            tracklist.zt = gt->GetInitialPosition().Z();
            tracklist.tt = gt->GetInitialPosition().T();
            tracklist.et = gt->GetInitialMomentum().E();
            tracklist.pxt = gt->GetInitialMomentum().Px();
            tracklist.pyt = gt->GetInitialMomentum().Py();
            tracklist.pzt = gt->GetInitialMomentum().Pz();
            tracklist.pdg = gt->GetPDGCode();
	   /* 
    	    outstream << "22223333"<<" "<<gt->GetPDGCode()<<" "<<gt->GetInitialMomentum().E()<<" "
                  << gt->GetInitialMomentum().Px()<<" "<< gt->GetInitialMomentum().Py() <<" "
                  << gt->GetInitialMomentum().Pz()<<" "<< gt->GetInitialPosition().X() <<" "
                  << gt->GetInitialPosition().Y() <<" " <<gt->GetInitialPosition().Z() <<" "
		  << gt->GetInitialPosition().T() << std::endl;
	   */	  
	}
    }    

    Cube::Handle<Cube::TrackState> frontState = obj->GetState();
    if (!frontState) {
        std::cout << "TrackState is missing!" << std::endl;
	return tracklist;
    }

    ++index;

    std::cout<<"let's output things.. track. "<<std::endl;
    std::unique_ptr<TReconTrackElement> eveTrack(
        new TReconTrackElement(*obj));
    std::vector<double> trackRecoList;
    trackRecoList = eveTrack->getInfoList();
    tracklist.x = trackRecoList[0];
    tracklist.y = trackRecoList[1];
    tracklist.z = trackRecoList[2];
    tracklist.t = trackRecoList[3];
    tracklist.px = trackRecoList[4];
    tracklist.py = trackRecoList[5];
    tracklist.pz = trackRecoList[6];
    tracklist.e = trackRecoList[7];
    tracklist.l = trackRecoList[8];

    return tracklist;	
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

Cube::TEventAnalysis::infoList Cube::TEventAnalysis::ShowReconCluster(
    Cube::Handle<Cube::ReconCluster> obj, int index ) {

    Cube::TEventAnalysis::infoList clusterlist ;

    if (!obj) return clusterlist;

    //std::ofstream outstream;
    //outstream.open ("testResult.txt", std::ofstream::out | std::ofstream::app);

    for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
             = Cube::gEvent->G4Trajectories.begin();
         g4Trajectory != Cube::gEvent->G4Trajectories.end();
         ++g4Trajectory) {
        if(g4Trajectory->first == Cube::Tool::MainTrajectory(*gEvent, *obj)){
            Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
            //std::cout << "matched . " << " .. first :  " << g4Trajectory->first
            //      <<" PDG :  "<<gt->GetPDGCode()<<"  "
            //      << " (" << gt->GetInitialMomentum().E() << " MeV)" << std::endl;
	    clusterlist.xt = gt->GetInitialPosition().X();
            clusterlist.yt = gt->GetInitialPosition().Y();
            clusterlist.zt = gt->GetInitialPosition().Z();
            clusterlist.tt = gt->GetInitialPosition().T();
            clusterlist.et = gt->GetInitialMomentum().E();
            clusterlist.pxt = gt->GetInitialMomentum().Px();
            clusterlist.pyt = gt->GetInitialMomentum().Py();
            clusterlist.pzt = gt->GetInitialMomentum().Pz();	  
            clusterlist.pdg = gt->GetPDGCode();  

	    //outstream << "55556666"<<" "<<gt->GetPDGCode()<<" "<<gt->GetInitialMomentum().E()<<" "
            //      << gt->GetInitialMomentum().Px()<<" "<< gt->GetInitialMomentum().Py() <<" "
            //      << gt->GetInitialMomentum().Pz()<<" "<< gt->GetInitialPosition().X() <<" "
            //      << gt->GetInitialPosition().Y() <<" " <<gt->GetInitialPosition().Z()<<" "
	    //	    << gt->GetInitialPosition().T() << std::endl;
        }
    }

    Cube::Handle<Cube::ClusterState> frontState = obj->GetState();
    if (!frontState) {
        std::cout << "ClusterState is missing!" << std::endl;
        return clusterlist;
    }

    ++index;
    std::cout<<"let's output things.. cluster. "<<std::endl;    
    Cube::TReconClusterElement *eveCluster
        = new Cube::TReconClusterElement(*obj);
    std::vector<double> clusterRecoList;
    clusterRecoList = eveCluster->getInfoList();
    clusterlist.x = clusterRecoList[0];
    clusterlist.y = clusterRecoList[1];
    clusterlist.z = clusterRecoList[2];
    clusterlist.t = clusterRecoList[3];
    clusterlist.e = clusterRecoList[4];
    //std::cout<<"----------------------- test "<<clusterRecoList[0]<<std::endl;

    return clusterlist;
}


Cube::TEventAnalysis::~TEventAnalysis() {
    std::cout << "Event analysis deconstructed" << std::endl;
}

// Local Variables:
// mode:c++
// c-basic-offset:4
// compile-command:"$(git rev-parse --show-toplevel)/build/cube-build.sh force"
// End:
