#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

// Hilfsfunktion, um ein einzelnes Mitglied auszugeben
template <typename T>
void printMember(const T& member, const std::string& name) {
    std::cout << "  " << name << " = " << member << std::endl;
}

// Hilfsfunktion, um die Mitglieder eines Objekts zu iterieren und auszugeben
template <typename Tuple, std::size_t... Is>
void printTuple(const Tuple& t, std::index_sequence<Is...>, const std::vector<std::string>& names) {
    (printMember(std::get<Is>(t), names[Is]), ...);
}

// Funktion, die die Mitglieder eines Objekts ausgibt
template <typename... Args>
void printObject(const std::tuple<Args...>& t, const std::vector<std::string>& names) {
    printTuple(t, std::index_sequence_for<Args...>{}, names);
}

#endif // SERIALIZE_HPP
