//Spielmodus 3 - Memory

#ifndef MODE_3_MEMORY_HPP
#define MODE_3_MEMORY_HPP

#include "game_mode.hpp"

#include "player.hpp"
#include "kitti_dataset.hpp"
#include "../helpers/member_util.hpp"
#include "../helpers/kitti_random.hpp"
#include "../helpers/time.hpp"

class Mode3Memory : public GameMode {
public:
    Mode3Memory(const StartParams &params, const GUI &gui); // Konstruktor

    bool startGame(const StartParams &params, const GUI &gui) override; // Spielablauf in Schleife

    void processClick(int x, int y) override; // Mauseingabe verarbeiten
    void processKeyPress(int key) override; // Tastatureingabe verarbeiten
    
    static void clickCallback(int event, int x, int y, int flags, void* userdata);

    // getter-Methoden
    const std::vector<BoundingBox> &getBoundingBoxes() const override { return boundingBoxes; };
    int getBoxDisplayCount() const override { return SHOW_ALL_BOXES; }
    cv::Scalar getBoxColor() const override { return BLUE_COLOR; }

private:
    std::vector<BoundingBox> m_sequence; // Sequenz der Boxen
    int m_sequenceIndex; // Aktuelle Position in der Sequenz

    // Member Variablen
    const float m_penaltyTime = 5; // Strafzeit in diesem Spielmodus
    int m_missedClicks = 0;
    float m_totalTime = 0.0;

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

    //init round

};

#endif // MODE_3_MEMORY_HPP