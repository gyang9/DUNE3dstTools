#include "TEventAnalysis.hxx"
#include "TEventManager.hxx"

#include <CubeEvent.hxx>
#include <CubeG4Hit.hxx>
#include <CubeG4Trajectory.hxx>
#include <CubeAlgorithmResult.hxx>
#include <CubeReconTrack.hxx>
#include <CubeReconCluster.hxx>
#include <CubeHit.hxx>

#include <TFile.h>

#include <TROOT.h>
#include <TSystem.h>
#include <TApplication.h>

#include <getopt.h>

#include <iostream>
#include <memory>


int main(int argc, char **argv) {
    std::string fileName = "";

    // Check if there is an input file on the command line.
    if (argc - optind > 0) {
        fileName = argv[optind];
    }

    TFile* eventSource = NULL;
    if (!fileName.empty()) {
        eventSource = new TFile(fileName.c_str());
    }

    Cube::TEventAnalysis* analysis = new Cube::TEventAnalysis(eventSource);
    //analysis->Init();
    //Cube::gCubeReconTree = (TTree*) eventSource->Get("CubeEvents");

    return 0;

}



