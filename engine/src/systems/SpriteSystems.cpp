#include "Azurite/systems/SpriteSystems.hpp"

using namespace Azurite;

void Azurite::Ssprites_drawer(Game &game)
{
    auto components = game.componentsStorage.getComponents<CSprite, CTransform2D>();

    for (auto [sprite, transform] : components)
        game.displayModule->get().drawSprite(sprite.spritesheet, sprite.id,
        {transform.location, transform.rotation, transform.scale});

    auto acomponents = game.componentsStorage.getComponents<CAnimatedSprite, CTransform2D>();

    for (auto [asprite, transform] : acomponents)
        game.displayModule->get().drawSprite(asprite.spritesheet, asprite.ids[asprite.currentId],
        {transform.location, transform.rotation, transform.scale});
}

void Azurite::Sanimated_sprite_updater(CAnimatedSprite &asprite)
{
    if (!asprite.running)
        return;

    if (++asprite.ticksOnCurrent >= asprite.ticksOnTile) {
        asprite.currentId++;
        if (asprite.currentId >= asprite.ids.size()) {
            asprite.currentId = 0;
            asprite.ticksOnCurrent = -1 * asprite.loopDelay;
            asprite.running = asprite.loop;
        } else
            asprite.ticksOnCurrent = 0;
    }
}
