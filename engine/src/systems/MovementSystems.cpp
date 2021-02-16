#include "Azurite/systems/MovementSystems.hpp"

using namespace Azurite;

void Azurite::Svelocity_applier(CTransform2D &transform, CVelocity &velocity)
{
    transform.location.x += velocity.x;
    transform.location.y += velocity.y;
}
