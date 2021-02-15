#include "Azurite/modules/SfmlModule.hpp"
#include "Azurite/Snitch.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/dll/runtime_symbol_info.hpp>

using namespace Azurite;

SfmlModule::SfmlModule(Game &game) :
AModule(game),
ADisplayModule(game),
AInputModule(game),
AAudioModule(game),
AAssetModule(game),
m_window(sf::VideoMode(1920, 1080), "Azurite Game"),
m_currentPath("")
{}

SfmlModule::~SfmlModule()
{}

/*
** Module Implementation
*/

void SfmlModule::onStart()
{}

#include <iostream>

void SfmlModule::onTick()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_owner.stop();
    }
    m_window.display();
    m_window.clear();
}

void SfmlModule::onStop()
{
}

/*
** Display Module Implementation
*/

void SfmlModule::drawSprite(const std::string spriteSheet, unsigned tileId, Transform2D transform)
{
    auto &asset = m_sprites.at(spriteSheet);
    auto &sprite = asset.data.at(tileId);

    sprite.setPosition(transform.location.x, transform.location.y);
    sprite.setRotation(transform.rotation);
    sprite.setScale(sf::Vector2f(transform.scale.x, transform.scale.y));

    m_window.draw(sprite);
}

void SfmlModule::drawRectangle(Transform2D shape, Color color)
{
    sf::RectangleShape rectangle;

    rectangle.setPosition(shape.location.x, shape.location.y);
    rectangle.setRotation(shape.rotation);
    rectangle.setSize(sf::Vector2f(shape.scale.x, shape.scale.y));
    rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));

    m_window.draw(rectangle);
}

/*
** Input Module Implementation
*/

#include <iostream>

bool SfmlModule::getInputStatus(Input input, __attribute__((unused))unsigned id)
{
    if (isKeyboard(input)) {
        return sf::Keyboard::isKeyPressed(InputToSfmlKey(input));
    }
    else if (isMouse(input)) {
        return sf::Mouse::isButtonPressed(InputToSfmlButton(input));
    }
    Snitch::warn() << "Unrecognized input" << Snitch::endl;
    return false;
}

Vector2D SfmlModule::getCursorLocation(__attribute__((unused))unsigned id)
{
    sf::Vector2i cursor = sf::Mouse::getPosition();

    /*
    ** For some reasons the result of this was 62 pixel above the correct position of my Cursor
    ** So, I did this VERY PROFESSIONAL FIX
    ** TODO: Fix this correctly
    */
    return {static_cast<float>(cursor.x), static_cast<float>(cursor.y) - 62};
}

/*
** Audio Module Implementation
*/

void SfmlModule::playSound(const std::string name, float volume, float pitch, bool loop)
{
    auto &sound = m_sounds.at(name).data;

    sound.setVolume(volume);
    sound.setPitch(pitch);
    sound.setLoop(loop);

    sound.stop();
    sound.play();
}

void SfmlModule::stopSound(const std::string name)
{
    auto &sound = m_sounds.at(name).data;

    sound.stop();
}

/*
** Asset Module Implementation
*/

void SfmlModule::loadAssets(const std::string dir_path)
{
    m_currentPath = dir_path;

    for (auto &file : std::filesystem::directory_iterator(dir_path))
        loadAsset(file.path());
    m_currentPath = "";
}

void SfmlModule::loadAsset(const std::string asset_path)
{
    if (asset_path.ends_with(".png"))
        loadSpriteSheet(asset_path);
    else if (asset_path.ends_with(".ogg"))
        loadSound(asset_path);
    else if (!asset_path.ends_with(".json"))
        Snitch::warn() << "Trying to load asset of unknown type : '" << asset_path << "'" << Snitch::endl;
}

void SfmlModule::loadSpriteSheet(std::filesystem::path path)
{
    sf::Texture texture;
    texture.loadFromFile(path);

    m_textures[path.stem()] = {std::move(texture), m_currentPath};

    boost::property_tree::ptree root(".");
    boost::property_tree::read_json(path.replace_extension(".json"), root);

    auto &asset = m_sprites[path.stem()];

    m_sprites[path.stem()] = {};
    for (auto const &sprite : root.get_child("sprites")) {
        sf::Sprite new_sprite(m_textures[path.stem()].data);
        sf::Rect<int> texture_rect(
            sprite.second.get<int>("origin_x"),
            sprite.second.get<int>("origin_y"),
            sprite.second.get<int>("width"),
            sprite.second.get<int>("height")
        );

        new_sprite.setTextureRect(texture_rect);

        asset.data[sprite.second.get<int>("id")] = std::move(new_sprite);
        asset.dir = m_currentPath;
    }
}

void SfmlModule::loadSound(const std::filesystem::path path)
{
    auto &asset = m_sounds[path.stem()];
    asset.dir = m_currentPath;
    asset.data.openFromFile(path);
}

void SfmlModule::releaseAssets(const std::string dir_path)
{
    for (auto &[path, asset] : m_sprites)
        if (asset.dir == dir_path)
            m_sprites.erase(path);
    for (auto &[path, asset] : m_textures)
        if (asset.dir == dir_path)
            m_textures.erase(path);
    for (auto &[path, asset] : m_sounds)
        if (asset.dir == dir_path)
            m_sounds.erase(path);
}

void SfmlModule::releaseAsset(const std::string asset_path)
{
    m_sprites.erase(asset_path);
    m_textures.erase(asset_path);
    m_sounds.erase(asset_path);
}
