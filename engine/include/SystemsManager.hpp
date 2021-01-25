#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#define __AZURITE__INNER__SYSTEMS_MANAGER

#include <iostream>
#include <functional>
#include <any>
#include <vector>
#include <tuple>
#include <type_traits>
#include <exception>
#include <concepts>

namespace Azurite {

    class Game;

    template<typename T> // Root template
    struct ComponentsSeeker : ComponentsSeeker<decltype(&T::operator())>
    {};

    template<typename T>
    concept system_fct = ComponentsSeeker<T>::isValid;

    // Global Logic Handling class
    class SystemsManager {
        class System {
            SystemsManager &m_owner;
            std::any m_function;
            std::function<void(Game &, std::any &)> m_summoner;
        public:
        // System Methods
            template<typename T> // System Ctor
            System(SystemsManager &owner, T function);
            // Core System Ctor
            System(SystemsManager &owner, std::function<void(Game &)> function);
            void run();
        };
        friend System;

        Game &m_owner;
        std::vector<System> m_systems;
    public:
        SystemsManager(Game &owner);
        ~SystemsManager();
        template<system_fct T>
        void createSystem(T function)
        {
            m_systems.emplace_back(*this, function);
        }
        void createCoreSystem(std::function<void(Game &)> function);
        void runSystems();
    };
};

#endif


/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif

#include "SystemsManager.impl.hpp"
