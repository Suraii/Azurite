#ifndef __AZURITE__INNER__COMPONENTS_STORAGE
#define __AZURITE__INNER__COMPONENTS_STORAGE

#include <map>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include <tuple>

#include "Game.hpp"

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

    private: // Inner control methods
        //template<typename... T>
        //void storeComponents<T...>(unsigned id, T... components);
        //template<typename T>
        //std::map<unsigned, T> &getStorage<T>();
        //template<typename T>
        //void clearZombies<T>(std::map<unsigned, T> storage);

    public: // Control methods
        //template<typename T>
        //void registerComponent<T>();
        //template<typename T...>
        //std::vector<std::tuple<T&...>> getComponents<T...>();
        //template<typename T...>
        //std::map<unsigned, std::tuple<T&...>> getComponentsWithIds<T...>();
        //EntityBuilder buildEntity();
        void destroyEntity(unsigned id);
    };


};

#endif
