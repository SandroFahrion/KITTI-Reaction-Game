#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>
#include <type_traits>
#include <tuple>
#include <vector>

class Debugger {
public:
    Debugger(bool debug);

    bool m_debug_boolean = false;

    static void log(const std::string &message);

    template<typename T>
    static void log(const T &obj, const std::string &description);
};

#ifdef DEBUG_MODE
extern Debugger* g_debugger; // Declare g_debugger as extern
#endif // DEBUG_MODE

#include "debug.tpp" // Include the template implementation file

#endif // DEBUG_HPP
