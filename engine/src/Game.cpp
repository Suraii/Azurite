#include "Azurite/Game.hpp"
#include <chrono>
#include <thread>

using namespace Azurite;

Game::Game() : stateMachine(*this), componentsStorage(*this), systemsManager(*this)
{}

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
