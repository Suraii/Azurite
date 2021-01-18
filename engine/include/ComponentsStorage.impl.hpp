#pragma once

#include "ComponentsStorage.hpp"

using namespace Azurite;

template<typename... T>
bool ComponentsStorage::entityIsValid(const unsigned id, const std::map<unsigned, T>&... storages) const
{
    bool is_alive;

    try {is_alive = m_lifeLines.at(id);}
    catch(std::out_of_range &e) {
        Snitch::warn() << "Trying to read component that isn't part of an entity, with id " << id << Snitch::endl;
        is_alive = false;
    }

    return
        is_alive
        && ((storages.find(id) != storages.end()) && ...)
        && (
            (
                m_owner.stateMachine.getCurrentState()
                && (*m_owner.stateMachine.getCurrentState()).get().getId() == m_parentStates.at(id)
            ) || (m_parentStates.at(id) == -1)
        );
}

template<typename T>
void ComponentsStorage::storeComponent(unsigned id, T components)
{
    std::map<unsigned, T> &storage = getStorage<T>();

    storage[id] = components;
}


template<typename T>
std::map<unsigned, T> &ComponentsStorage::getStorage()
{
    for (auto &[id, storage] : m_components) {
        if (std::type_index(typeid(T)) == id) {
            std::map<unsigned, T> &output = std::any_cast<std::map<unsigned, T> &>(storage);
            clearZombies(output);
            return output;
        }
    }
    Snitch::err() << "Call to ComponentsStorage::getStorage() on unregistered type '"
    << typeid(T).name()
    << "', please register it before via ComponentsStorage::registerComponent()" << Snitch::endl;
    throw(std::out_of_range("Element not found in map"));
}

template<typename T>
void ComponentsStorage::clearZombies(std::map<unsigned, T> &storage)
{
    for (const auto &[id, is_alive] : m_lifeLines)
        if (!is_alive)
            storage.erase(id);
}

template<typename T>
void ComponentsStorage::registerComponent()
{
    std::map<unsigned, T> new_storage;

    m_components[std::type_index(typeid(T))] = std::move(new_storage);
}

template<typename T, typename... R>
std::vector<std::tuple<T&, R&...>> ComponentsStorage::getComponents()
{
    return joinStorages(getStorage<std::remove_reference_t<T>>(), getStorage<std::remove_reference_t<R>>()...);
}

template<typename T, typename... R>
std::map<unsigned, std::tuple<T&, R&...>> ComponentsStorage::getComponentsWithIds()
{
    return joinStoragesWithIds(getStorage<std::remove_reference_t<T>>(), getStorage<std::remove_reference_t<R>>()...);
}
