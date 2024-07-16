// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include "image.hpp"
#include "bounding_box.hpp"
#include "player.hpp"
#include "../helpers/member_util.hpp"

class StartParams {
public:
    StartParams();  // Standardkonstruktor
    ~StartParams(); // Standarddestruktor

    StartParams(const std::string &name, int turns, const std:: string &seq, int mode); // Überladener Konstruktor

    // getter-Methoden
    int getNumTurns() const{ return m_numTurns; }
    int getGameMode() const{ return m_gameMode; }
    const std::string &getPlayerName() const { return m_playerName; }
    const std::string &getSequence() const { return m_sequence; }

    // setter-Methoden
    void setNumTurns(int numTurns) { m_numTurns = numTurns; }
    void setGameMode(int gameMode) { m_gameMode = gameMode; }
    void setPlayerName(const std::string &playerName) { m_playerName = playerName; }
    void setSequence(const std::string &sequence) { m_sequence = sequence; }

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_numTurns, m_gameMode, m_sequence, m_playerName)

private:
    // Startparameter
    std::string m_playerName, m_sequence;
    int m_numTurns, m_gameMode;
    
};

class GUI {
public:
    GUI();  // Standardkonstruktor
    ~GUI(); // Standarddestruktor

    std::string formatSequenceInput(const std::string &seq);

    void displayImageWithBoundingBox(const Image &img, const BoundingBox &box, cv::Scalar color) const;
    void displayImageWithBoundingBoxes(const Image &img, const std::vector<BoundingBox> &boxes, cv::Scalar color) const;

    void displayImage(Image &image);  // Finale Bildausgabe mit OpenCV

    void displayCountdown(const std::string &message);
    void displayMessage(const std::string &message);

    // Konsole: Abfrage der Spieleinstellungen (Parameter) als Referenz für StartParams
    // Rückgabewert bestimmt über Spielstart oder Programmende
    bool showMenu(StartParams &params);

    Player showScoreboard();    // Instanziierung und Aufruf der Konsole zur Ausgabe an den Spieler

private:
};

#endif // GUI_HPP
