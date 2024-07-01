// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#include "gui.hpp"

StartParams::StartParams(const std::string& name, int num, const std::string& seq, int mode):    // Überladener Konstruktor
m_playerName(name), m_numImages(num), m_sequence(seq), m_gameMode(mode) {                        // Initializer List

}

StartParams GUI::showMenu(){

}

Player GUI::showScoreboard(){

}

void displayImage(const Image &image){

}