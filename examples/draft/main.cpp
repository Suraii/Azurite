#include "Azurite/Game.hpp"
#include "Azurite/modules/SfmlModule.hpp"
#include <memory>

int main()
{
    Azurite::Game game;
    std::unique_ptr<Azurite::AModule> sfml_mod(new Azurite::SfmlModule(game));

    game.addModule("sfml", std::move(sfml_mod));

    game.run();
}
