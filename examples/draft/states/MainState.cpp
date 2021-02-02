#include "MainState.hpp"

#include "Azurite/Game.hpp"

#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CAnimatedSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"
#include "Azurite/components/CCollisionBox.hpp"
#include "components/CButton.hpp"

void MainState::onStart(Azurite::Game &instance)
{
    // Title
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CAnimatedSprite{"shooting_range_spritesheet",
    {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
    4, true, 300})
    .withComponent(Azurite::CTransform2D{{445, 150}, 0, {10, 10}})
    .build();

    // Start Button
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CSprite{"shooting_range_spritesheet"})
    .withComponent(Azurite::CTransform2D{{1045, 450}, 0, {5, 5}})
    .withComponent(CButton{0, 1, 2, [](Azurite::Game &game){}})
    .withComponent(Azurite::CCollisionBox{40, 7})
    .build();

    // Quit Button
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 10})
    .withComponent(Azurite::CTransform2D{{1045, 550}, 0, {5, 5}})
    .withComponent(CButton{10, 11, 12, [](Azurite::Game &game){
        game.stop();
    }})
    .withComponent(Azurite::CCollisionBox{30, 7})
    .build();
}

void MainState::onTick(Azurite::Game &instance)
{
    while (auto event = readEvent())
        if (event->name == "QUIT")
            instance.stateMachine.leaveCurrentState();
}

void MainState::onPause(Azurite::Game &instance)
{}

void MainState::onResume(Azurite::Game &instance)
{}

void MainState::onStop(Azurite::Game &instance)
{}
