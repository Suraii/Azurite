#include "ScoreState.hpp"
#include "PauseState.hpp"
#include "Azurite/Game.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"
#include "Azurite/components/CCollisionBox.hpp"
#include "Azurite/components/CButton.hpp"

constexpr float STARS_ORIGIN = 310;
constexpr float STARS_INTERSPACE = 15;
constexpr int STARS_FILL_DELAY = 10;

ScoreState::ScoreState(int score) : m_score(score), m_ticks(0), m_starsFilled(0)
{}

void ScoreState::onStart(Azurite::Game &instance)
{
    // Building 20 'Empty' stars to represent the scores
    for (char i = 0; i < 20; i++) {
        instance.componentsStorage.buildEntity()
            .withComponent(Azurite::CTransform2D{{STARS_ORIGIN + 50 * i + STARS_INTERSPACE * i, 300}, 0, {10, 10}})
            .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 30})
        .build();
    }

    // Quit Button
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 10})
    .withComponent(Azurite::CTransform2D{{1545, 850}, 0, {5, 5}})
    .withComponent(Azurite::CButton{10, 11, 12, [](Azurite::Game &game){
        game.stop();
    }})
    .withComponent(Azurite::CCollisionBox{30, 7})
    .build();
}

void ScoreState::onTick(Azurite::Game &instance)
{
    // 'Filling' stars by placing colored stars on them for every target hit in precedent state
    if (m_starsFilled < m_score && m_ticks >= STARS_FILL_DELAY) {
        instance.componentsStorage.buildEntity()
            .withComponent(Azurite::CTransform2D{{STARS_ORIGIN + 50 * m_starsFilled + STARS_INTERSPACE * m_starsFilled, 300}, 0, {10, 10}})
            .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 31})
        .build();
        m_starsFilled++;
        m_ticks = 0;
    }
    m_ticks++;
}

void ScoreState::onPause(Azurite::Game &instance)
{}

void ScoreState::onResume(Azurite::Game &instance)
{}

void ScoreState::onStop(Azurite::Game &instance)
{}

