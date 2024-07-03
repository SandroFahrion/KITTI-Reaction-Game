// spielerinformationen

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

class Player {
    public:
        Player(const std::string &name);    // Überladener Konstruktor
        void addReactionTime(double time);  // Wert einer Reaktionszeit verarbeiten

        // Debugging tools
        const std::string &getName() const;
        const std::vector<double> &getReactionTimes() const;

    private:
        std::string m_name;                   // Speichert den Spielernamen
        std::vector<double> m_reactionTimes;  // Enthält die Reaktionszeiten des Spielers
};

#endif // PLAYER_HPP
