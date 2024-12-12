// Spielmodus 1 - Direct Click Reaction

#ifndef MODE_1_DIRECT_CLICK_HPP
#define MODE_1_DIRECT_CLICK_HPP

#include "game_mode.hpp"

#include "player.hpp"
#include "kitti_dataset.hpp"
#include "../helpers/member_util.hpp"
#include "../helpers/kitti_random.hpp"
#include "../helpers/time.hpp"

class Mode1DirectClick : public GameMode {
public:
    Mode1DirectClick(const StartParams &params, const GUI &gui); // Konstruktor

    bool startGame(const StartParams &params, const GUI &gui) override; // Spielablauf in Schleife
    
    void processClick(int x, int y) override; // Mauseingabe verarbeiten
    void processKeyPress(int key) override; // Tastatureingabe verarbeiten

    static void clickCallback(int event, int x, int y, int flags, void* userdata);

    // getter-Methoden
    const std::vector<BoundingBox> &getBoundingBoxes() const override { return boundingBoxes; };
    int getBoxDisplayCount() const override { return 1; }
    cv::Scalar getBoxColor() const override { return RED_COLOR; }


    float getTotalReactionTime() const { return m_totalTime; }
    float getPenaltyTime() const { return m_penaltyTime; }
    float getReactionTime() const { return m_reactionTime; }
private:
    // Member Variablen
    const float m_penaltyTime = 5; // Strafzeit in diesem Spielmodus
    int m_missedClicks = 0;
    float m_totalTime = 0.0;
    
    int m_turns;
    float m_reactionTime;
    bool m_mouseClicked = false;

    BoundingBox boundingBox;
    std::vector<BoundingBox> boundingBoxes;
    Time timer;
    Player m_player;
    const GUI &gui;

};

#endif // MODE_1_DIRECT_CLICK_HPP
