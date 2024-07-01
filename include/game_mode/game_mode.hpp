// abstrakte klasse mit den spiel-funktionen

#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

class GameMode {
    public:
        virtual void processClick(int x, int y) = 0;    // *rein* virtuelle Methode, keine Definition mehr nötig. 
                                                        // -> es gibt keinen Spielmodus "Spielmodus"
};

#endif // GAME_MODE_HPP
