#define BOOST_TEST_MODULE Engine Core Tests

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "Game.hpp"
#include "StateMachine.hpp"

using namespace Azurite;

/*
** ASTATE TESTS
*/

class DummyState : public AState {
public:
    std::string getEvent() {
        std::string buf = m_events.front().name;
        m_events.pop();
        return buf;
    }
    void onStart(__attribute__((unused)) Game &instance) {}
    void onTick(__attribute__((unused)) Game &instance)  {}
    void onPause(__attribute__((unused)) Game &instance) {}
    void onResume(__attribute__((unused)) Game &instance) {}
    void onStop(__attribute__((unused)) Game &instance) {}
};

BOOST_AUTO_TEST_CASE(states_ids)
{
    DummyState states[3] = {DummyState(), DummyState(), DummyState()};

    for (unsigned i = 0; i < 3; i++)
        BOOST_CHECK_MESSAGE(states[i].getId() == i,
    "Error in state id, expected " << i << " got " << states[i].getId());
}

BOOST_AUTO_TEST_CASE(states_events)
{
    DummyState state;
    std::string words[4] = {"It's", "free", "real", "estate"};

    for (unsigned i = 0; i < 4; i++)
        state.sendEvent(Event{words[i]});
    for (unsigned i = 0; i < 4; i++) {
        std::string word = state.getEvent();
        BOOST_CHECK_MESSAGE(word == words[i],
    "Error in events queue, expected " << words[i] << " got " << word);
    }
}

/*
** STATEMACHINE TESTS
*/

enum class StateState { // Damn, things are getting meta again
    Inactive,
    Started,
    Updated,
    Paused,
    Resumed,
    Stopped,
};

class MonitoringState : public AState {
public:
    StateState &state;
    MonitoringState(StateState &_state) : AState(), state(_state) {}
    void onStart(__attribute__((unused)) Game &instance) { state = StateState::Started; }
    void onTick(__attribute__((unused)) Game &instance)  { state = StateState::Updated; }
    void onPause(__attribute__((unused)) Game &instance) { state = StateState::Paused; }
    void onResume(__attribute__((unused)) Game &instance) { state = StateState::Resumed; }
    void onStop(__attribute__((unused)) Game &instance) { state = StateState::Stopped; }
};

BOOST_AUTO_TEST_CASE(state_machine_start_and_stop)
{
    Game game;
    StateMachine machine(game);
    StateState stateState = StateState::Inactive;
    MonitoringState state(stateState);

    machine.stackState(std::make_unique<MonitoringState>(state));
    BOOST_CHECK_MESSAGE(stateState == StateState::Started,
    "State hasn't bein started properly when stacked");
    machine.leaveCurrentState();
    BOOST_CHECK_MESSAGE(stateState == StateState::Stopped,
    "State hasn't bein stopped properly when left");
}

BOOST_AUTO_TEST_CASE(state_machine_pause_and_resume)
{
    Game game;
    StateMachine machine(game);
    StateState stateStates[2] = {StateState::Inactive, StateState::Inactive};
    MonitoringState states[2] = {MonitoringState(stateStates[0]), MonitoringState(stateStates[1])};

    machine.stackState(std::make_unique<MonitoringState>(states[0]));
    machine.stackState(std::make_unique<MonitoringState>(states[1]));
    BOOST_CHECK_MESSAGE(stateStates[0] == StateState::Paused,
    "State hasn't bein paused properly when overstacked");
    machine.leaveCurrentState();
    BOOST_CHECK_MESSAGE(stateStates[0] == StateState::Resumed,
    "State hasn't bein resumed properly when taken back to the top");
}

BOOST_AUTO_TEST_CASE(state_machine_ticking)
{
    Game game;
    StateMachine machine(game);
    StateState stateStates[2] = {StateState::Inactive, StateState::Inactive};
    MonitoringState states[2] = {MonitoringState(stateStates[0]), MonitoringState(stateStates[1])};

    machine.stackState(std::make_unique<MonitoringState>(states[0]));
    machine.stackState(std::make_unique<MonitoringState>(states[1]));
    machine.update();
    BOOST_CHECK_MESSAGE(stateStates[0] == StateState::Paused,
    "Non-current state has ticked on update (OR the state isn't paused properly)");
    BOOST_CHECK_MESSAGE(stateStates[1] == StateState::Updated,
    "Current state hasn't ticked on update'");
}

BOOST_AUTO_TEST_CASE(state_machine_get_curent_state)
{
    Game game;
    StateMachine machine(game);
    DummyState states[2] = {DummyState(), DummyState()};

    machine.stackState(std::make_unique<DummyState>(states[0]));
    BOOST_CHECK_MESSAGE(machine.getCurrentState()->get().getId() == 9,
    "Returned current state's id isn't valid, expected 9 got " << machine.getCurrentState()->get().getId());
    machine.stackState(std::make_unique<DummyState>(states[1]));
    BOOST_CHECK_MESSAGE(machine.getCurrentState()->get().getId() == 10,
    "Returned current state's id isn't valid, expected 10 got " << machine.getCurrentState()->get().getId());
    machine.leaveCurrentState();
    BOOST_CHECK_MESSAGE(machine.getCurrentState()->get().getId() == 9,
    "Returned current state's id isn't valid, expected 9 got " << machine.getCurrentState()->get().getId());
}
