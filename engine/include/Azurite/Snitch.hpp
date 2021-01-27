#ifndef __AZURINTE__INNER__SNITCH
#define __AZURINTE__INNER__SNITCH

#include <iostream>
#include <string>

namespace Azurite {

    class Snitch {
    public:
        static std::ostream &output;
        static std::string endl;
        static std::ostream &info(const std::string &label = "INFO");
        static std::ostream &warn(const std::string &label = "WARNING");
        static std::ostream &err(const std::string &label = "ERROR");
    };

}
#endif
