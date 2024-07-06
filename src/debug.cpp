#include "debug.hpp"

Debugger::Debugger(bool debug): m_debug_boolean(debug){}

void Debugger::log(const std::string &message) {
    std::cout << "\n[DEBUG]: " << message << "\n" << std::endl;
}
