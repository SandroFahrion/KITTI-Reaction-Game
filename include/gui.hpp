// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef GUI_HPP
#define GUI_HPP

#include "image.hpp"
#include <string>
#include <iostream>
#include "player.hpp"
/*
#include <opencv/include/opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
*/
class GUI {
    public:
        StartParams showMenu();                     // Instanziierung und Aufruf der Konsole als Menü, zur Abfrage der Spieleinstellungen und Ausgabe
        Player showScoreboard();                    // Instanziierung und Aufruf der Konsole zur Ausgabe an den Spieler
        void displayImage(const Image &image);      // Finale Bildausgabe mit OpenCV
};

class StartParams{
    StartParams(const std::string &name, int num, const std::string &seq, int mode); // Überladener Konstruktor
    public:
        std::string m_playerName;
        int m_numImages;
        std::string m_sequence;
        int m_gameMode;
};

#endif // GUI_HPP
