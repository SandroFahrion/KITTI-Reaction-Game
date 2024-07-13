#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>
#include <type_traits>
#include <tuple>
#include <vector>

extern bool g_debug_mode;

class Debugger {
public:
    static void log(const std::string &description) {
        if (g_debug_mode) {
            std::cout << "[DEBUG]: " << description << std::endl;
        }
    }

    template <typename T>
    static void log(const T &obj, const std::string &description) {
        if (g_debug_mode) {
            std::cout << "[DEBUG]: " << description;
            printObject(obj);
        }
    }

private:
    template <typename T, typename = void>
    struct has_members : std::false_type {};

    template <typename T>
    struct has_members<T, std::void_t<decltype(std::declval<T>().getMembers()), decltype(std::declval<T>().getMemberNames())>> : std::true_type {};

    template <typename T>
    static void printObject(const T &obj) {
        if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, std::string>) {
            std::cout << "  " << obj << std::endl;
        } else if constexpr (has_members<T>::value) {
            auto members = obj.getMembers();
            auto memberNames = obj.getMemberNames();
            printMembers(members, memberNames, std::index_sequence_for<decltype(members)>{});
        } else {
            std::cout << "  [Object of type " << typeid(T).name() << "]" << std::endl;
        }
    }

    template <typename Tuple, typename Names, std::size_t... Is>
    static void printMembers(const Tuple &members, const Names &names, std::index_sequence<Is...>) {
        ((std::cout << "  " << names[Is] << " = " << std::get<Is>(members) << std::endl), ...);
    }
};

#endif // DEBUG_HPP
