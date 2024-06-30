//plan
// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef GUI_HPP
#define GUI_HPP

#include "Image.hpp"
#include <string>

class GUI {
    public:
        StartParams showMenu();
        void displayImage(const Image &image);
};

class StartParams{
    public:
        std::string playerName;
        int numImages;
        std::string sequence;
        int gameMode;

        StartParams(const std::string& name, int num, const std::string& seq, int mode): 
        playerName(name), numImages(num), sequence(seq), gameMode(mode) {}
};

#endif // GUI_HPP
