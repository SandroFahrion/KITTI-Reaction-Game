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

    void startTurn(const std::vector<BoundingBox> &boxes, const GUI &gui); // Spielzug, Verarbeitung von Spieler-Input

    void processClick(int x, int y, const GUI &gui) override; // Mauseingabe verarbeiten
    void processKeyPress(int key) override; // Tastatureingabe verarbeiten

    // getter-Methoden
    const std::vector<BoundingBox> &getBoundingBoxes() const override { return boundingBoxes; };
    int getBoxDisplayCount() const override { return SHOW_ALL_BOXES; }
    cv::Scalar getBoxColor() const override { return BLUE_COLOR; }

private:
    const float m_penaltyTime = 5; // Strafzeit in diesem Spielmodus

    // Member Variablen
    int m_turns;
    float m_reactionTime;
    bool m_isKeyPressed;
    bool m_isRedBoxShown;

    std::vector<BoundingBox> boundingBoxes;
    BoundingBox targetBox;
    Time timer;

};

#endif // MODE_2_COLOR_CHANGE_HPP
