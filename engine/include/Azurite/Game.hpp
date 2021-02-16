/*
** DEPENDENCIES
*/

#ifndef __AZURITE__INNER__STATE_MACHINE
#include "Azurite/StateMachine.hpp"
#endif

#ifndef __AZURITE__INNER__COMPONENTS_STORAGE
#include "Azurite/ComponentsStorage.hpp"
#endif

#ifndef __AZURITE__INNER__MODULES
#include "Azurite/Modules.hpp"
#endif

#ifndef __AZURITE__INNER__SYSTEMS_MANAGER
#include "Azurite/SystemsManager.hpp"
#endif

#ifndef __AZURITE__INNER__GAME
#define __AZURITE__INNER__GAME

#include <vector>
#include <functional>
#include <string>
#include <memory>

namespace Azurite {

    class Game {
    public:
    // Subclasses
        StateMachine stateMachine;
        ComponentsStorage componentsStorage;
        SystemsManager systemsManager;
        Game();
        ~Game();

    private:
    // Modules storage
        std::unordered_map<std::string, std::unique_ptr<AModule>> m_modules;
        std::optional<std::reference_wrapper<AModule>> m_lastModule;
    public:
    // Modules placeholdes
        std::optional<std::reference_wrapper<ADisplayModule>> displayModule;
        std::optional<std::reference_wrapper<AInputModule>> inputModule;
        std::optional<std::reference_wrapper<AAudioModule>> audioModule;
        std::optional<std::reference_wrapper<AAssetModule>> assetModule;
    // Modules Control Methods
        Game &addModule(const std::string &name, std::unique_ptr<AModule> module);
        Game &useAsDisplayModule();
        Game &useAsInputModule();
        Game &useAsAudioModule();
        Game &useAsAssetModule();
        AModule &getModule(const std::string &name);
        void removeModule(const std::string &name);
    // Game Control Methods
        void run();
        void stop();
    // Game content Methods
        void importBuiltIns();
        void enableDebugSystems();
    };
}

#endif
