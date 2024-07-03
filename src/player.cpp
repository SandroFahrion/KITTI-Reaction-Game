// spielerinformationen

#include "player.hpp"

Player::Player(const std::string &name) : m_name(name){} // Überladenen Konstruktor aufrufen, Wert aus Referenz in member-Variable schreiben

void Player::addReactionTime(double time){  // siehe header-file für doku
    m_reactionTimes.push_back(time);        // Befüllen des reactionTimes-Vektors
}

// ----------------------------------------------------------
// Debugging tools

const std::string &Player::getName() const {
    return m_name;
}

const std::vector<double> &Player::getReactionTimes() const {
    return m_reactionTimes;
}

// Debugging tools
// ----------------------------------------------------------