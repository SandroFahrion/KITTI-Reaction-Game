// abstrakte klasse mit den spiel-funktionen

#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

#include <chrono>

class GameMode {
public:
    // rein virtuelle Methode, keine Definition mehr nötig. 
    // -> es gibt keinen Spielmodus "Spielmodus"
    virtual void processClick(int x, int y) = 0;

};

#endif // GAME_MODE_HPP
