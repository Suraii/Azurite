#include "Azurite/Game.hpp"
#include "Azurite/modules/SfmlModule.hpp"
#include "Azurite/systems/SpriteSystems.hpp"

#include <memory>
#include <iostream>

#include "systems/ShootingRangeSystems.hpp"
#include "states/MainState.hpp"
#include "states/ScoreState.hpp"

int main()
{
    // Creating the game itself
    Azurite::Game game;

    // Creating a sfml module and setting it up in game placeholders
    std::unique_ptr<Azurite::AModule> sfml_mod(new Azurite::SfmlModule(game));

    game.addModule("sfml", std::move(sfml_mod))
    .useAsInputModule()
    .useAsAudioModule()
    .useAsAssetModule()
    .useAsDisplayModule();

    // Loading assets
    game.assetModule->get().loadAssets("../examples/draft/assets");

    // Creating a state and adding it in the state queue
    MainState state;
    game.stateMachine.setState(std::make_unique<MainState>(state));

    // Target systems
    game.systemsManager.createSystem(Starget_destructer);

    // Creating the Azurite logo
    game.componentsStorage.buildEntity()
    .withComponent(Azurite::CAnimatedSprite{"azurite", {0, 1, 2, 3, 4, 5, 6, 7, 8}, 10, true, 500})
    .withComponent(Azurite::CTransform2D{{1867, 925}, 0, {0.5, 0.5}})
    .buildAsOrphan();

    game.run();
}
