#ifndef __AZURITE__BUILT_IN_COMPONENTS_DEATH_RATTLE
#define __AZURITE__BUILT_IN_COMPONENTS_DEATH_RATTLE

#include <functional>
#include "Azurite/Game.hpp"

namespace Azurite {

struct CDeathRattle {
    std::function<void(Azurite::Game &)> action = [](Azurite::Game &){};
};

};

#endif
