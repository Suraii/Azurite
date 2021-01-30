#ifndef __AZURITE__BUILT_IN_COMPONENTS_ANIMATED_SPRITE
#define __AZURITE__BUILT_IN_COMPONENTS_ANIMATED_SPRITE

#include <string>
#include <vector>

namespace Azurite {

struct CAnimatedSprite {
    std::string spritesheet;
    std::vector<unsigned> ids = {0};
    int ticksOnTile = 10;
    bool loop = true;
    int loopDelay = 0;
    // Metadatas
    unsigned short currentId = 0;
    int ticksOnCurrent = 0;
    bool running = true;
};

}

#endif
