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

/*
** SYSTEM IMPLEMENTATION
*/

void SystemsManager::System::run()
{
    m_summoner(m_owner.m_owner, m_function);
}
