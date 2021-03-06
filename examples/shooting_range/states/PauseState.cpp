#include "PauseState.hpp"
#include "Azurite/components/MovementComponents.hpp"
#include "Azurite/components/UIComponents.hpp"


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

void PauseState::onTick(__attribute__((unused))Azurite::Game &instance)
{}

void PauseState::onPause(__attribute__((unused))Azurite::Game &instance)
{}

void PauseState::onResume(__attribute__((unused))Azurite::Game &instance)
{}

void PauseState::onStop(__attribute__((unused))Azurite::Game &instance)
{}
