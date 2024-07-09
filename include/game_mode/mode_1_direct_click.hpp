// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#ifndef MODE_1_DIRECT_CLICK_HPP
#define MODE_1_DIRECT_CLICK_HPP

#include "game_mode.hpp"
#include "player.hpp"
#include "bounding_box.hpp"

#include <chrono>

class Mode1DirectClick : public GameMode {
public:
    Mode1DirectClick();
    void processClick(int x, int y) override;
    double calculateReactionTime();
    
private:
    BoundingBox boundingBox;
    double reactionTime;
    double penaltyTime;
    std::chrono::high_resolution_clock::time_point startTime;

};

#endif // MODE_1_DIRECT_CLICK_HPP
