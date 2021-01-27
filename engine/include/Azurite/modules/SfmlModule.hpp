#ifndef __AZURITE__OUTER__SFML_MODULE
#define __AZURITE__OUTER__SFML_MODULE

#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <utility>
#include <filesystem>

namespace Azurite {

    class SfmlModule :
    public ADisplayModule,
    public AInputModule,
    public AAudioModule,
    public AAssetModule
    {
        sf::RenderWindow m_window;

        template<typename T>
        struct Asset {
            T data;
            std::string dir;
        };

        std::unordered_map<std::string, Asset<sf::Texture>> m_textures;
        std::unordered_map<std::string, Asset<std::unordered_map<unsigned, sf::Sprite>>> m_sprites;
        std::unordered_map<std::string, Asset<sf::Music>> m_sounds;
        std::string m_currentPath;

    public:
        SfmlModule(Game &);
        ~SfmlModule();
    // Module Implementation
        void onStart() override;
        void onTick() override;
        void onStop() override;
    // DisplayModule Implementation
        void drawSprite(const std::string spriteSheet, unsigned tileId, Transform2D transform) override;
        void drawRectangle(Transform2D shape, Color color) override;
    // InputModule Implementation
        bool getInputStatus(Input input, unsigned id = 0) override;
        Vector2D getCursorLocation(unsigned id = 0) override;
    // AudioModule Implementation
        void playSound(const std::string name, float volume = 1, float pitch = 1, bool loop = false) override;
        void stopSound(const std::string name) override;
    // AssetModule Implementation
        void loadAssets(const std::string dir_path) override;
        void loadAsset(const std::string asset_path) override;
        void loadSpriteSheet(std::filesystem::path path);
        void loadSound(const std::filesystem::path path);
        void releaseAssets(const std::string dir_path) override;
        void releaseAsset(const std::string asset_path) override;
    };

};

#endif
