// umgeformte unterklasse für den Mode 2 - Color Change Reaction

#ifndef MODE_2_COLOR_CHANGE_HPP
#define MODE_2_COLOR_CHANGE_HPP

#include <thread>

#include "game_mode.hpp"

#include "player.hpp"
#include "kitti_dataset.hpp"
#include "../helpers/member_util.hpp"
#include "../helpers/kitti_random.hpp"
#include "../helpers/time.hpp"

class Mode2ColorChange : public GameMode {
public:
    Mode2ColorChange(const StartParams &params, const GUI &gui); // Standardkonstruktor

    bool startGame(const StartParams &params, const GUI &gui) override;
    void startTurn(const std::vector<BoundingBox> &boxes, const GUI &gui);

    void processClick(int x, int y, const GUI &gui) override;
    void processKeyPress(int key) override;

    int getBoxDisplayCount() const override { return SHOW_ALL_BOXES; }
    cv::Scalar getBoxColor() const override { return BLUE_COLOR; }

private:
    int m_turns;
    float m_reactionTime;
    const float m_penaltyTime = 5;
    bool m_isKeyPressed;
    bool m_isRedBoxShown;

    std::vector<BoundingBox> boundingBoxes;
    BoundingBox targetBox;
    Image currentImage;
    Time timer;

};

#endif // MODE_2_COLOR_CHANGE_HPP
