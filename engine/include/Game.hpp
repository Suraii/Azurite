/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__STATE_MACHINE
#include "StateMachine.hpp"
#endif

#ifndef __AZURITE__INNER__COMPONENTS_STORAGE
#include "ComponentsStorage.hpp"
#endif

#ifndef __AZURITE__INNER__MODULES
#include "Modules.hpp"
#endif

#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#include "SystemsManager.hpp"
#endif

#ifndef __AZURITE__INNER__GAME
#define __AZURITE__INNER__GAME

namespace Azurite {

    class Game {
    public:
        StateMachine stateMachine;
        ComponentsStorage componentsStorage;
        SystemsManager systemsManager;
        Game();
        ~Game();
    };
}

#endif
