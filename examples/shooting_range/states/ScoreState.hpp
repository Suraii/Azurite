#pragma once

#include "Azurite/StateMachine.hpp"
#include <random>

// State for the score screen

class ScoreState : public Azurite::AState {
private:
    unsigned m_score;
    unsigned m_ticks;
    unsigned m_starsFilled;
public:
    ScoreState(int score);
    void onStart(Azurite::Game &instance);
    void onTick(Azurite::Game &instance);
    void onPause(Azurite::Game &instance);
    void onResume(Azurite::Game &instance);
    void onStop(Azurite::Game &instance);
};
