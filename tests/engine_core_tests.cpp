#define BOOST_TEST_MODULE Engine Core Tests

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "StateMachine.hpp"

using namespace Azurite;

/*
** ASTATE TESTS
*/

class DummyState : public AState {
    void onStart(__attribute__((unused)) Game &instance) {}
    void onTick(__attribute__((unused)) Game &instance)  {}
    void onPause(__attribute__((unused)) Game &instance) {}
    void onResume(__attribute__((unused)) Game &instance) {}
    void onStop(__attribute__((unused)) Game &instance) {}
public:
    std::string getEvent() {
        std::string buf = m_events.front().name;
        m_events.pop();
        return buf;
    }
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
