#include "TReconShowerElement.hxx"

#include <CubeUnits.hxx>
#include <CubeHandle.hxx>
#include <TUnitsTable.hxx>

#include <CubeReconShower.hxx>
#include <CubeReconNode.hxx>
#include <CubeReconCluster.hxx>
#include <CubeShowerState.hxx>
#include <CubeHandle.hxx>

#include <TEveLine.h>

#include <sstream>


Cube::TReconShowerElement::~TReconShowerElement() {}

Cube::TReconShowerElement::TReconShowerElement(Cube::ReconShower& shower)
{
   
    std::cout<<"doing TReconShowerElement . "<<std::endl;	
    Cube::Handle<Cube::ShowerState> frontState = shower.GetState();
    if (!frontState) {
        CUBE_ERROR << "ShowerState missing!" << std::endl;
        fValid = false;
        return;
    }

#define USE_BACKSTATE
#ifdef USE_BACKSTATE
    Cube::Handle<Cube::ShowerState> backState
        = shower.GetNodes().back()->GetState();
#endif

    // The unit length for drawing the line directions.  The direction vectors
    // are this long.
    const double dirLineLen = 7.0*unit::mm;

    //////////////////////////////////////////////////////////
    // Generate the title for the shower.
    //////////////////////////////////////////////////////////
    

        TLorentzVector pos = frontState->GetPosition();
        TLorentzVector var = frontState->GetPositionVariance();
        TVector3 dir = frontState->GetDirection().Unit();
        TVector3 dvar = frontState->GetDirectionVariance();

        double length = GetLength(shower);
        double dEdX = 0.0;
        if (length > 0) {
            dEdX = shower.GetEDeposit()/length;
        }
	std::cout << "Shower(" << shower.GetUniqueID() << ") --"
              << " Nodes: " << shower.GetNodes().size()
              << " Hits: " << shower.GetHitSelection()->size()
              << " Length: " << unit::AsString(length,"length")
              << std::endl
              << "   Energy Deposit: "
              << unit::AsString(shower.GetEDeposit(),"pe")
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
              << ")";

	std::cout << std::endl
              << "   Algorithm: " << shower.GetAlgorithmName()
              << " w/ goodness: " << shower.GetQuality()
              << " / " << shower.GetNDOF();
        
}

double Cube::TReconShowerElement::GetLength(Cube::ReconShower& shower) const {
    double length = 0.0;
    Cube::ReconNodeContainer::iterator n = shower.GetNodes().begin();
    Cube::Handle<Cube::ShowerState> lastState = (*(n++))->GetState();
    while (n != shower.GetNodes().end()) {
        Cube::Handle<Cube::ShowerState> nodeState = (*(n++))->GetState();
        length += (nodeState->GetPosition().Vect()
                   - lastState->GetPosition().Vect()).Mag();
        lastState = nodeState;
    }
    return length;
}


