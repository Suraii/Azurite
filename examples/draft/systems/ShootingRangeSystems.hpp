#pragma once

#include "Azurite/Game.hpp"
#include "components/CTarget.hpp"
#include "Azurite/components/LifeComponents.hpp"
#include "Azurite/components/UIComponents.hpp"

/*
** System that destroy targets when they are clicked
**
*/

void Starget_destructer(CTarget &, Azurite::CButton &, Azurite::CDestructible &);
