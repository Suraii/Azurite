#ifndef __AZURITE__INNER__COMPONENTS_STORAGE
#define __AZURITE__INNER__COMPONENTS_STORAGE

#include <map>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include <tuple>
#include <exception>

#include "Game.hpp"
#include "Snitch.hpp"

namespace Azurite {

    // ECS Data container class
    class ComponentsStorage {
        Game &m_owner;
        std::unordered_map<std::type_index, std::any> m_components;
        std::map<unsigned, long> m_parentStates;
        std::map<unsigned, bool> m_lifeLines;
        unsigned m_entityCount;

    public: // Ctor / Dtor
        ComponentsStorage(Game &owner);
        ~ComponentsStorage();

    // Inner control methods
        //template<typename... T>
        //void storeComponents<T...>(unsigned id, T... components);
        template<typename T>
        std::map<unsigned, T> &getStorage()
        {
            for (auto &[id, storage] : m_components)
                if (std::type_index(typeid(T)) == id)
                    return std::any_cast<std::map<unsigned, T> &>(storage);
            Snitch::err() << "Call to ComponentsStorage::getStorage() on unregistered type '"
            << typeid(T).name()
            << "', please register it before via ComponentsStorage::registerComponent()" << Snitch::endl;
            throw(std::out_of_range("Element not found in map"));
        }
        //template<typename T>
        //void clearZombies<T>(std::map<unsigned, T> storage);

    // Control methods
        template<typename T>
        void registerComponent()
        {
            std::map<unsigned, T> new_storage;

            m_components[std::type_index(typeid(T))] = std::move(new_storage);
        }
        //template<typename T...>
        //std::vector<std::tuple<T&...>> getComponents<T...>();
        //template<typename T...>
        //std::map<unsigned, std::tuple<T&...>> getComponentsWithIds<T...>();
        //EntityBuilder buildEntity();
        void destroyEntity(unsigned id);
    };


};

#endif
