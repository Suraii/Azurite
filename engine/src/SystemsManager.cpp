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
{}

/*
** SYSTEM IMPLEMENTATION
*/

void SystemsManager::System::run()
{}
