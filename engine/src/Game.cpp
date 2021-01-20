#include "Game.hpp"

using namespace Azurite;

Game::Game() : stateMachine(*this), componentsStorage(*this), systemsManager(*this)
{}

Game::~Game()
{}

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
