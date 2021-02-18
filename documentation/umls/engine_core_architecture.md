@startuml
class Game {
    -ComponentsStorage componentsStorage
    -SystemsManager systemsManager
    -StateMachine stateMachine
    -vector<IModule> modules
}

class ComponentsStorage
Game *-- ComponentsStorage

class SystemsManager
Game *-- SystemsManager

class StateMachine
Game *-- StateMachine

interface IModule
Game *-- IModule
@enduml
