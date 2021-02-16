#include "Azurite/StateMachine.hpp"

using namespace Azurite;

/*
** STATEMACHINE IMPLEMENTATION
*/

StateMachine::StateMachine(Game &owner) : m_owner(owner) {}

StateMachine::~StateMachine()
{
    while (getCurrentState())
        leaveCurrentState();
}

void StateMachine::update()
{
    if (getCurrentState())
        getCurrentState()->get().onTick(m_owner);
}

void StateMachine::setState(std::unique_ptr<AState> state)
{
    if (getCurrentState()) {
        getCurrentState()->get().onStop(m_owner);
        m_states.pop();
    }
    m_states.push(std::move(state));
    getCurrentState()->get().onStart(m_owner);
}

void StateMachine::stackState(std::unique_ptr<AState> state)
{
    if (getCurrentState())
        getCurrentState()->get().onPause(m_owner);
    m_states.push(std::move(state));
    getCurrentState()->get().onStart(m_owner);
}

void StateMachine::leaveCurrentState()
{
    if (!getCurrentState())
        return;
    getCurrentState()->get().onStop(m_owner);
    m_states.pop();
    if (getCurrentState())
        getCurrentState()->get().onResume(m_owner);
}

std::optional<std::reference_wrapper<AState>> StateMachine::getCurrentState() const
{
    if (!m_states.empty())
        return *(m_states.top());
    return {};
}


/*
** ASTATE IMPLEMENTATION
*/

unsigned AState::statesCount = 0;

AState::AState() : m_id(AState::statesCount++)
{}

AState::~AState() {}

unsigned AState::getId() const
{
    return m_id;
}

void AState::sendEvent(const Event event)
{
    m_events.push(std::move(event));
}

std::optional<Event> AState::readEvent()
{
    if (m_events.empty())
        return {};
    Event buf = m_events.front();
    m_events.pop();
    return buf;
}
