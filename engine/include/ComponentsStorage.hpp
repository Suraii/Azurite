#ifndef __AZURITE__INNER__COMPONENTS_STORAGE
#define __AZURITE__INNER__COMPONENTS_STORAGE

#include <map>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include <tuple>
#include <exception>

#include "Snitch.hpp"

namespace Azurite {

    class Game;

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
        bool entityIsValid(const unsigned id, const std::map<unsigned, T>&... storages) const;

    // Inner control methods
        template<typename T>
        void storeComponent(unsigned id, T components);

        template<typename T>
        std::map<unsigned, T> &getStorage();

        template<typename T>
        void clearZombies(std::map<unsigned, T> &storage);

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

    // Control methods
    public:

        template<typename T>
        void registerComponent();

        template<typename T, typename... R>
        std::vector<std::tuple<T&, R&...>> getComponents();

        template<typename T, typename... R>
        std::map<unsigned, std::tuple<T&, R&...>> getComponentsWithIds();

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

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif

#include "ComponentsStorage.impl.hpp"
