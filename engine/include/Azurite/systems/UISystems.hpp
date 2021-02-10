#ifndef __AZURITE__BUILT_IN_UI_SYSTEMS
#define __AZURITE__BUILT_IN_UI_SYSTEMS

#include "Azurite/Game.hpp"
#include "Azurite/components/UIComponents.hpp"

namespace Azurite {

/*
** System that change the sprite of a button depending of its state
*/

void Sbutton_sprite_updater(Azurite::CSprite &sprite, CButton &button);

/*
** System that update the state of a button
*/

void Sbutton_params_updater(Azurite::Game &game);

/*
** Core System that trigger actions of input actions when needed
*/

void Sinput_action_invoker(Azurite::Game& game);

};

#endif
