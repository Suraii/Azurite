@startuml
class ComponentsStorage {
    -Game &owner
    -map<type, any> components
    -map<unsigned, long> parentStates
    -map<unsigned, bool> alive;
    -unsigned entityCount
    +registerComponent<T>()
    +vector<tuple<T&...>> getComponents<T...>()
    +map<unsigned, tuple<T&...>> getComponentsWithIds<T...>()
    +EntityBuilder buildEntity();
    +destroyEntity(unsigned id);
    -storeComponent<T>(unsigned id, T component)
    -map<unsigned, T> &getStorage<T>();
    -clearZombies<T>(map<unsigned, T>)
}

class EntityBuilder {
    -friend ComponentStorage &owner;
    -bool builded;
    +EntityBuilder &withComponent<T>(T component)
    +build()
    +buildAsOrphan()
}
@enduml
