#pragma once

#include <functional>
#include "Azurite/Game.hpp"

struct CButton {
    unsigned idleId;
    unsigned hoveredId;
    unsigned clickedId;
    std::function<void(Azurite::Game &)> action;
    // Metadata
    bool clicked = false;
    bool hovered = false;
};
