#ifndef TG4HitChangeHandler_hxx_seen
#define TG4HitChangeHandler_hxx_seen

#include "TVEventChangeHandler.hxx"

namespace Cube {
    class TG4HitChangeHandler;
}

class TEveElementList;

/// Handle drawing the GEANT4 (truth) hits.
class Cube::TG4HitChangeHandler: public TVEventChangeHandler {
public:
    TG4HitChangeHandler();
    ~TG4HitChangeHandler();

    /// Draw the trajectories into the current scene.
   virtual void Apply();

private:

    /// The GEANT4 hits to draw in the event.
    TEveElementList* fG4HitList;

};

#endif
