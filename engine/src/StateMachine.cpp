#include "StateMachine.hpp"

using namespace Azurite;

/*
** STATEMACHINE IMPLEMENTATION
*/

StateMachine::StateMachine(Game &owner) : m_owner(owner) {}

StateMachine::~StateMachine()
{
}

void StateMachine::update()
{
}

void StateMachine::setState(std::unique_ptr<AState>)
{
}

void StateMachine::stackState(std::unique_ptr<AState> state)
{
}

void StateMachine::leaveCurrentState() {}

std::optional<std::reference_wrapper<AState>> StateMachine::getCurrentState() const
{
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
