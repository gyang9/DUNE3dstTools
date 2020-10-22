#ifndef TG4HitHandler_hxx_seen
#define TG4HitHandler_hxx_seen

#include "TVEventChangeHandler.hxx"

namespace Cube {
    class TG4HitHandler;
}

class TEveElementList;

/// Handle drawing the GEANT4 (truth) hits.
class Cube::TG4HitHandler: public TVEventChangeHandler {
public:
    TG4HitHandler();
    ~TG4HitHandler();

    /// Draw the trajectories into the current scene.
   virtual void Apply();

private:

    /// The GEANT4 hits to draw in the event.
    TEveElementList* fG4HitList;

};

#endif

