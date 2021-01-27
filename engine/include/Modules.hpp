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
        virtual ~AModule() {}
        virtual void onStart() = 0;
        virtual void onTick() = 0;
        virtual void onStop() = 0;
    };

    // Module to interact with the screen
    class ADisplayModule : virtual public AModule {
    public:
        ADisplayModule(Game &game) : AModule(game) {}
        virtual ~ADisplayModule() {}
        virtual void drawSprite(const std::string spriteSheet, unsigned tileId, Transform2D transform) = 0;
        virtual void drawRectangle(Transform2D shape, Color color) = 0;
    };

    // Module to interact with the keyboard / mouse
    class AInputModule : virtual public AModule {
    public:
        AInputModule(Game &game) : AModule(game) {}
        virtual ~AInputModule() {}
        virtual bool getInputStatus(Input input, unsigned id) = 0;
        virtual Vector2D getCursorLocation(unsigned id) = 0;
    };

    // Module to interact with the speakers
    class AAudioModule : virtual public AModule {
    public:
        AAudioModule(Game &game) : AModule(game) {}
        virtual ~AAudioModule() {}
        virtual void playSound(const std::string name, float volume = 1, float pitch = 1, bool loop = false) = 0;
        virtual void stopSound(const std::string name) = 0;
    };

    // Module to interact with the filesystem
    class AAssetModule : virtual public AModule {
    public:
        AAssetModule(Game &game) : AModule(game) {}
        virtual ~AAssetModule() {}
        virtual void loadAssets(const std::string dir_path) = 0;
        virtual void loadAsset(const std::string asset_path) = 0;
        virtual void releaseAssets(const std::string dir_path) = 0;
        virtual void releaseAsset(const std::string asset_path) = 0;
    };
}

#endif

/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif
