#include "GameState.hpp"
#include "PauseState.hpp"
#include "ScoreState.hpp"
#include "Azurite/Game.hpp"
#include "Azurite/components/MovementComponents.hpp"
#include "Azurite/components/LifeComponents.hpp"
#include "Azurite/components/UIComponents.hpp"
#include "Azurite/components/SoundComponents.hpp"
#include "components/CTarget.hpp"

constexpr unsigned TARGET_SUMMON_DELAY = 100;
constexpr unsigned TARGET_MIN_HEIGHT = 100;
constexpr unsigned TARGET_MAX_HEIGHT = 920;
constexpr float TARGET_MIN_VELOCITY = 3;
constexpr float TARGET_MAX_VELOCITY = 10;
constexpr float TARGET_MIN_SCALE = 7;
constexpr float TARGET_MAX_SCALE = 15;

GameState::GameState() : m_ticks(0), m_targetCounts(20), m_generator(), m_score(0)
{}

void GameState::onStart(Azurite::Game &instance)
{
    // This entity is used pause the game when 'Escape' is pressed
    instance.componentsStorage.buildEntity()
        .withComponent(Azurite::CInputAction{Azurite::Input::ESC, [](Azurite::Game &game){
            PauseState state;

            game.stateMachine.stackState(std::make_unique<PauseState>(state));
        }})
    .build();
}

void GameState::onTick(Azurite::Game &instance)
{
    // Initializing Randomizers
    std::uniform_real_distribution<float> heightDistribution(TARGET_MIN_HEIGHT, TARGET_MAX_HEIGHT);
    std::uniform_real_distribution<float> velocityDistribution(TARGET_MIN_VELOCITY, TARGET_MAX_VELOCITY);
    std::uniform_real_distribution<float> scaleDistriution(TARGET_MIN_SCALE, TARGET_MAX_SCALE);

    float scale = scaleDistriution(m_generator);

    if (m_ticks >= TARGET_SUMMON_DELAY && m_targetCounts > 0) {
    // Summoning targets that send events and gets destroyed when you click on them
        instance.componentsStorage.buildEntity()
            .withComponent(Azurite::CTransform2D{{1920, heightDistribution(m_generator)}, 0, {scale, scale}})
            .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 20})
            .withComponent(Azurite::CCollisionBox{7, 7})
            .withComponent(Azurite::CButton{20, 20, 21})
            .withComponent(Azurite::CDestructible{})
            .withComponent(Azurite::CDeathRattle{[](Azurite::Game &game){
                game.stateMachine.getCurrentState()->get().sendEvent(Azurite::Event{"Target Destroyed"});
            }})
            .withComponent(Azurite::CVelocity{-1 * velocityDistribution(m_generator), 0})
            .withComponent(CTarget{})
            .withComponent(Azurite::CSpeaker{"gunshot"})
        .build();
        // Updating variables
        m_ticks = 0;
        m_targetCounts -= 1;
    }
    // Moving to score board when all targets are summoned
    if (m_ticks > 400) {
        ScoreState state(m_score);
        instance.stateMachine.setState(std::make_unique<ScoreState>(state));
    }
    m_ticks++;

    // Incremeting Score when 'Target Destroyed' event is received
    while (auto event = readEvent()) {
        if (event->name == "Target Destroyed")
            m_score++;
    }
}

void GameState::onPause(__attribute__((unused))Azurite::Game &instance)
{}

void GameState::onResume(__attribute__((unused))Azurite::Game &instance)
{}

void GameState::onStop(__attribute__((unused))Azurite::Game &instance)
{}
