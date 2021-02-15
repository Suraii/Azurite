#pragma once

#include "Azurite/StateMachine.hpp"

// State for the main menu

class MainState : public Azurite::AState {
    void onStart(Azurite::Game &instance);
    void onTick(Azurite::Game &instance);
    void onPause(Azurite::Game &instance);
    void onResume(Azurite::Game &instance);
    void onStop(Azurite::Game &instance);
};
