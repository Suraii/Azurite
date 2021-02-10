#include "PauseState.hpp"
#include "Azurite/components/CInputAction.hpp"
#include "Azurite/components/CSprite.hpp"
#include "Azurite/components/CTransform2D.hpp"


void PauseState::onStart(Azurite::Game &instance)
{
    // Pause text
    instance.componentsStorage.buildEntity()
        .withComponent(Azurite::CSprite{"shooting_range_spritesheet", 70})
        .withComponent(Azurite::CTransform2D{{852.5, 300}, 0, {5, 5}})
    .build();

    // Entity that let you resume the game by pressing 'Escape'
    instance.componentsStorage.buildEntity()
        .withComponent(Azurite::CInputAction{Azurite::Input::ESC, [](Azurite::Game &game){
            PauseState state;

            game.stateMachine.leaveCurrentState();
        }})
    .build();
}

void PauseState::onTick(Azurite::Game &instance)
{}

void PauseState::onPause(Azurite::Game &instance)
{}

void PauseState::onResume(Azurite::Game &instance)
{}

void PauseState::onStop(Azurite::Game &instance)
{}
