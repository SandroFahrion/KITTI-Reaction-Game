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

class StartParams{
    public:
        StartParams(const std::string &name, int num, int seq, int mode); // Überladener Konstruktor
        std::string m_playerName;
        int m_numImages, m_gameMode, m_sequence;
};

class GUI {
    public:
        // Konsole: Abfrage der Spieleinstellungen (Parameter) als Referenz für StartParams
        // Rückgabewert bestimmt über Spielstart oder Programmende
        bool showMenu(StartParams &params);

        Player showScoreboard();    // Instanziierung und Aufruf der Konsole zur Ausgabe an den Spieler
        void displayImage(const Image &image);      // Finale Bildausgabe mit OpenCV
};

#endif // GUI_HPP
