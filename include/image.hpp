// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>
#include "bounding_box.hpp"

class Image {
    public:
        void loadImage(const std::string &path);
        void display();
        void setBoundingBoxes(const std::vector<BoundingBox> &boxes);
    
    private:
        std::string filePath;
        std::vector<BoundingBox> boundingBoxes;
};

#endif // IMAGE_HPP
