#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>
#include <type_traits>
#include <tuple>
#include <vector>

#ifdef DEBUG_MODE
extern bool g_debug_mode;

class Debugger {
public:
    static void log(const std::string &description) {
        if (g_debug_mode) {
            std::cout << "\n[DEBUG]: " << description << std::endl;
        }
    }

    template <typename T>
    static void log(const T &obj, const std::string &description) {
        if (g_debug_mode) {
            std::cout << "\n[DEBUG]: " << description << std::endl;
            if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, std::string>) {
                std::cout << "  " << obj << std::endl;
            } else {
                printObject(obj);
            }
        }
    }

private:
    template <typename T>
    static void printObject(const T &obj) {
        auto members = obj.getMembers();
        auto memberNames = obj.getMemberNames();
        printMembers(members, memberNames, std::index_sequence_for<decltype(members)>{});
    }

    template <typename Tuple, typename Names, std::size_t... Is>
    static void printMembers(const Tuple &members, const Names &names, std::index_sequence<Is...>) {
        ((std::cout << "  " << names[Is] << " = " << std::get<Is>(members) << std::endl), ...);
    }
};

#endif // DEBUG_MODE

#endif // DEBUG_HPP
