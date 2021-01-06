@startuml

class SystemsManager {
    -Game &owner
    -vector<System> systems
    +void addSystem(System system)
    -void runSystems()
}

@enduml
