#include "Azurite/Snitch.hpp"

using namespace Azurite;

std::ostream &Snitch::output = std::cerr;

std::string Snitch::endl = "\e[0m\n";

std::ostream &Snitch::info(const std::string &label)
{
    Snitch::output << "\e[36m[" << label << "]: ";
    return Snitch::output;
}

std::ostream &Snitch::warn(const std::string &label)
{
    Snitch::output << "\e[33m[" << label << "]: ";
    return Snitch::output;
}

std::ostream &Snitch::err(const std::string &label)
{
    Snitch::output << "\e[31m[" << label << "]: ";
    return Snitch::output;
}
