// Erstellung der Bilder

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "image.hpp"

Image::Image() : cv::Mat() {}   // Standardkonstruktor
Image::~Image() {}              // Standarddestruktor

Image &Image::operator=(const cv::Mat& mat) {
    if (this != &mat) {
        // Zuweisungsoperator verwenden
        cv::Mat::operator=(mat);
    }
    return *this;
}

// Überladener Konstruktor für Bilder mit 1 Box
Image::Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color) {
    *this = cv::imread(imagePath);

    if (!this->empty()) {
        // Box erstellen
        cv::rectangle(*this, cv::Point(box.getCoordX(), box.getCoordY()), 
                      cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);

        // Boxtyp als Text hinzufügen
        std::string boxType = box.getType();
        cv::putText(*this, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    } 
    #ifdef DEBUG_MODE
        else if (g_debug_mode) Debugger::log(imagePath, "ERROR loading image");
    #endif // DEBUG_MODE
}

// Überladener Konstruktor für Bilder mit mehreren Boxen
Image::Image(const std::string &imagePath, const std::vector<BoundingBox> &boxes, cv::Scalar color){
    *this = cv::imread(imagePath);

    // Vektor an die Methode zum Erstellen aller Boxen in dieser Farbe übergeben
    if (!this->empty()) {
        this->drawBoundingBoxes(boxes, color);
    }
    #ifdef DEBUG_MODE
        else if (g_debug_mode) Debugger::log(imagePath, "ERROR loading image");
    #endif // DEBUG_MODE
}

// Überladener Konstruktor für Bilder mit mehreren Boxen in verschiedenen Farben
Image::Image(const std::string &imagePath, const std::vector<BoundingBox> &redBoxes, cv::Scalar redColor, const std::vector<BoundingBox> &blueBoxes, cv::Scalar blueColor) {
    *this = cv::imread(imagePath);

    // Vektoren an die Methode zum Erstellen aller Boxen in den jeweiligen Farben übergeben
    if (!this->empty()) {
        this->drawBoundingBoxes(blueBoxes, blueColor); // Zeichne zuerst die blauen Boxen
        this->drawBoundingBoxes(redBoxes, redColor);   // Zeichne dann die roten Boxen
    }
    #ifdef DEBUG_MODE
        else if (g_debug_mode) Debugger::log(imagePath, "ERROR loading image");
    #endif // DEBUG MODE
}


void Image::drawBoundingBoxes(const std::vector<BoundingBox> &boxes, cv::Scalar color) {
    for (const auto &box : boxes) {
        // Box erstellen
        cv::rectangle(*this, cv::Point(box.getCoordX(), box.getCoordY()), 
                      cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);

        // Boxtyp als Text hinzufügen
        std::string boxType = box.getType();
        cv::putText(*this, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    }
}
