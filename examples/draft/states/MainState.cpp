#include "MainState.hpp"

#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CAnimatedSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"

void MainState::onStart(Azurite::Game &instance)
{
    // Title
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CAnimatedSprite{"shooting_range_spritesheet",
    {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
    4, true, 300})
    .withComponent(Azurite::CTransform2D{{{445, 150}, 0, {10, 10}}})
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
