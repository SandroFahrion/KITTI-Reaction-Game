// Sämtliche Funktionen zur Interaktion mit dem Spieler (=User Interface)

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

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

    std::string formatSequenceInput(const std::string &seq); // Benutzereingabe zur Sequenzwahl zur Weiterverarbeitung formatieren

    // Methoden zur Bildausgabe mit Bounding Boxen
    void displayImageWithBoundingBox(const std::string &imagePath, const BoundingBox &box, cv::Scalar color) const;
    void displayImageWithBoundingBoxes(const std::string &imagePath, const std::vector<BoundingBox> &boxes, cv::Scalar color) const;

    void displayImage(const Image &image); // Bildausgabe mit OpenCV (ungenutzt)

    void displayMessage(const std::string &message) const; // Nachricht in der Konsole zeigen

    void displayCountdown(const std::string &message);
    
    // Abfrage der Spieleinstellungen (Startparameter)
    // Rückgabewert bestimmt über Spielstart oder Programmende
    bool showMenu(StartParams &params);

    void showScoreboard(const Player &player) const; // Ausgabe der Spielergebnisse

private:
};

#endif // GUI_HPP
