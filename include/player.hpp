// Spielerinformationen

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

    void addReactionTime(float time);  // Wert einer Reaktionszeit verarbeiten
    void addHitTime(float time);

    // getter-Methoden
    const std::string &getName() const { return m_name; }
    const std::vector<float> &getReactionTimes() const { return m_reactionTimes; }
    const std::vector<float> &getHitTimes() const { return m_hitTimes; }

    //setter-Methoden
    void setName (std::string name); 

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_name, m_reactionTimes)

private:
    std::string m_name; // Speichert den Spielernamen
    std::vector<float> m_reactionTimes; // Enthält die Reaktionszeiten des Spielers
    std::vector<float> m_hitTimes; //Enthält die Hit-Zeiten des Spielers
};

#endif // PLAYER_HPP
