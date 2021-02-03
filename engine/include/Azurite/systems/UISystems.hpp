#ifndef __AZURITE__BUILT_IN_UI_SYSTEMS
#define __AZURITE__BUILT_IN_UI_SYSTEMS

#include "Azurite/Game.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CButton.hpp"
#include "Azurite/components/CCollisionBox.hpp"
#include "Azurite/components/CTransform2D.hpp"

namespace Azurite {

/*
** System that change the sprite of a button depending of its state
*/

void Sbutton_sprite_updater(Azurite::CSprite &sprite, CButton &button);

/*
** System that update the state of a button
*/

void Sbutton_params_updater(Azurite::Game &game);

};

#endif