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
        class EntityBuilder;
        friend EntityBuilder;

        Game &m_owner;
        std::unordered_map<std::type_index, std::any> m_components;
        std::map<unsigned, long> m_parentStates;
        std::map<unsigned, bool> m_lifeLines;
        unsigned m_entityCount;

    public: // Ctor / Dtor
        ComponentsStorage(Game &owner);
        ~ComponentsStorage();

    private : // Tools

        unsigned getFreeId();

        template<typename... T>
        bool entityIsValid(
            const unsigned id,
            const std::map<unsigned, T>&... storages
        )
        {
            bool is_alive;

            try {
                is_alive = m_lifeLines.at(id);
            } catch(std::out_of_range &e) {
                Snitch::warn() << "Trying to read component that isn't part of an entity, with id " << id << Snitch::endl;
                is_alive = false;
            }

            return
            is_alive
            && ((storages.find(id) != storages.end()) && ...)
            && (
                !(m_owner.stateMachine.getCurrentState())
                || (*m_owner.stateMachine.getCurrentState()).get().getId() == m_parentStates.at(id)
                || (m_parentStates.at(id) == -1)
            );
        }

    // Inner control methods
        template<typename T>
        void storeComponent(unsigned id, T components)
        {
            std::map<unsigned, T> &storage = getStorage<T>();

            storage[id] = components;
        }

        template<typename T>
        std::map<unsigned, T> &getStorage()
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

        template<typename T, typename... R>
        std::vector<std::tuple<T&, R&...>> joinStorages
        (
            std::map<unsigned, T>& first,
            std::map<unsigned, R>&... rest
        )
        {
            std::vector<std::tuple<T&, R&...>> output;

            for (auto& [id, component]: first)
                if (entityIsValid(id, rest...))
                    output.push_back(std::tuple<T&, R&...>{component, rest.at(id)...});
            return output;
        }

        template<typename T, typename... R>
        std::map<unsigned, std::tuple<T&, R&...>> joinStoragesWithIds
        (
            std::map<unsigned, T>& first,
            std::map<unsigned int, R>&... rest
        )
        {
            std::map<unsigned, std::tuple<T&, R&...>> output;

            for (auto& [id, component]: first)
                if (entityIsValid(id, rest...))
                    output.emplace(id, std::tuple<T&, R&...>{component, rest.at(id)...});
            return output;
        }

        template<typename T>
        void clearZombies(std::map<unsigned, T> &storage)
        {
            for (const auto &[id, is_alive] : m_lifeLines)
                if (!is_alive)
                    storage.erase(id);
        }

    // Control methods
    public:

        template<typename T>
        void registerComponent()
        {
            std::map<unsigned, T> new_storage;

            m_components[std::type_index(typeid(T))] = std::move(new_storage);
        }

        template<typename T, typename... R>
        std::vector<std::tuple<T&, R&...>> getComponents()
        {
            return joinStorages(getStorage<T>(), getStorage<R>()...);
        }

        template<typename T, typename... R>
        std::map<unsigned, std::tuple<T&, R&...>> getComponentsWithIds()
        {
            return joinStoragesWithIds(getStorage<T>(), getStorage<R>()...);
        }

        EntityBuilder buildEntity();
        void destroyEntity(unsigned id);

    /*
    ** ENTITY BUILDER SUBCLASS
    */

    private:

        class EntityBuilder {
            ComponentsStorage &m_owner;
            unsigned m_id;
            bool m_builded;
        public:
            EntityBuilder(ComponentsStorage &owner, unsigned id);
            ~EntityBuilder();
            template<typename T>
            EntityBuilder &withComponent(T component)
            {
                m_owner.storeComponent(m_id, component);
                return *this;
            }
            unsigned build();
            unsigned buildAsOrphan();
        };
    };
};

#endif
