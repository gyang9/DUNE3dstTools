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

	for (int loop = 0; loop<1000; loop++){
	    reco_x[loop] = -1; 
            reco_y[loop] = -1;
            reco_z[loop] = -1;

            reco_t[loop] = -1;
            reco_px[loop] = -1;
            reco_py[loop] = -1;
            reco_pz[loop] = -1;
            reco_e[loop] = -1;
            reco_l[loop] = -1;

            reco_x_back[loop] = -1;
            reco_y_back[loop] = -1;
            reco_z_back[loop] = -1;
            reco_t_back[loop] = -1;
            reco_px_back[loop] = -1;
            reco_py_back[loop] = -1;
            reco_pz_back[loop] = -1;

            true_x[loop] = -1;
            true_y[loop] = -1;
            true_z[loop] = -1;
            true_t[loop] = -1;
            true_px[loop] = -1;
            true_py[loop] = -1;
            true_pz[loop] = -1;
            true_e[loop] = -1;
            true_l[loop] = -1;
            true_pdg[loop] = -1;
	    true_parentPdg[loop] = -1;
	    traj_pdg[loop] = -1;
	    traj_e[loop] = -1;
	    traj_px[loop] = -1;
	    traj_py[loop] = -1;
	    traj_pz[loop] = -1;
	    traj_x[loop] = -1;
            traj_y[loop] = -1;
            traj_z[loop] = -1;
	    traj_t[loop] = -1;
	    traj_id[loop] = -1;
	    traj_parentId[loop] = -1;
	    true_id[loop] = -1;
	    true_parentId[loop] = -1;
	}

	int loopp=0;
	double record_x = 0; double record_y =0; double record_z =0; int record_pdg = 0;
        for(int loop=0;loop<allResultList.size();loop++){
	    if(loopp < 999 ){
		if(loop>0 && (allResultList[loop].x == record_x && allResultList[loop].y == record_y && allResultList[loop].z == record_z && allResultList[loop].pdg == record_pdg) )
		    continue;
    	        reco_x[loopp] = allResultList[loop].x;
    	        reco_y[loopp] = allResultList[loop].y;
    	        reco_z[loopp] = allResultList[loop].z;
	    
    	    	reco_t[loopp] = allResultList[loop].t;
    	    	reco_px[loopp] = allResultList[loop].px;
    	    	reco_py[loopp] = allResultList[loop].py;
    	    	reco_pz[loopp] = allResultList[loop].pz;
    	    	reco_e[loopp] = allResultList[loop].e;
    	    	reco_l[loopp] = allResultList[loop].l;
	   
                reco_x_back[loopp] = allResultList[loop].x_back;
                reco_y_back[loopp] = allResultList[loop].y_back;
                reco_z_back[loopp] = allResultList[loop].z_back;
                reco_t_back[loopp] = allResultList[loop].t_back;
                reco_px_back[loopp] = allResultList[loop].px_back;
                reco_py_back[loopp] = allResultList[loop].py_back;
                reco_pz_back[loopp] = allResultList[loop].pz_back;

    	    	true_x[loopp] = allResultList[loop].xt;
    	    	true_y[loopp] = allResultList[loop].yt;
     	    	true_z[loopp] = allResultList[loop].zt;
    	    	true_t[loopp] = allResultList[loop].tt;
    	    	true_px[loopp] = allResultList[loop].pxt;
    	    	true_py[loopp] = allResultList[loop].pyt;
    	    	true_pz[loopp] = allResultList[loop].pzt;
    	    	true_e[loopp] = allResultList[loop].et;
    	    	true_l[loopp] = allResultList[loop].lt;
    	    	true_pdg[loopp] = allResultList[loop].pdg;
		true_parentPdg[loopp] = allResultList[loop].parentPdg;
		true_id[loopp] = allResultList[loop].id;
		true_parentId[loopp] = allResultList[loop].parentId;
		record_x = allResultList[loop].x;
		record_y = allResultList[loop].y;
		record_z = allResultList[loop].z;
		record_pdg = allResultList[loop].pdg;
		loopp++;
	    }
	}  

	int trajloop = 0;
        for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
                 = Cube::gEvent->G4Trajectories.begin();
             g4Trajectory != Cube::gEvent->G4Trajectories.end();
             ++g4Trajectory) {
	    Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
	    traj_pdg[trajloop] = gt->GetPDGCode();
	    traj_id[trajloop] = gt->GetTrackId();
	    traj_parentId[trajloop] = gt->GetParentId();
            traj_e[trajloop] = gt->GetInitialMomentum().E();
            traj_px[trajloop] = gt->GetInitialMomentum().Px();
            traj_py[trajloop] = gt->GetInitialMomentum().Py();
            traj_pz[trajloop] = gt->GetInitialMomentum().Pz();
	    traj_x[trajloop] = gt->GetInitialPosition().X();
            traj_y[trajloop] = gt->GetInitialPosition().Y();
            traj_z[trajloop] = gt->GetInitialPosition().Z();
	    traj_t[trajloop] = gt->GetInitialPosition().T();
	    trajloop++;
	}

	allResultList.clear();
        event_number = eventCounter;	
	htree->Fill();
	//this->fillTree();

	//entries.push_back(baseName + (*o)->GetName());
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

    int tempID = -999;
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
            tracklist.id = gt->GetTrackId();
            tracklist.parentId = gt->GetParentId();	    

	    tempID = gt->GetParentId();
	   /* 
    	    outstream << "22223333"<<" "<<gt->GetPDGCode()<<" "<<gt->GetInitialMomentum().E()<<" "
                  << gt->GetInitialMomentum().Px()<<" "<< gt->GetInitialMomentum().Py() <<" "
                  << gt->GetInitialMomentum().Pz()<<" "<< gt->GetInitialPosition().X() <<" "
                  << gt->GetInitialPosition().Y() <<" " <<gt->GetInitialPosition().Z() <<" "
		  << gt->GetInitialPosition().T() << std::endl;
	   */	  
	}
    }   

    for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
             = Cube::gEvent->G4Trajectories.begin();
         g4Trajectory != Cube::gEvent->G4Trajectories.end();
         ++g4Trajectory) {
        if(g4Trajectory->first == tempID){
            Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
	    //std::cout<<"----------------- parent pdg is : "<<gt->GetPDGCode()<<std::endl;
            tracklist.parentPdg = gt->GetPDGCode();
	    break;
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

    tracklist.x_back = trackRecoList[9];
    tracklist.y_back = trackRecoList[10];
    tracklist.z_back = trackRecoList[11];
    tracklist.t_back = trackRecoList[12];
    tracklist.px_back = trackRecoList[13];
    tracklist.py_back = trackRecoList[14];
    tracklist.pz_back = trackRecoList[15];

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

    int tempID = -999;
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
	    clusterlist.id = gt->GetTrackId();
	    clusterlist.parentId = gt->GetParentId();
	    //outstream << "55556666"<<" "<<gt->GetPDGCode()<<" "<<gt->GetInitialMomentum().E()<<" "
            //      << gt->GetInitialMomentum().Px()<<" "<< gt->GetInitialMomentum().Py() <<" "
            //      << gt->GetInitialMomentum().Pz()<<" "<< gt->GetInitialPosition().X() <<" "
            //      << gt->GetInitialPosition().Y() <<" " <<gt->GetInitialPosition().Z()<<" "
	    //	    << gt->GetInitialPosition().T() << std::endl;
        }
    }
    for (Cube::Event::G4TrajectoryContainer::iterator g4Trajectory
             = Cube::gEvent->G4Trajectories.begin();
         g4Trajectory != Cube::gEvent->G4Trajectories.end();
         ++g4Trajectory) {
        if(g4Trajectory->first == tempID){
            //std::cout<<"----------------- parent pdg is : "<<gt->GetPDGCode()<<std::endl;
            Cube::Handle<Cube::G4Trajectory> gt = g4Trajectory->second;
            clusterlist.parentPdg = gt->GetPDGCode();
            break;
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
