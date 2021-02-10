#ifndef __AZURITE__BUILT_IN_MOVEMENT_SYSTEMS
#define __AZURITE__BUILT_IN_MOVEMENT_SYSTEMS

#include "Azurite/Game.hpp"
#include "Azurite/components/MovementComponents.hpp"

namespace Azurite {

    /*
    ** System that update the location entities according to their velocity
    */

    void Svelocity_applier(CTransform2D &transform, CVelocity &velocity);

}

#endif
