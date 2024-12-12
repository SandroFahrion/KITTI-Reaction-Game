// Spielmodus 2 - Color Change Reaction

#ifndef MODE_2_COLOR_CHANGE_HPP
#define MODE_2_COLOR_CHANGE_HPP

#include "game_mode.hpp"

#include "player.hpp"
#include "kitti_dataset.hpp"
#include "../helpers/member_util.hpp"
#include "../helpers/kitti_random.hpp"
#include "../helpers/time.hpp"

class Mode2ColorChange : public GameMode {
public:
    Mode2ColorChange(const StartParams &params, const GUI &gui); // Konstruktor

    bool startGame(const StartParams &params, const GUI &gui) override; // Spielablauf in Schleife

    void processClick(int x, int y) override; // Mauseingabe verarbeiten
    void processKeyPress(int key) override; // Tastatureingabe verarbeiten
    
    static void clickCallback(int event, int x, int y, int flags, void* userdata);

    // getter-Methoden
    const std::vector<BoundingBox> &getBoundingBoxes() const override { return boundingBoxes; };
    int getBoxDisplayCount() const override { return SHOW_ALL_BOXES; }
    cv::Scalar getBoxColor() const override { return BLUE_COLOR; }


    float getTotalReactionTime() const { return m_totalTime; }
private:
    // Member Variablen
    const float m_penaltyTime = 5; // Strafzeit in diesem Spielmodus
    float m_totalTime = 0.0;
    bool m_allowClicks;
    
    int m_turns;
    float m_reactionTime;
    bool m_mouseClicked = false;
    bool m_isKeyPressed = false;
    bool m_isRedBoxShown = false;

    std::vector<BoundingBox> boundingBoxes;
    BoundingBox targetBox;
    Time timer;
    Player m_player;
    const GUI &gui;

};

#endif // MODE_2_COLOR_CHANGE_HPP
