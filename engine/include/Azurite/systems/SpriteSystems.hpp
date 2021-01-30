#ifndef __AZURITE__BUILT_IN_SPRITE_SYSTEMS
#define __AZURITE__BUILT_IN_SPRITE_SYSTEMS

#include "Azurite/Game.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CAnimatedSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"

namespace Azurite {

    /*
    ** Core system that draw the entities with BOTH a SPRITE/ANIMATED_SPRITE and a TRANSFORM2D
    ** Using the current displayModule
    */

    void Ssprites_drawer(Game &game);

    /*
    ** System that update the datas of ANIMATED_SPRITE components
    */

    void Sanimated_sprite_updater(CAnimatedSprite &asprite);
}

#endif
