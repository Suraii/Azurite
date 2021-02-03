#include "GameState.hpp"
#include "Azurite/Game.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CAnimatedSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"
#include "Azurite/components/CCollisionBox.hpp"
#include "Azurite/components/CDestructible.hpp"
#include "Azurite/components/CButton.hpp"
#include "components/CTarget.hpp"

void GameState::onStart(Azurite::Game &instance)
{
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CTransform2D{{10, 10}, 0, {10, 10}})
    .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 20})
    .withComponent(Azurite::CCollisionBox{7, 7})
    .withComponent(Azurite::CButton{20, 20, 21})
    .withComponent(Azurite::CDestructible{})
    .withComponent(CTarget{})
    .build();
}

void GameState::onTick(Azurite::Game &instance)
{}

void GameState::onPause(Azurite::Game &instance)
{}

void GameState::onResume(Azurite::Game &instance)
{}

void GameState::onStop(Azurite::Game &instance)
{}
