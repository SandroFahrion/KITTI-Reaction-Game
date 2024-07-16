// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box 

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "image.hpp"

Image::Image() : cv::Mat() {}
Image::~Image() {}

Image::Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color) {
    *this = cv::imread(imagePath);

    if (!this->empty()) {
        cv::rectangle(*this, cv::Point(box.getCoordX(), box.getCoordY()), 
                      cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);

        // add box type as plain text
        std::string boxType = box.getType();
        cv::putText(*this, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    } 
    #ifdef DEBUG_MODE
        else {
            if (g_debug_mode) Debugger::log(imagePath, "ERROR loading image");
        }
    #endif // DEBUG_MODE
}

Image::Image(const std::string &imagePath, const std::vector<BoundingBox> &boxes, cv::Scalar color){
    *this = cv::imread(imagePath);

    if (!this->empty()) {
        this->drawBoundingBoxes(boxes, color);
    }
    #ifdef DEBUG_MODE
        else {
            if (g_debug_mode) Debugger::log(imagePath, "ERROR loading image");
        }
    #endif // DEBUG_MODE
}

void Image::drawBoundingBoxes(const std::vector<BoundingBox> &boxes, cv::Scalar color) {
    for (const auto &box : boxes) {
        cv::rectangle(*this, cv::Point(box.getCoordX(), box.getCoordY()), 
                      cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);
        std::string boxType = box.getType();
        cv::putText(*this, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    }
}

// void Image::setBoundingBoxes(const std::vector<BoundingBox> &boxes) {
//     if (!this->empty()) {
//         drawBoundingBoxes(boxes, cv::Scalar(0, 0, 255));
//     }
// }