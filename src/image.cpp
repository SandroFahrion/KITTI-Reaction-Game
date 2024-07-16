// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box 

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "image.hpp"

Image::Image(){}
Image::~Image(){}

Image::Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color) {
    
    cv::Mat m_cv_image = cv::imread(imagePath);
    
    #ifdef DEBUG_MODE
        if (g_debug_mode) {
            if (m_cv_image.empty()) Debugger::log(imagePath, "ERROR loading image");
        }
    #endif // DEBUG_MODE

    cv::rectangle(m_cv_image, cv::Point(box.getCoordX(), box.getCoordY()), cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);

    // add box type as plain text
    std::string boxType = box.getType();
    cv::putText(m_cv_image, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);

}

Image::Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color, int boxCount){
    m_cv_image = cv::imread(imagePath);

    for(int i = 0; i <= boxCount; i++){
        cv::rectangle(m_cv_image, cv::Point(box.getCoordX(), box.getCoordY()), cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);
        
        // add box type as plain text
        std::string boxType = box.getType();
        cv::putText(m_cv_image, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    }
}

cv::Mat Image::getImage() const {
    return m_cv_image;
}

void Image::setBoundingBoxes(const std::vector<BoundingBox> &boxes) {
    m_boundingBoxes = boxes;
}