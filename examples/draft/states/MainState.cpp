#include "MainState.hpp"

#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"

void MainState::onStart(Azurite::Game &instance)
{
    instance.componentsStorage.buildEntity()
    .withComponent(Azurite::CSprite{"azurite"})
    .withComponent(Azurite::CTransform2D{{{0, 0}}})
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
