#ifndef __AZURITE__INNER__MODULES
#define __AZURITE__INNER__MODULES

#include <string>
#include <Types.hpp>

namespace Azurite {

    class Game;

    // Module Abstract
    class AModule {
    protected:
        Game &m_owner;
    public:
        AModule(Game &game) : m_owner(game) {}
        virtual ~AModule() = 0;
        virtual void onStart() = 0;
        virtual void onTick() = 0;
        virtual void onStop() = 0;
    };

    // Module to interact with the screen
    class ADisplayModule : public AModule {
        void drawSprite(const std::string spriteSheet, unsigned tileId, Transform2D transform);
        void drawRectangle(Transform2D shape, Color color);
    };

    // Module to interact with the keyboard / mouse
    class AInputModule : public AModule {
        bool getInputStatus(unsigned id, Input input);
        Vector2D getCursorLocation(unsigned id);
    };

    // Module to interact with the speakers
    class AAudioModule : public AModule {
        void playSound(const std::string name, float volume = 1, float pitch = 1, bool loop = false);
        void stopSound(const std::string name);
    };

    // Module to interact with the filesystem
    class AAssetModule : public AModule {
        void loadAssets(const std::string dir_path);
        void loadAsset(const std::string asset_path);
        void releaseAssets(const std::string dir_path);
        void releaseAsset(const std::string asset_path);
    };
}

#endif

/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif
