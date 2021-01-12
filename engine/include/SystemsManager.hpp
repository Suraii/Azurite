#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#define __AZURITE__INNER__SYSTEMS_MANAGER

#include <iostream>
#include <functional>
#include <any>

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

template<>
int getValue<int>() {
    return 5;
}

template<>
char getValue<char>() {
    return 'f';
}

#include <string>

template<>
std::string getValue<std::string>() {
    return "five";
}

namespace Azurite {

    class Game;

    // Global Logic Handling class
    class SystemsManager {
        class System {
        public:
            SystemsManager &m_owner;
            std::any m_function;
            std::function<void(System &)> m_summoner;
        // System Methods
            template<typename T>
            System(SystemsManager &owner, T function) : m_owner(owner), m_function(function)
            {
                m_summoner = [](System &self) {
                    Game &game = self.m_owner.m_owner;
                    std::any_cast<T>(self.m_function)();
                };
            }
            void run();
        };
        friend System;

        Game &m_owner;
    public:
        SystemsManager(Game &owner);
        ~SystemsManager();
        template<typename T>
        void createSystem(T function)
        {

        };
        void runSystems();
    };

    /*class System {
        std::any m_function;
        std::function<void(Game &, std::any)> m_summoner;
        Game &m_game;
    public:
        template<typename T>
        System(Game &game, T lambda) : m_game(game), m_function(lambda)
        {
            m_summoner = [](Game &, std::any function) {
                std::cout << "hoho\n";
                std::any_cast<T>(function)();
            };
        }

        void run()
        {
            m_summoner(m_game, m_function);
        }
    };*/
};

#endif

/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__GAME
#include "Game.hpp"
#endif
