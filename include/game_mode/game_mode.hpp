// abstrakte klasse mit den spiel-funktionen

#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

#include <chrono>
#include <vector>

#include <opencv2/opencv.hpp>

#include "bounding_box.hpp"
#include "gui.hpp"
#include "image.hpp"

const int SHOW_ALL_BOXES = -1;

const cv::Scalar BLUE_COLOR(255, 0, 0);
const cv::Scalar RED_COLOR(0, 0, 255);

class GameMode {
public:

    virtual ~GameMode() = default;

    virtual bool startGame(const StartParams &params, const GUI &gui) = 0;
    virtual void startTurn(const Image &img, const std::vector<BoundingBox> &boxes) = 0;

    virtual void processClick(int x, int y) = 0;
    virtual void processKeyPress(int key) = 0;
    virtual const std::vector<BoundingBox> &getBoundingBoxes() const = 0;
    virtual const Image &getCurrentImage() const = 0;
    virtual int getBoxDisplayCount() const = 0;
    virtual cv::Scalar getBoxColor() const = 0;
};

#endif // GAME_MODE_HPP
