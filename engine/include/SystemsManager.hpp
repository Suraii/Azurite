/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif

#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#define __AZURITE__INNER__SYSTEMS_MANAGER

#include <iostream>
#include <functional>
#include <any>
#include <vector>
#include <tuple>
#include <type_traits>
#include <exception>

namespace Azurite {

    template<typename T> // Root template
    struct ComponentsSeeker : ComponentsSeeker<decltype(&T::operator())> {};

    template<class F, class... Args> // Function specification
    struct ComponentsSeeker<F(Args...)> {
        std::vector<std::tuple<Args...>> seekComponents(Game &game) {
            return game.componentsStorage.getComponents<Args...>();
        }
    };

    template<class F, class... Args> // Function pointer specification
    struct ComponentsSeeker<F (*)(Args...)> {
        std::vector<std::tuple<Args...>> seekComponents(Game &game) {
            return game.componentsStorage.getComponents<Args...>();
        }
    };

    template<class F, class... Args> // std::function specification
    struct ComponentsSeeker<std::function<F(Args...)>> {
        std::vector<std::tuple<Args...>> seekComponents(Game &game) {
            return game.componentsStorage.getComponents<Args...>();
        }
    };

    template<class F, class R, class... Args> // Lambda specification
    struct ComponentsSeeker<R (F::*)(Args...) const> {
        std::vector<std::tuple<Args...>> seekComponents(Game &game) {
            return game.componentsStorage.getComponents<Args...>();
        }
    };

    class Game;

    // Global Logic Handling class
    class SystemsManager {
        class System {
            SystemsManager &m_owner;
            std::any m_function;
            std::function<void(Game &, std::any &)> m_summoner;
        public:
        // System Methods
            template<typename T> // System Ctor
            System(SystemsManager &owner, T function) : m_owner(owner), m_function(function)
            {
                m_summoner = [](Game &game, std::any function) {
                    T casted_function = std::any_cast<T>(function);
                    ComponentsSeeker<T> seeker;
                    auto components = seeker.seekComponents(game);

                    for (auto &pack : components)
                        std::apply(casted_function, pack);
                };

            }

            template <> // Core System Ctor
            System(SystemsManager &owner, std::function<void(Game &)> function)
            : m_owner(owner), m_function(function)
            {
                m_summoner = [](Game &game, std::any function) {
                    std::function<void(Game &)> casted_function = \
                    std::any_cast<std::function<void(Game &)>>(function);

                    casted_function(game);
                };
            }

            void run();
        };
        friend System;

        Game &m_owner;
        std::vector<System> m_systems;
    public:
        SystemsManager(Game &owner);
        ~SystemsManager();
        template<typename T>
        void createSystem(T function)
        {
            m_systems.emplace_back(*this, function);
        };
        void createCoreSystem(std::function<void(Game &)> function);
        void runSystems();
    };
};

#endif
