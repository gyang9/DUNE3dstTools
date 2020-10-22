#ifndef TTrajectoryHandler_hxx_seen
#define TTrajectoryHandler_hxx_seen

#include "TEventAnalysis.hxx"

namespace Cube {
    class TTrajectoryHandler;
}

class TEveElementList;

/// Handle drawing the trajectories.
class Cube::TTrajectoryHandler: public TEventAnalysis {
public:
    TTrajectoryHandler();
    ~TTrajectoryHandler();

private:

    /// The trajectories to draw in the event.
    TEveElementList* fTrajectoryList;

};

#endif

