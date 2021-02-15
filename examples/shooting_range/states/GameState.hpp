#pragma once

#include "Azurite/StateMachine.hpp"
#include <random>

// State for the game itself

class GameState : public Azurite::AState {
private:
    unsigned m_ticks;
    int m_targetCounts;
    std::default_random_engine m_generator;
    int m_score;
public:
    GameState();
    void onStart(Azurite::Game &instance);
    void onTick(Azurite::Game &instance);
    void onPause(Azurite::Game &instance);
    void onResume(Azurite::Game &instance);
    void onStop(Azurite::Game &instance);
};
