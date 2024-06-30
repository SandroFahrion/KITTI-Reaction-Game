// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#ifndef MODE_1_DIRECTCLICK_HPP
#define MODE_1_DIRECTCLICK_HPP

#include "game_mode.hpp"
#include "player.hpp"

class Mode1DirectClick : public GameMode {
    public:
        void processClick(int x, int y) override;
        void calculateReactionTime();
    
    private:
        Player *player;
        double startTime;
};

#endif MODE_1_DIRECTCLICK_HPP
