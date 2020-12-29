#ifndef __AZURITE__INNER__STATE_MACHINE
#define __AZURITE__INNER__STATE_MACHINE

#include <stack>
#include <queue>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include "Game.hpp"

namespace Azurite {

    class AState;
    struct Event;

    // State Manager Class
    class StateMachine {
        Game &m_owner;
        std::stack<std::reference_wrapper<AState>> m_states;
    private:
    // This method should only be called by the Owner of the state machine
        void update();
    public:
    // This class should only be built by game class
        StateMachine(Game &owner);
        ~StateMachine();
    // Control Methods
        void setState(std::unique_ptr<AState>);
        void stackState(std::unique_ptr<AState>);
        void leaveCurrentState();
        std::optional<std::reference_wrapper<AState>> getCurrentState() const;
    };

    // State abstract parent
    class AState {
        const unsigned m_id;
    protected:
        std::queue<Event> m_events;
    public:
        AState();
        virtual ~AState();
    // Control Methods
        unsigned getId() const;
        void sendEvent(const Event event);
    // State Logic Methods
        virtual void onStart(Game &instance) = 0;
        virtual void onTick(Game &instance) = 0;
        virtual void onPause(Game &instance) = 0;
        virtual void onResume(Game &instance) = 0;
        virtual void onStop(Game &instance) = 0;
    };

    // Struct used to system-state communication
    struct Event {
        std::string name;
    };
}

#endif
