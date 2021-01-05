/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__STATE_MACHINE
#include "StateMachine.hpp"
#endif

#ifndef __AZURITE__INNER__GAME
#define __AZURITE__INNER__GAME

namespace Azurite {
    class Game {
    public:
        StateMachine stateMachine;
        Game();
        ~Game();
    };
}

#endif
