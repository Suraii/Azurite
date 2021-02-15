#include "ShootingRangeSystems.hpp"

// System that destroyes target when theur button components is clicked
void Starget_destructer(CTarget &target, Azurite::CButton &button, Azurite::CDestructible &destructible)
{
    if (button.clicked)
        destructible.isAlive = false;
}
