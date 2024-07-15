// spielerinformationen

#include "player.hpp"

Player::Player() {}     // Standardkonstruktor
Player::~Player() {}    // Standarddestruktor

Player::Player(const std::string &name) : m_name(name) {} // Überladenen Konstruktor aufrufen, Wert aus Referenz in member-Variable schreiben

void Player::addReactionTime(float time) {  
    m_reactionTimes.push_back(time);    // Befüllen des reactionTimes-Vektors
}
