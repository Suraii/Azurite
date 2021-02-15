#pragma once

#include "Azurite/Game.hpp"
#include <string>

namespace Azurite {

struct CSpeaker {
    std::string sound;
    float volume = 100;
    float pitch = 1;
    bool loop = false;
    void play() {
        isStopping = false;
        isPlaying = true;
    }
    void stop() {
        isPlaying = false;
        isStopping = true;
    }
    // Metadatas
    bool isPlaying = false;
    bool isStopping = false;
};

};
