@startuml

class SystemsManager {
    -Game &owner
    -vector<System> systems
    +void createSystem(T function)
    -void runSystems()
}


SystemsManager *-- System
class System {
    -SystemsManager &owner
    -any function
    -function<void(Game &)> summoner
    +run()
}

@enduml
