#pragma once

#include "Azurite/StateMachine.hpp"
#include <random>

class PauseState : public Azurite::AState {
    void onStart(Azurite::Game &instance);
    void onTick(Azurite::Game &instance);
    void onPause(Azurite::Game &instance);
    void onResume(Azurite::Game &instance);
    void onStop(Azurite::Game &instance);
};
