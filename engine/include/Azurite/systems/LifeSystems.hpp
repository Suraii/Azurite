#ifndef __AZURITE__BUILT_IN_LIFE_SYSTEMS
#define __AZURITE__BUILT_IN_LIFE_SYSTEMS

#include "Azurite/Game.hpp"
#include "Azurite/components/LifeComponents.hpp"

namespace Azurite {

    /*
    ** Core system to destroy dead entities
    */

    void Sdestructible_reaper(Game &game);

    /*
    ** Core system that execute death rattles
    */

    void Sdeath_rattle_invoker(Game &game);

    /*
    ** System that tick entities lifetimes and kill them when needed
    */

    void Slifetime_ticker(CLifetime &lifetime, CDestructible &destructible);
}

#endif
