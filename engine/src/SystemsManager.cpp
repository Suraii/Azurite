#include "SystemsManager.hpp"

using namespace Azurite;

/*
** SYSTEMS MANAGER IMPLEMENTATION
*/

SystemsManager::SystemsManager(Game &owner) : m_owner(owner)
{}

SystemsManager::~SystemsManager()
{}

void SystemsManager::runSystems()
{
    for (auto &system : m_systems)
        system.run();
}

void SystemsManager::createCoreSystem(std::function<void(Game &)> function)
{
    m_systems.emplace_back(*this, function);
}

/*
** SYSTEM IMPLEMENTATION
*/

// Core System Ctor
SystemsManager::System::System(SystemsManager &owner, std::function<void(Game &)> function)
: m_owner(owner), m_function(function)
{
    m_summoner = [](Game &game, std::any function) {
        std::function<void(Game &)> casted_function = \
        std::any_cast<std::function<void(Game &)>>(function);

        casted_function(game);
    };
}

void SystemsManager::System::run()
{
    m_summoner(m_owner.m_owner, m_function);
}
