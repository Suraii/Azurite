#include "ComponentsStorage.hpp"

using namespace Azurite;

/*
** COMPONENT STORAGE IMPLEMENTATION
*/

ComponentsStorage::ComponentsStorage(Game &owner) : m_owner(owner)
{}

ComponentsStorage::~ComponentsStorage() {}

//EntityBuilder ComponentsStorage::buildEntity() {}

/*
** ENTITY BUILDER IMPLEMENTATION
*/

EntityBuilder::EntityBuilder(ComponentsStorage &owner, unsigned id)
: m_owner(owner), m_id(id), m_builded(false)
{}

EntityBuilder::~EntityBuilder()
{
    if (!m_builded)
        Snitch::warn() << "missing .build() after entity builder" << Snitch::endl;
}

void EntityBuilder::build()
{
    if (m_owner.m_owner.stateMachine.getCurrentState())
        m_owner.m_parentStates[m_id] = \
m_owner.m_owner.stateMachine.getCurrentState()->get().getId();
    else
        m_owner.m_parentStates[m_id] = -1;
    m_owner.m_lifeLines[m_id] = true;
    m_owner.m_entityCount++;
    m_builded = true;
}

void EntityBuilder::buildAsOrphan()
{
    m_owner.m_parentStates[m_id] = -1;
    m_owner.m_lifeLines[m_id] = true;
    m_owner.m_entityCount++;
    m_builded = true;
}
