// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>

#include "image.hpp"
#include "player.hpp"
#include "../helpers/member_util.hpp"

class StartParams {
public:
    StartParams();  // Standardkonstruktor
    ~StartParams(); // Standarddestruktor

    StartParams(const std::string &name, int turns, int seq, int mode); // Überladener Konstruktor

    // getter-Methoden
    int getNumTurns() const { return m_numTurns; }
    const std::string& getPlayerName() const { return m_playerName; }
    int getGameMode() const{ return m_gameMode; }
    int getSequence() const { return m_sequence; }

    // setter-Methoden
    void setNumTurns(int numTurns) { m_numTurns = numTurns; }
    void setPlayerName(const std::string &playerName) { m_playerName = playerName; }
    void setGameMode(int gameMode) { m_gameMode = gameMode; }
    void setSequence(int sequence) { m_sequence = sequence; }

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_numTurns, m_gameMode, m_sequence, m_playerName)

private:
    // Member-Variablen
    std::string m_playerName;
    int m_numTurns, m_gameMode, m_sequence;
};

class GUI {
public:
    GUI();  // Standardkonstruktor
    ~GUI(); // Standarddestruktor

    // Konsole: Abfrage der Spieleinstellungen (Parameter) als Referenz für StartParams
    // Rückgabewert bestimmt über Spielstart oder Programmende
    bool showMenu(StartParams &params);

    Player showScoreboard();    // Instanziierung und Aufruf der Konsole zur Ausgabe an den Spieler
    
    void displayImage(Image &image);  // Finale Bildausgabe mit OpenCV
};

#endif // GUI_HPP
