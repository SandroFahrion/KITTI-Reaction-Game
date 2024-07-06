// spielerinformationen

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>

class Player {
public:
    Player();
    Player(const std::string &name);    // Überladener Konstruktor
    void addReactionTime(double time);  // Wert einer Reaktionszeit verarbeiten

    const std::string &getName() const {
        return m_name;
    }
    const std::vector<double> &getReactionTimes() const {
        return m_reactionTimes;
    }

    auto getMembers() const {
        return std::make_tuple(m_name, m_reactionTimes);
    }

    std::vector<std::string> getMemberNames() const {
        return {"m_name", "m_reactionTimes"};
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player);


private:
    std::string m_name;                   // Speichert den Spielernamen
    std::vector<double> m_reactionTimes;  // Enthält die Reaktionszeiten des Spielers
};

#endif // PLAYER_HPP
