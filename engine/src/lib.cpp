#include "Snitch.hpp"
#include <iostream>

namespace Azurite {

    void print_hello() {
        std::cout << "(Azurite): Hello fellow programmer !" << std::endl;
        Snitch::info() << "Don't worry this is just an info, you're doing some weird stuff, but the program is still stable" << Snitch::endl;
        Snitch::warn() << "Oh no a warning, it may cause problems" << Snitch::endl;
        Snitch::err() << "An Error ?! fix this now" << Snitch::endl;
    }

}
