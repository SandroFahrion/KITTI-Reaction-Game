// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#ifndef MODE_1_DIRECT_CLICK_HPP
#define MODE_1_DIRECT_CLICK_HPP

#include <chrono>
#include <vector>
#include "game_mode.hpp"
#include "player.hpp"
#include "bounding_box.hpp"

class Mode1DirectClick : public GameMode {
public:
    Mode1DirectClick();

    void startRound(const Image& img, const std::vector<BoundingBox>& boxes) override;

    void processClick(int x, int y) override;
    void processKeyPress(int key) override;

    const std::vector<BoundingBox>& getBoundingBoxes() const override;
    const Image& getCurrentImage() const override;

    int getBoxDisplayCount() const override { return 1; }
    cv::Scalar getBoxColor() const override { return RED_COLOR; }

private:
    const float m_penaltyTime = 5;
    float m_reactionTime;
    std::chrono::high_resolution_clock::time_point m_startTime;

    BoundingBox boundingBox;
    std::vector<BoundingBox> boundingBoxes;
    Image currentImage;

    float calculateReactionTime();
};

#endif // MODE_1_DIRECT_CLICK_HPP
