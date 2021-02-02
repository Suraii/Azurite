#pragma once

#include "Azurite/Game.hpp"
#include "components/CButton.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"
#include "Azurite/components/CCollisionBox.hpp"

/*
** System that update the visual of Entities with both a Sprite & a Button
*/

void Sbutton_sprite_updater(Azurite::CSprite &sprite, CButton &button);


/*
** Core system that update the parameters of Button components from the InputModule
** and trigger their actions when needed (Transform & CollisionBox required)
*/

void Sbutton_params_updater(Azurite::Game &game);
