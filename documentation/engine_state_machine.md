@startuml
class StateMachine {
-Game &owner
-stack<AState &> states
-update()
+setState(unique_ptr<AState>)
+stackState(unique_ptr<AState>)
+leaveCurrentState()
+optional<AState &> getCurrentState()
}

StateMachine *-right- AState
abstract AState {
-unsigned id
-queue<Event> events_queue
+getId()
+sendEvent(Event)
+onStart(Game &)
+onTick(Game &)
+OnPause(Game &)
+OnResume(Game &)
+OnStop(Game &)
}

AState *-right- Event
class Event {
+string name
}
@enduml
