// umgeformte unterklasse für den Mode 2 - Color Change Reaction

#ifndef MODE_2_COLOR_CHANGE_HPP
#define MODE_2_COLOR_CHANGE_HPP

#include <chrono>
#include <vector>
#include "game_mode.hpp"
#include "player.hpp"
#include "bounding_box.hpp"

class Mode2ColorChange : public GameMode {
public:
    Mode2ColorChange(); // Standardkonstruktor

    void startRound(const Image& img, const std::vector<BoundingBox>& boxes) override;

    void processClick(int x, int y) override;
    void processKeyPress(int key) override;

    const std::vector<BoundingBox>& getBoundingBoxes() const override;
    const Image& getCurrentImage() const override;

    int getBoxDisplayCount() const override { return SHOW_ALL_BOXES; }
    cv::Scalar getBoxColor() const override { return BLUE_COLOR; }

private:
    float m_reactionTime;
    const float m_penaltyTime = 5;
    std::chrono::high_resolution_clock::time_point m_startTime;
    bool m_isKeyPressed;
    bool m_isRedBoxShown;

    std::vector<BoundingBox> boundingBoxes;
    BoundingBox targetBox;
    Image currentImage;

    float calculateReactionTime();
};

#endif // MODE_2_COLOR_CHANGE_HPP
