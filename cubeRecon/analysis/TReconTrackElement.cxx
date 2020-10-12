#include "TReconTrackElement.hxx"

#include <CubeUnits.hxx>
#include <CubeHandle.hxx>
#include <TUnitsTable.hxx>

#include <CubeReconTrack.hxx>
#include <CubeReconNode.hxx>
#include <CubeReconCluster.hxx>
#include <CubeTrackState.hxx>
#include <CubeHandle.hxx>

#include <TEveLine.h>

#include <sstream>
#include <fstream>

Cube::TReconTrackElement::~TReconTrackElement() {}

Cube::TReconTrackElement::TReconTrackElement(Cube::ReconTrack& track)
{
    std::ofstream outstream;
    outstream.open ("testResult.txt", std::ofstream::out | std::ofstream::app);

    std::cout<<"doing TReconTrackElement . "<<std::endl;	
    Cube::Handle<Cube::TrackState> frontState = track.GetState();
    if (!frontState) {
        CUBE_ERROR << "TrackState missing!" << std::endl;
        fValid = false;
        return;
    }

#define USE_BACKSTATE
#ifdef USE_BACKSTATE
    Cube::Handle<Cube::TrackState> backState
        = track.GetNodes().back()->GetState();
#endif

    // The unit length for drawing the line directions.  The direction vectors
    // are this long.
    const double dirLineLen = 7.0*unit::mm;

    //////////////////////////////////////////////////////////
    // Generate the title for the track.
    //////////////////////////////////////////////////////////
    

        TLorentzVector pos = frontState->GetPosition();
        TLorentzVector var = frontState->GetPositionVariance();
        TVector3 dir = frontState->GetDirection().Unit();
        TVector3 dvar = frontState->GetDirectionVariance();

        double length = GetLength(track);
        double dEdX = 0.0;
        if (length > 0) {
            dEdX = track.GetEDeposit()/length;
        }
	std::cout << "Track(" << track.GetUniqueID() << ") --"
              << " Nodes: " << track.GetNodes().size()
              << " Hits: " << track.GetHitSelection()->size()
              << " Length: " << unit::AsString(length,"length")
              << std::endl
              << "   Energy Deposit: "
              << unit::AsString(track.GetEDeposit(),"pe")
              << ", dEdX: " << unit::AsString(dEdX,"pe") << "/mm"
              << std::endl
              << "   Position:  ("
              << unit::AsString(pos.X(),std::sqrt(var.X()),"length")
              << ", "<<unit::AsString(pos.Y(),std::sqrt(var.Y()),"length")
              << ", "<<unit::AsString(pos.Z(),std::sqrt(var.Z()),"length")
              << ")" <<std::endl;

	std::cout << std::endl
              << "   Direction: ("
              << unit::AsString(dir.X(), dvar.X(),"direction")
              << ", " << unit::AsString(dir.Y(), dvar.Y(),"direction")
              << ", " << unit::AsString(dir.Z(), dvar.Z(),"direction")
              << ")" << std::endl;

	std::cout << std::endl
              << "   Algorithm: " << track.GetAlgorithmName()
              << " w/ goodness: " << track.GetQuality()
              << " / " << track.GetNDOF();
 
 	outstream<<track.GetNodes().size()<<" "<<track.GetHitSelection()->size()
	         <<" "<<length
	         <<" "<<dEdX
		 <<" "<<pos.X()
		 <<" "<<pos.Y()
		 <<" "<<pos.Z()
		 <<" "<<dir.X()
		 <<" "<<dir.Y()
		 <<" "<<dir.Z() <<std::endl;
}

double Cube::TReconTrackElement::GetLength(Cube::ReconTrack& track) const {
    double length = 0.0;
    Cube::ReconNodeContainer::iterator n = track.GetNodes().begin();
    Cube::Handle<Cube::TrackState> lastState = (*(n++))->GetState();
    while (n != track.GetNodes().end()) {
        Cube::Handle<Cube::TrackState> nodeState = (*(n++))->GetState();
        length += (nodeState->GetPosition().Vect()
                   - lastState->GetPosition().Vect()).Mag();
        lastState = nodeState;
    }
    return length;
}


