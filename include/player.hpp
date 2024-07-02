// spielerinformationen

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

class Player {
    public:
        //Player(); // Standardkonstruktor
        //~Player(); // Destruktor
        Player(const std::string &name);    // Überladener Konstruktor
        void addReactionTime(double time);  // Wert einer Reaktionszeit verarbeiten
    
    private:
        std::string m_name; // Speichert den Spielernamen
        std::vector<double> m_reactionTimes;  // Enthält die Reaktionszeiten des Spielers
};

#endif // PLAYER_HPP
