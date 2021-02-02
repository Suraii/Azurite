#ifndef __AZURITE__BUILT_IN_COMPONENTS_TRANSFORM2D
#define __AZURITE__BUILT_IN_COMPONENTS_TRANSFORM2D

#include "Azurite/Types.hpp"

namespace Azurite {

struct CTransform2D {
    Vector2D location = {0, 0};
    float rotation = 0;
    Vector2D scale = {1, 1};
};

}

#endif
