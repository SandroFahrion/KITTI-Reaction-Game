// spielerinformationen

#include "player.hpp"

Player::Player() {}

Player::Player(const std::string &name) : m_name(name) {} // Überladenen Konstruktor aufrufen, Wert aus Referenz in member-Variable schreiben

void Player::addReactionTime(double time) {  // siehe header-file für doku
    m_reactionTimes.push_back(time);        // Befüllen des reactionTimes-Vektors
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player: { Name: " << player.m_name << ", Reaction Times: [";
    for (const auto& time : player.m_reactionTimes) {
        os << time << " ";
    }
    os << "]}";
    return os;
}