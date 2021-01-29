#include "Azurite/Game.hpp"
#include "Azurite/modules/SfmlModule.hpp"
#include "states/MainState.hpp"
#include <memory>
#include <iostream>

#include "Azurite/systems/Ssprites_drawer.hpp"

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
    game.componentsStorage.registerComponent<Azurite::CTransform2D>();

    // Creating a state and adding it in the state queue
    MainState state;

    game.stateMachine.setState(std::make_unique<MainState>(state));

    // Adding the drawer system
    game.systemsManager.createCoreSystem(Azurite::Ssprites_drawer);

    game.run();
}
