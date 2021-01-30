#include "Azurite/Game.hpp"
#include "Azurite/modules/SfmlModule.hpp"
#include "states/MainState.hpp"
#include <memory>
#include <iostream>

#include "Azurite/systems/SpriteSystems.hpp"

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

    // Registering components
    game.componentsStorage.registerComponent<Azurite::CSprite>();
    game.componentsStorage.registerComponent<Azurite::CAnimatedSprite>();
    game.componentsStorage.registerComponent<Azurite::CTransform2D>();

    // Creating a state and adding it in the state queue
    MainState state;

    game.stateMachine.setState(std::make_unique<MainState>(state));

    // Adding the drawer system
    game.systemsManager.createCoreSystem(Azurite::Ssprites_drawer);
    game.systemsManager.createSystem(Azurite::Sanimated_sprite_updater);

    // Creating the Azurite logo
    game.componentsStorage.buildEntity()
    .withComponent(Azurite::CAnimatedSprite{"azurite", {0, 1, 2, 3, 4, 5, 6, 7, 8}, 10, true, 500})
    .withComponent(Azurite::CTransform2D{{{1867, 925}, 0, {0.5, 0.5}}})
    .build();

    game.run();
}
