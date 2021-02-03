#include "ShootingRangeSystems.hpp"

void Starget_destructer(CTarget &target, Azurite::CButton &button, Azurite::CDestructible &destructible)
{
    if (button.triggered)
        destructible.isAlive = false;
}
