#include "Azurite/Game.hpp"
#include "Azurite/modules/SfmlModule.hpp"
#include "states/MainState.hpp"
#include <memory>
#include <iostream>

#include "Azurite/systems/SpriteSystems.hpp"
#include "systems/ShootingRangeSystems.hpp"

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
    game.componentsStorage.registerComponent<Azurite::CCollisionBox>();
    game.componentsStorage.registerComponent<CButton>();

    // Creating a state and adding it in the state queue
    MainState state;

    game.stateMachine.setState(std::make_unique<MainState>(state));

    // Adding the drawer system
    game.systemsManager.createCoreSystem(Azurite::Ssprites_drawer);
    game.systemsManager.createSystem(Azurite::Sanimated_sprite_updater);
    // Adding the button systems
    game.systemsManager.createSystem(Sbutton_sprite_updater);
    game.systemsManager.createCoreSystem(Sbutton_params_updater);
    // DEBUG Collision box displayer
    game.systemsManager.createCoreSystem([](Azurite::Game &game){
        auto params = game.componentsStorage.getComponents<Azurite::CCollisionBox, Azurite::CTransform2D>();
        for (auto &[box, transform] : params) {
            game.displayModule->get().drawRectangle({{transform.location.x, transform.location.y},
            transform.rotation, {box.size.x * transform.scale.x, box.size.y * transform.scale.y}},
            {255, 0, 0, 125});
        }
    });
    // DEBUG Draw Cursor
    game.systemsManager.createCoreSystem([](Azurite::Game &game){
        Azurite::Vector2D cursor = game.inputModule->get().getCursorLocation();
        bool lclick = game.inputModule->get().getInputStatus(Azurite::Input::MOUSE_LEFT_CLICK);
        unsigned char red = (lclick)? 255 : 0;
        bool rclick = game.inputModule->get().getInputStatus(Azurite::Input::MOUSE_RIGHT_CLICK);
        unsigned char blue = (rclick)? 255 : 0;
        game.displayModule->get().drawRectangle(
            {{cursor.x, cursor.y}, 0, {30, 30}},
            {red, 255, blue, 125}
        );
    });

    // Creating the Azurite logo
    game.componentsStorage.buildEntity()
    .withComponent(Azurite::CAnimatedSprite{"azurite", {0, 1, 2, 3, 4, 5, 6, 7, 8}, 10, true, 500})
    .withComponent(Azurite::CTransform2D{{1867, 925}, 0, {0.5, 0.5}})
    .build();

    game.run();
}
