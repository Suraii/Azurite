#include "ComponentsStorage.hpp"

using namespace Azurite;

/*
** COMPONENT STORAGE IMPLEMENTATION
*/

ComponentsStorage::ComponentsStorage(Game &owner) : m_owner(owner), m_entityCount(0)
{}

ComponentsStorage::~ComponentsStorage() {}

unsigned ComponentsStorage::getFreeId()
{
    for (unsigned i = 0; i < m_entityCount; i++)
        if (!m_lifeLines[i])
            return i;
    return m_entityCount++;
}

ComponentsStorage::EntityBuilder ComponentsStorage::buildEntity()
{
    return EntityBuilder(*this, getFreeId());
}

void ComponentsStorage::destroyEntity(unsigned id)
{
    m_lifeLines[id] = false;
}

/*
** ENTITY BUILDER IMPLEMENTATION
*/

ComponentsStorage::EntityBuilder::EntityBuilder(ComponentsStorage &owner, unsigned id)
: m_owner(owner), m_id(id), m_builded(false)
{}

ComponentsStorage::EntityBuilder::~EntityBuilder()
{
    if (!m_builded)
        Snitch::warn() << "missing .build() after entity builder" << Snitch::endl;
}

unsigned ComponentsStorage::EntityBuilder::build()
{
    if (m_owner.m_owner.stateMachine.getCurrentState())
        m_owner.m_parentStates[m_id] = \
m_owner.m_owner.stateMachine.getCurrentState()->get().getId();
    else
        m_owner.m_parentStates[m_id] = -1;
    m_owner.m_lifeLines[m_id] = true;
    m_builded = true;

    return m_id;
}

unsigned ComponentsStorage::EntityBuilder::buildAsOrphan()
{
    m_owner.m_parentStates[m_id] = -1;
    m_owner.m_lifeLines[m_id] = true;
    m_builded = true;

    return m_id;
}
