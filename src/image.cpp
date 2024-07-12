// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box 

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "image.hpp"

Image::Image(){}
Image::~Image(){}

Image::Image(const std::string &imagePath) {
    m_cv_image = cv::imread(imagePath);
    
    #ifdef DEBUG_MODE
        if (g_debug_mode) {
            if (m_cv_image.empty()) Debugger::log(imagePath, "ERROR loading image");
        }
    #endif // DEBUG_MODE
}

cv::Mat Image::getImage() const {
    return m_cv_image;
}

void Image::joinDataset(){

}

void Image::setBoundingBoxes(const std::vector<BoundingBox> &boxes){
    
}