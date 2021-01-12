#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#define __AZURITE__INNER__SYSTEMS_MANAGER

#include <iostream>
#include <functional>
#include <any>
#include <vector>

template<typename Ret, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(*) (Arg, Rest...));

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(F::*) (Arg, Rest...));

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg first_argument_helper(Ret(F::*) (Arg, Rest...) const);

template <typename F>
decltype(first_argument_helper(&F::operator())) first_argument_helper(F);

template <typename T>
using first_argument = decltype(first_argument_helper(std::declval<T>()));

template <typename T>
T getValue();

namespace Azurite {

    class Game;

    // Global Logic Handling class
    class SystemsManager {
        class System {
            SystemsManager &m_owner;
            std::any m_function;
            std::function<void(Game &, std::any &)> m_summoner;
        public:
        // System Methods
            template<typename T>
            System(SystemsManager &owner, T function) : m_owner(owner), m_function(function)
            {
                m_summoner = [](Game &game, std::any &function) {
                    std::any_cast<T>(function)();
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
