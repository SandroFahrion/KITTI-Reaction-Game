// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

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
    Mode1DirectClick(const StartParams &params, const GUI &gui);

    bool startGame(const StartParams &params, const GUI &gui) override;
    void startTurn(const Image &img, const std::vector<BoundingBox> &boxes, const GUI &gui) override;

    void processClick(int x, int y, const GUI &gui);
    void processKeyPress(int key) override;

    const std::vector<BoundingBox> &getBoundingBoxes() const override { return boundingBoxes; };
    const Image &getCurrentImage() const override { return currentImage; };
    int getBoxDisplayCount() const override { return 1; }
    cv::Scalar getBoxColor() const override { return RED_COLOR; }

private:
    int m_turns;
    const float m_penaltyTime = 5;
    float m_reactionTime;

    BoundingBox boundingBox;
    std::vector<BoundingBox> boundingBoxes;
    Image currentImage;
    Time timer;

};

#endif // MODE_1_DIRECT_CLICK_HPP
