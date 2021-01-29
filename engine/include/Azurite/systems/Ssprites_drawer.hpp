#ifndef __AZURITE__BUILT_IN_SYSTEMS_SPRITES_DRAWER
#define __AZURITE__BUILT_IN_SYSTEMS_SPRITES_DRAWER

#include "Azurite/Game.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"

namespace Azurite {

    /*
    ** Core system that draw the entities with BOTH a SPRITE and a TRANSFORM2D
    ** Using the current displayModule
    */

    void Ssprites_drawer(Game &game);
}

#endif
