// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <chrono>

#include <opencv2/opencv.hpp>

#include "image.hpp"
#include "bounding_box.hpp"
#include "player.hpp"
#include "../helpers/member_util.hpp"

class StartParams {
public:
    StartParams();  // Standardkonstruktor
    ~StartParams(); // Standarddestruktor

    StartParams(const std::string &name, int turns, int seq, int mode); // Überladener Konstruktor

    // getter-Methoden
    int getNumTurns() const{ return m_numTurns; }
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
    // Startparameter
    std::string m_playerName;
    int m_numTurns, m_gameMode, m_sequence;
    
};

class GUI {
public:
    GUI();  // Standardkonstruktor
    ~GUI(); // Standarddestruktor

    void displayImageWithBoundingBox(const Image& img, const BoundingBox& box);
    void displayImage(Image &image);  // Finale Bildausgabe mit OpenCV

    double measureReactionTime(int& key, cv::Point& cursorPos);

    // Konsole: Abfrage der Spieleinstellungen (Parameter) als Referenz für StartParams
    // Rückgabewert bestimmt über Spielstart oder Programmende
    bool showMenu(StartParams &params);

    Player showScoreboard();    // Instanziierung und Aufruf der Konsole zur Ausgabe an den Spieler

private:
    // zur Berechnung der Reaktionszeit
    std::chrono::high_resolution_clock::time_point startTime;    
};

#endif // GUI_HPP
