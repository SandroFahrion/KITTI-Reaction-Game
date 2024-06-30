// abstrakte klasse mit den spiel-funktionen

#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

class GameMode {
    public:
        virtual void processClick(int x, int y) = 0;
};

#endif GAME_MODE_HPP
