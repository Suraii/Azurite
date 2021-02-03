#pragma once

#include "Azurite/Game.hpp"
#include "components/CTarget.hpp"
#include "Azurite/components/CButton.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"
#include "Azurite/components/CCollisionBox.hpp"
#include "Azurite/components/CDestructible.hpp"

/*
** System that destroy targets when they are clicked
**
*/

void Starget_destructer(CTarget &, Azurite::CButton &, Azurite::CDestructible &);
