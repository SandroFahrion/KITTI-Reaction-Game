// spielerinformationen

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "../helpers/member_util.hpp"

class Player {
public:
    Player();   // Standardkonstruktor
    ~Player();  // Standarddestruktor

    Player(const std::string &name);    // Überladener Konstruktor

    // setter-Methode
    void addReactionTime(float time);  // Wert einer Reaktionszeit verarbeiten

    // getter-Methoden
    const std::string &getName() const {
        return m_name;
    }
    const std::vector<float> &getReactionTimes() const {
        return m_reactionTimes;
    }

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_name, m_reactionTimes)

private:
    std::string m_name;                   // Speichert den Spielernamen
    std::vector<float> m_reactionTimes;  // Enthält die Reaktionszeiten des Spielers
};

#endif // PLAYER_HPP
