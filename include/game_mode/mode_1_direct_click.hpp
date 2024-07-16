// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#ifndef MODE_1_DIRECT_CLICK_HPP
#define MODE_1_DIRECT_CLICK_HPP

#include <chrono>
#include <vector>
#include <iostream>

#include "game_mode.hpp"
#include "player.hpp"
#include "bounding_box.hpp"
#include "kitti_dataset.hpp"
#include "gui.hpp"
#include "image.hpp"
#include "../helpers/member_util.hpp"
#include "../helpers/kitti_random.hpp"

class Mode1DirectClick : public GameMode {
public:
    Mode1DirectClick(const StartParams &params, const GUI &gui);

    bool startGame(const StartParams &params, const GUI &gui) override;
    void startTurn(const Image &img, const std::vector<BoundingBox> &boxes) override;

    void processClick(int x, int y) override;
    void processKeyPress(int key) override;

    const std::vector<BoundingBox> &getBoundingBoxes() const override;
    const Image &getCurrentImage() const override;

    int getBoxDisplayCount() const override { return 1; }
    cv::Scalar getBoxColor() const override { return RED_COLOR; }

private:
    int m_turns;
    const float m_penaltyTime = 5;
    float m_reactionTime;
    std::chrono::high_resolution_clock::time_point m_startTime;

    BoundingBox boundingBox;
    std::vector<BoundingBox> boundingBoxes;
    Image currentImage;

    float calculateReactionTime();
};

#endif // MODE_1_DIRECT_CLICK_HPP
