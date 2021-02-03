#include "Azurite/systems/LifeSystems.hpp"

using namespace Azurite;

void Azurite::Sdestructible_reaper(Game &game)
{
    auto destructibles = game.componentsStorage.getComponentsWithIds<CDestructible>();

    for (auto &[id, destructible] : destructibles)
        if (!get<0>(destructible).isAlive)
            game.componentsStorage.destroyEntity(id);
}

void Azurite::Sdeath_rattle_invoker(Game &game)
{
    auto components = game.componentsStorage.getComponents<CDestructible, CDeathRattle>();

    for (auto &[destructible, death_rattle] : components)
        if (!destructible.isAlive)
            death_rattle.action(game);
}
