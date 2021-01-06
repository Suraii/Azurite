#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#define __AZURITE__INNER__SYSTEMS_MANAGER

namespace Azurite {

    class Game;

    class SystemsManager {
        Game &m_owner;
        SystemsManager(Game &owner);
        ~SystemsManager();
    };
};

#endif

/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif
