#ifndef TReconClusterElement_hxx_seen
#define TReconClusterElement_hxx_seen

#include <CubeReconCluster.hxx>

#include <TEveElement.h>

namespace Cube {
    class TReconClusterElement;
};


/// A Eve Element object to represent a Cube::ReconCluster.
class Cube::TReconClusterElement {
public:
    TReconClusterElement(Cube::ReconCluster& track);
    virtual ~TReconClusterElement();

    std::vector<double> getInfoList() {return fInfoList;}
    bool Valid() {return fValid;}
    std::vector<double> fInfoList;

private:
    // Count up the track length from the nodes.
    double GetLength(Cube::ReconCluster& track) const;

    bool fValid;
};
#endif

