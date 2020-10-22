#ifndef TReconTrackElement_hxx_seen
#define TReconTrackElement_hxx_seen

#include <CubeReconTrack.hxx>

#include <TEveElement.h>

namespace Cube {
    class TReconTrackElement;
};


/// A Eve Element object to represent a Cube::ReconTrack.
class Cube::TReconTrackElement {
public:
    TReconTrackElement(Cube::ReconTrack& track);
    virtual ~TReconTrackElement();

    bool Valid() {return fValid;}

    std::vector<double> getInfoList() {return fInfoList;}
    std::vector<double> fInfoList;


private:
    // Count up the track length from the nodes.
    double GetLength(Cube::ReconTrack& track) const;

    bool fValid;
};
#endif

