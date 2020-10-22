#include "TReconClusterElement.hxx"

#include <CubeUnits.hxx>
#include <CubeHandle.hxx>
#include <TUnitsTable.hxx>

#include <CubeReconCluster.hxx>
#include <CubeReconNode.hxx>
#include <CubeReconCluster.hxx>
#include <CubeClusterState.hxx>
#include <CubeHandle.hxx>

#include <TEveLine.h>

#include <sstream>
#include <fstream>

Cube::TReconClusterElement::~TReconClusterElement() {}

Cube::TReconClusterElement::TReconClusterElement(Cube::ReconCluster& cluster)
{

    double minEnergy = 10.0;
    double maxEnergy = 200.0;

    Cube::Handle<Cube::ClusterState> state = cluster.GetState();
    TLorentzVector var = state->GetPositionVariance();
    TLorentzVector pos = state->GetPosition();


	std::cout << "Cluster(" << cluster.GetUniqueID() << ") @ "
                  << unit::AsString(pos.X(),std::sqrt(var.X()),"length")
                  << ", "
                  << unit::AsString(pos.Y(),std::sqrt(var.Y()),"length")
                  << ", "
                  << unit::AsString(pos.Z(),std::sqrt(var.Z()),"length")
                  << std::endl;

        std::cout << "  Time "
                  << unit::AsString(pos.T(),std::sqrt(var.T()),"time")
                  << "  Charge "
                  << unit::AsString(cluster.GetEDeposit(),"pe")
                  << std::endl;
/*
        outstream<<"77778888"
                 <<" "<<pos.X()
                 <<" "<<pos.Y()
                 <<" "<<pos.Z()
		 <<" "<<pos.T()
                 <<" "<<cluster.GetEDeposit() <<std::endl;
*/
    fInfoList.push_back(pos.X());	
    fInfoList.push_back(pos.Y());
    fInfoList.push_back(pos.Z());
    fInfoList.push_back(pos.T());
    fInfoList.push_back(cluster.GetEDeposit());
}


double Cube::TReconClusterElement::GetLength(Cube::ReconCluster& cluster) const {
    double length = 0.0;
    Cube::ReconNodeContainer::iterator n = cluster.GetNodes().begin();
    Cube::Handle<Cube::ClusterState> lastState = (*(n++))->GetState();
    while (n != cluster.GetNodes().end()) {
        Cube::Handle<Cube::ClusterState> nodeState = (*(n++))->GetState();
        length += (nodeState->GetPosition().Vect()
                   - lastState->GetPosition().Vect()).Mag();
        lastState = nodeState;
    }
    return length;
}


