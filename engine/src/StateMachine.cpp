#include "StateMachine.hpp"

using namespace Azurite;

/*
** STATEMACHINE IMPLEMENTATION
*/

StateMachine::StateMachine(Game &owner) : m_owner(owner) {}

StateMachine::~StateMachine() {}

void StateMachine::update() {}

void StateMachine::setState(std::unique_ptr<AState>) {}

void StateMachine::stackState(std::unique_ptr<AState>) {}

void StateMachine::leaveCurrentState() {}

std::optional<std::reference_wrapper<AState>> StateMachine::getCurrentState() const
{
    return {};
}


/*
** ASTATE IMPLEMENTATION
*/

AState::AState() : m_id(0) {}

AState::~AState() {}

unsigned AState::getId() const
{
    return 0;
}

void AState::sendEvent(const Event event) {}
