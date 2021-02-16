#include "Azurite/Game.hpp"
#include <chrono>
#include <thread>

using namespace Azurite;

Game::Game() : stateMachine(*this), componentsStorage(*this), systemsManager(*this)
{
    importBuiltIns();
}

Game::~Game()
{}

/*
** MODULES CONTROL METHODS
*/

Game &Game::addModule(const std::string &name, std::unique_ptr<AModule> module)
{
    m_modules.emplace(name, std::move(module));
    m_lastModule = getModule(name);

    return *this;
}

Game &Game::useAsDisplayModule()
{
    if (!m_lastModule)
        Snitch::warn() << \
"Call to useAsDisplayModule while no modules are loaded" << Snitch::endl;
    else
        displayModule = dynamic_cast<ADisplayModule &>(m_lastModule->get());

    return *this;
}

Game &Game::useAsInputModule()
{
    if (!m_lastModule)
        Snitch::warn() << \
"Call to useAsInputModule while no modules are loaded" << Snitch::endl;
    else
        inputModule = dynamic_cast<AInputModule &>(m_lastModule->get());

    return *this;
}

Game &Game::useAsAudioModule()
{
    if (!m_lastModule)
        Snitch::warn() << \
"Call to useAsAudioModule while no modules are loaded" << Snitch::endl;
    else
        audioModule = dynamic_cast<AAudioModule &>(m_lastModule->get());

    return *this;
}

Game &Game::useAsAssetModule()
{
    if (!m_lastModule)
        Snitch::warn() << \
"Call to useAsAssetModule while no modules are loaded" << Snitch::endl;
    else
        assetModule = dynamic_cast<AAssetModule &>(m_lastModule->get());

    return *this;
}

AModule &Game::getModule(const std::string &name)
{
    return (*m_modules.at(name));
}

void Game::removeModule(const std::string &name)
{
    m_modules.erase(name);
}

/*
** GAME CONTROL METHODS
*/

void Game::run()
{
    int game_tick_delay = 10/*ms*/;
    std::chrono::time_point loop_start = std::chrono::system_clock::now();
    std::chrono::milliseconds tick_delay(game_tick_delay);

    while(stateMachine.getCurrentState()) {
        loop_start = std::chrono::system_clock::now();
        stateMachine.update();
        for (auto &[name, module] : m_modules) {
            (*module).onTick();
        }
        systemsManager.runSystems();
        if (std::chrono::system_clock::now() - loop_start < tick_delay)
            std::this_thread::sleep_for(tick_delay - (std::chrono::system_clock::now() - loop_start));
        else
            Snitch::warn() << "Game update took " <<
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - loop_start).count()
            << " ms, that's over the maximum needed to maintain a constant framerate (" << game_tick_delay << " ms)" << Snitch::endl;
    }
}

void Game::stop()
{
    while(stateMachine.getCurrentState())
        stateMachine.leaveCurrentState();
    for (auto &[name, module] : m_modules) {
        module->onStop();
    }
}

/*
** GAME CONTENT METHODS
*/

#include "Azurite/systems/SpriteSystems.hpp"
#include "Azurite/systems/LifeSystems.hpp"
#include "Azurite/systems/UISystems.hpp"
#include "Azurite/systems/MovementSystems.hpp"
#include "Azurite/systems/SoundSystems.hpp"

void Game::importBuiltIns()
{
    // Misc
    componentsStorage.registerComponent<CTransform2D>();
    componentsStorage.registerComponent<CCollisionBox>();
    // Sprites
    componentsStorage.registerComponent<CSprite>();
    componentsStorage.registerComponent<CAnimatedSprite>();
    systemsManager.createCoreSystem(Ssprites_drawer);
    systemsManager.createSystem(Sanimated_sprite_updater);
    // Life
    componentsStorage.registerComponent<CDeathRattle>();
    systemsManager.createCoreSystem(Sdeath_rattle_invoker);
    systemsManager.createCoreSystem(Sdestructible_reaper);
    systemsManager.createSystem(Slifetime_ticker);
    // UI
    componentsStorage.registerComponent<CInputAction>();
    systemsManager.createSystem(Sbutton_sprite_updater);
    systemsManager.createCoreSystem(Sbutton_params_updater);
    systemsManager.createCoreSystem(Sinput_action_invoker);
    // Movement
    systemsManager.createSystem(Svelocity_applier);
    // Sound
    systemsManager.createSystem(Sbutton_speaker_activator);
    systemsManager.createCoreSystem(Sspeaker_player);
}

void Game::enableDebugSystems()
{
    // DEBUG Collision box displayer
    systemsManager.createCoreSystem([](Azurite::Game &game){
        auto params = game.componentsStorage.getComponents<Azurite::CCollisionBox, Azurite::CTransform2D>();
        for (auto &[box, transform] : params) {
            game.displayModule->get().drawRectangle({{transform.location.x, transform.location.y},
            transform.rotation, {box.size.x * transform.scale.x, box.size.y * transform.scale.y}},
            {255, 0, 0, 125});
        }
    });
    // DEBUG Draw Cursor
    systemsManager.createCoreSystem([](Azurite::Game &game){
        Azurite::Vector2D cursor = game.inputModule->get().getCursorLocation();
        bool lclick = game.inputModule->get().getInputStatus(Azurite::Input::MOUSE_LEFT_CLICK);
        unsigned char red = (lclick)? 255 : 0;
        bool rclick = game.inputModule->get().getInputStatus(Azurite::Input::MOUSE_RIGHT_CLICK);
        unsigned char blue = (rclick)? 255 : 0;
        game.displayModule->get().drawRectangle(
            {{cursor.x, cursor.y}, 0, {30, 30}},
            {red, 255, blue, 125}
        );
    });
}
