#ifndef TReconShowerElement_hxx_seen
#define TReconShowerElement_hxx_seen

#include <CubeReconShower.hxx>

#include <TEveElement.h>

namespace Cube {
    class TReconShowerElement;
};


/// A Eve Element object to represent a Cube::ReconShower.
class Cube::TReconShowerElement {
public:
    TReconShowerElement(Cube::ReconShower& track);
    virtual ~TReconShowerElement();

    bool Valid() {return fValid;}

private:
    // Count up the track length from the nodes.
    double GetLength(Cube::ReconShower& track) const;

    bool fValid;
};
#endif

