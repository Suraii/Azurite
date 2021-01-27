#define BOOST_TEST_MODULE Engine Core Tests

#include <boost/test/included/unit_test.hpp>
#include <string>
#include "Azurite/Game.hpp"
#include "Azurite/StateMachine.hpp"
#include "Azurite/ComponentsStorage.hpp"
#include "Azurite/SystemsManager.hpp"

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

BOOST_AUTO_TEST_CASE(states_read_event)
{
    DummyState state;
    std::string words[4] = {"It's", "free", "real", "estate"};

    for (unsigned i = 0; i < 4; i++)
        state.sendEvent(Event{words[i]});

    int count = 0;
    while (auto event = state.readEvent()) {
        std::string word = event->name;
        BOOST_CHECK_MESSAGE(word == words[count],
"Error in events queue, expected " << words[count] << " got " << word);
        count++;
    }
    BOOST_CHECK_MESSAGE(count == 4,
"Only " << count << " events on 4 were read");
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
    BOOST_CHECK_MESSAGE(machine.getCurrentState()->get().getId() == 10,
    "Returned current state's id isn't valid, expected 10 got " << machine.getCurrentState()->get().getId());
    machine.stackState(std::make_unique<DummyState>(states[1]));
    BOOST_CHECK_MESSAGE(machine.getCurrentState()->get().getId() == 11,
    "Returned current state's id isn't valid, expected 11 got " << machine.getCurrentState()->get().getId());
    machine.leaveCurrentState();
    BOOST_CHECK_MESSAGE(machine.getCurrentState()->get().getId() == 10,
    "Returned current state's id isn't valid, expected 10 got " << machine.getCurrentState()->get().getId());
}

/*
** COMPONENTS STORAGE TESTS
*/

struct Misc {
    int data = 0;
};

BOOST_AUTO_TEST_CASE(components_storage_building_entities_and_getting_components)
{
    Game game;
    ComponentsStorage storage(game);
    unsigned ids[3];

    storage.registerComponent<int>();
    storage.registerComponent<char>();
    storage.registerComponent<bool>();
    storage.registerComponent<Misc>();

    ids[0] = storage.buildEntity()
        .withComponent(false)
        .withComponent('z')
        .build();

    ids[1] = storage.buildEntity()
        .withComponent(true)
        .withComponent('t')
        .withComponent(33)
        .withComponent(Misc{3})
        .build();

    ids[2] = storage.buildEntity()
        .withComponent('q')
        .build();

    for (unsigned i = 0; i < 3; i++)
        BOOST_CHECK_MESSAGE(ids[i] == i,
        "Wrong id returned by build(), expected " << i << " got " << ids[i]);

    std::map<unsigned, std::tuple<int &, char &, bool &>> components_ids \
    = storage.getComponentsWithIds<int, char, bool>();
    std::vector<std::tuple<int &, char &, bool &>> components \
    = storage.getComponents<int, char, bool>();

    BOOST_CHECK_MESSAGE(components.size() == components_ids.size()
    && components_ids.size() == 1,
    "Wrong size for returned components containers, expected 1 for both, got " << components.size()\
    << " and " << components_ids.size() << " with ids");
    BOOST_CHECK_MESSAGE(components_ids.find(1) != components_ids.end(),
    "Couldn't find entity 1 in returned components containers");
    BOOST_CHECK_MESSAGE(components_ids.at(1) == components.at(0),
    "Different values in components containers with and without ids");
}

BOOST_AUTO_TEST_CASE(components_storage_destroying_entities)
{
    Game game;
    ComponentsStorage storage(game);

    storage.registerComponent<int>();
    storage.registerComponent<bool>();

    storage.buildEntity()
        .withComponent(44)
        .withComponent(false)
        .build();

    storage.buildEntity()
        .withComponent(22)
        .withComponent(true)
        .build();

    storage.buildEntity()
        .withComponent(55)
        .withComponent(true)
        .build();

    storage.destroyEntity(0);
    storage.destroyEntity(2);

    std::vector<std::tuple<int &, bool &>> components \
    = storage.getComponents<int, bool>();

    BOOST_CHECK_MESSAGE(components.size() == 1,
    "Wrong size for returned components, expected 1, got " << components.size());
}

BOOST_AUTO_TEST_CASE(components_storage_id_recycling)
{
    Game game;
    ComponentsStorage storage(game);

    storage.registerComponent<int>();

    storage.buildEntity()
        .withComponent(0)
        .build();

    storage.destroyEntity(0);

    unsigned id = storage.buildEntity()
        .withComponent(1)
        .build();

    BOOST_CHECK_MESSAGE(id == 0,
    "Builded entity should use the freed id '0', instead it used " << id);
}

BOOST_AUTO_TEST_CASE(components_storage_parent_states)
{
    Game game;
    ComponentsStorage storage(game);

    storage.registerComponent<int>();

    storage.buildEntity()
        .withComponent(0)
        .build();

    game.stateMachine.stackState(std::make_unique<DummyState>(DummyState()));

    storage.buildEntity()
        .withComponent(1)
        .build();
    storage.buildEntity()
        .withComponent(1)
        .buildAsOrphan();

    game.stateMachine.stackState(std::make_unique<DummyState>(DummyState()));

    storage.buildEntity()
        .withComponent(1)
        .build();
    storage.buildEntity()
        .withComponent(1)
        .build();

    BOOST_CHECK_MESSAGE(storage.getComponents<int>().size() == 4,
    "Wrong numbers of components actives during state " <<
    game.stateMachine.getCurrentState()->get().getId() <<
    ", expected " << 4 << " got " << storage.getComponents<int>().size());

    game.stateMachine.leaveCurrentState();

    BOOST_CHECK_MESSAGE(storage.getComponents<int>().size() == 3,
    "Wrong numbers of components actives during state " <<
    game.stateMachine.getCurrentState()->get().getId() <<
    ", expected " << 3 << " got " << storage.getComponents<int>().size());

    game.stateMachine.leaveCurrentState();

    BOOST_CHECK_MESSAGE(storage.getComponents<int>().size() == 2,
    "Wrong numbers of components actives out of states " <<
    ", expected " << 2 << " got " << storage.getComponents<int>().size());
}

/*
** SYSTEMS MANAGER TESTS
*/

struct WitnessBool {
    bool value = false;
};

void change_bools(bool &b) { b = true; }

BOOST_AUTO_TEST_CASE(systems_manager_creating_systems_from_various_types)
{
    Game game;
    SystemsManager system(game);
    std::function<void(bool &b)> my_function = [](bool &b){ b = true; };

    system.createSystem([](bool &b) { b = true; });
    system.createSystem(&change_bools);
    system.createSystem(my_function);
}

BOOST_AUTO_TEST_CASE(systems_manager_basic_system)
{
    Game game;
    SystemsManager system(game);

    system.createSystem([](WitnessBool &wb, int &i) {
        wb.value = true;
        i++;
    });
    for (int i = 0; i < 10; i++)
        game.componentsStorage.buildEntity()
        .withComponent(WitnessBool()).withComponent(0).build();
    system.runSystems();
    auto components = game.componentsStorage.getComponents<WitnessBool, int>();

    BOOST_CHECK_MESSAGE(components.size() == 10, \
    "Wrong size for components vector, expected 10, got " << components.size());

    for (auto &component : components)
        BOOST_REQUIRE_MESSAGE(std::get<0>(component).value && std::get<1>(component),
    "Witness's value wasn't properly set to true or int wasn't properly incremented'");
}

BOOST_AUTO_TEST_CASE(systems_manager_core_system)
{
    Game game;
    SystemsManager system(game);

    game.componentsStorage.registerComponent<bool>();
    system.createCoreSystem([](Game &game){
        game.componentsStorage.buildEntity().withComponent(true).build();
    });
    system.runSystems();
    BOOST_CHECK_MESSAGE(game.componentsStorage.getComponents<bool>().size() == 1,
    "Component was not added in storage during core system's run");
}

/*
** MODULES
*/

class DummyModule : public AModule {
    public:
        DummyModule(Game &game) : AModule(game) {}
        ~DummyModule() {}
        void onStart() override {}
        void onTick() override {}
        void onStop() override {}
};

class DummyInput : public AInputModule {
    public:
        DummyInput(Game &game) : AModule(game), AInputModule(game) {}
        ~DummyInput() {}
        void onStart() override {}
        void onTick() override {}
        void onStop() override {}
        bool getInputStatus(__attribute__((unused))Input input, __attribute__((unused))unsigned id) override { return true; }
        Vector2D getCursorLocation(__attribute__((unused))unsigned id) override {return {0.5, 0.5}; }
};

BOOST_AUTO_TEST_CASE(modules_creating_modules)
{
    Game game;
    std::unique_ptr<AModule> dummy(new DummyModule(game));
    std::unique_ptr<AModule> input(new DummyInput(game));

    game.addModule("dummy", std::move(dummy));
    __attribute__((unused))DummyModule &casted = dynamic_cast<DummyModule &>(game.getModule("dummy"));
    game.addModule("input", std::move(input));
    __attribute__((unused))DummyInput &casted2 = dynamic_cast<DummyInput &>(game.getModule("input"));
}
