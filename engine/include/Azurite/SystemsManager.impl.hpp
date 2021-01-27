#pragma once

namespace Azurite {

template<class F, class... Args> // Function specification
struct ComponentsSeeker<F(Args...)> {
    static void registerComponents(Game &game) {
        (game.componentsStorage.registerComponent<Args>(), ...);
    }
    std::vector<std::tuple<Args...>> seekComponents(Game &game) {
        return game.componentsStorage.getComponents<Args...>();
    }
    static constexpr bool isValid = true;
};

template<class F, class... Args> // Function pointer specification
struct ComponentsSeeker<F (*)(Args...)> {
    static void registerComponents(Game &game) {
        (game.componentsStorage.registerComponent<Args>(), ...);
    }
    std::vector<std::tuple<Args...>> seekComponents(Game &game) {
        return game.componentsStorage.getComponents<Args...>();
    }
    static constexpr bool isValid = true;
};

template<class F, class... Args> // std::function specification
struct ComponentsSeeker<std::function<F(Args...)>> {
    static void registerComponents(Game &game) {
        (game.componentsStorage.registerComponent<Args>(), ...);
    }
    std::vector<std::tuple<Args...>> seekComponents(Game &game) {
        return game.componentsStorage.getComponents<Args...>();
    }
    static constexpr bool isValid = true;
};

template<class F, class R, class... Args> // Lambda specification
struct ComponentsSeeker<R (F::*)(Args...) const> {
    static void registerComponents(Game &game) {
        (game.componentsStorage.registerComponent<Args>(), ...);
    }
    std::vector<std::tuple<Args...>> seekComponents(Game &game) {
        return game.componentsStorage.getComponents<Args...>();
    }
    static constexpr bool isValid = true;
};


template<typename T> // System Ctor
SystemsManager::System::System(SystemsManager &owner, T function) : m_owner(owner), m_function(function)
{
    ComponentsSeeker<T>::registerComponents(owner.m_owner);

    m_summoner = [](Game &game, std::any function) {
        T casted_function = std::any_cast<T>(function);
        ComponentsSeeker<T> seeker;
        auto components = seeker.seekComponents(game);

        for (auto &pack : components)
            std::apply(casted_function, pack);
    };
}

};
