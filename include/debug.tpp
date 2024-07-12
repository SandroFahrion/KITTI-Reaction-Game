#ifndef DEBUG_TPP
#define DEBUG_TPP

#include "debug.hpp"
#include "serialize.hpp"

template <typename T>
void Debugger::log(const T &obj, const std::string &description) {
    std::cout << "[DEBUG]: " << description;

    if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, std::string>) {
        std::cout << "  " << obj << std::endl;
    } else {
        auto members = obj.getMembers();
        auto memberNames = obj.getMemberNames();
        printObject(members, memberNames);
    }
}

#endif // DEBUG_TPP
