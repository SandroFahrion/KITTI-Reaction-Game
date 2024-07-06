// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>

#include "image.hpp"
#include "player.hpp"

class StartParams {
public:
    StartParams();
    StartParams(const std::string &name, int turns, int seq, int mode); // Überladener Konstruktor
    // Member-Variablen
    std::string m_playerName;
    int m_numTurns, m_gameMode, m_sequence;
};

class GUI {
public:
    // Konsole: Abfrage der Spieleinstellungen (Parameter) als Referenz für StartParams
    // Rückgabewert bestimmt über Spielstart oder Programmende
    bool showMenu(StartParams &params);

    Player showScoreboard();                // Instanziierung und Aufruf der Konsole zur Ausgabe an den Spieler
    
    void displayImage(Image &image);  // Finale Bildausgabe mit OpenCV
};

#endif // GUI_HPP
