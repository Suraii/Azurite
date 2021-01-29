#include "Azurite/systems/Ssprites_drawer.hpp"

using namespace Azurite;

void Azurite::Ssprites_drawer(Game &game)
{
    auto components = game.componentsStorage.getComponents<CSprite, CTransform2D>();

    for (auto [sprite, transform] : components)
        game.displayModule->get().drawSprite(sprite.spritesheet, sprite.id,
        {transform.location, transform.rotation, transform.scale});
}
