#include "GameState.hpp"
#include "Azurite/Game.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CAnimatedSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"
#include "Azurite/components/CCollisionBox.hpp"
#include "Azurite/components/CDestructible.hpp"
#include "Azurite/components/CButton.hpp"
#include "Azurite/components/CLifetime.hpp"
#include "Azurite/components/CVelocity.hpp"
#include "Azurite/components/CDeathRattle.hpp"
#include "components/CTarget.hpp"

constexpr unsigned TARGET_SUMMON_DELAY = 100;
constexpr unsigned TARGET_MIN_HEIGHT = 100;
constexpr unsigned TARGET_MAX_HEIGHT = 920;
constexpr float TARGET_MIN_VELOCITY = 3;
constexpr float TARGET_MAX_VELOCITY = 10;
constexpr float TARGET_MIN_SCALE = 7;
constexpr float TARGET_MAX_SCALE = 15;

GameState::GameState() : m_ticks(0), m_targetCounts(20), m_generator()
{}

void GameState::onStart(Azurite::Game &instance)
{}

void GameState::onTick(Azurite::Game &instance)
{
    std::uniform_real_distribution<float> heightDistribution(TARGET_MIN_HEIGHT, TARGET_MAX_HEIGHT);
    std::uniform_real_distribution<float> velocityDistribution(TARGET_MIN_VELOCITY, TARGET_MAX_VELOCITY);
    std::uniform_real_distribution<float> scaleDistriution(TARGET_MIN_SCALE, TARGET_MAX_SCALE);

    float scale = scaleDistriution(m_generator);

    if (m_ticks >= TARGET_SUMMON_DELAY && m_targetCounts > 0) {
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
        .build();
        m_ticks = 0;
        m_targetCounts -= 1;
    }
    if (m_ticks > 400)
        instance.stateMachine.leaveCurrentState();
    m_ticks++;
}

void GameState::onPause(Azurite::Game &instance)
{}

void GameState::onResume(Azurite::Game &instance)
{}

void GameState::onStop(Azurite::Game &instance)
{}
