// Abstrakte Oberklasse für die Spielmodi
// keine Implementierung / Definiton von Methoden, da kein Spielmodus "Spielmodus" existiert

#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

#include <vector>

#include <opencv2/opencv.hpp>

#include "bounding_box.hpp"
#include "gui.hpp"
#include "image.hpp"

const int SHOW_ALL_BOXES = -1;

const cv::Scalar BLUE_COLOR(255, 0, 0);     // Definition der Farbe Blau
const cv::Scalar GREEN_COLOR(0, 255, 0);    // Definition der Farbe Grün
const cv::Scalar RED_COLOR(0, 0, 255);      // Definition der Farbe Rot

class GameMode {
public:
    virtual ~GameMode() = default;

    virtual bool startGame(const StartParams &params, const GUI &gui) = 0; // Spielablauf in Schleife

    virtual void processClick(int x, int y, const GUI &gui) = 0; // Mauseingabe verarbeiten
    virtual void processKeyPress(int key) = 0; // Tastatureingabe verarbeiten
    
    // getter-Methoden
    virtual const std::vector<BoundingBox> &getBoundingBoxes() const = 0;
    virtual int getBoxDisplayCount() const = 0;
    virtual cv::Scalar getBoxColor() const = 0;
};

#endif // GAME_MODE_HPP
