#pragma once

#include <functional>
#include "Azurite/Game.hpp"

namespace Azurite {

struct CButton {
    unsigned idleId;
    unsigned hoveredId;
    unsigned clickedId;
    std::function<void(Azurite::Game &)> action = [](Azurite::Game &){};
    // Metadata
    bool clicked = false;
    bool hovered = false;
    bool triggered = false;
};

};
