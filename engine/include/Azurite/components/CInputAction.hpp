#ifndef __AZURITE__BUILT_IN_COMPONENTS_INPUT_ACTION
#define __AZURITE__BUILT_IN_COMPONENTS_INPUT_ACTION

#include "Azurite/Types.hpp"
#include <functional>

namespace Azurite {

struct CInputAction {
    Azurite::Input input;
    std::function<void(Azurite::Game &)> action = [](Azurite::Game &){};
    // Metadatas
    bool ready = false;
};

}

#endif
