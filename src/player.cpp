// spielerinformationen

#include "player.hpp"

//entweder
#include <iostream>
// oder
#include "gui.hpp"

Player::Player(const std::string &name) : m_name(name){} // Überladenen Konstruktor aufrufen, Wert aus Referenz in member-Variable schreiben

void Player::addReactionTime(double time){ 
    m_reactionTimes.push_back(time);        // Befüllen des reactionTimes-Vektors
}

void Player::printStatistics(){
    // entweder cout oder gui aufrufen
}
