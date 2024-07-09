// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box 

#include "image.hpp"

Image::Image(){}
Image::~Image(){}

Image::Image(const std::string& imagePath) {
    image = cv::imread(imagePath);
    if (image.empty()) {
        throw std::runtime_error("Could not open or find the image");
    }
}

cv::Mat Image::getImage() const {
    return image;
}

void Image::loadImage(const std::string &path){ 
     
}

void Image::joinDataset(){

}

void Image::setBoundingBoxes(const std::vector<BoundingBox> &boxes){
    
}