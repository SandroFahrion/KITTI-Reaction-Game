// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "bounding_box.hpp"

class Image {
public:
    Image();    // Standardkonstruktor
    ~Image();   // Standarddestruktor

    Image(const std::string &imagePath);    // Überladener Konstruktor, liest das Bild vom Pfad in openCV ein

    cv::Mat getImage() const;
        
    void setBoundingBoxes(const std::vector<BoundingBox> &boxes);
    
private:
    cv::Mat m_cv_image;
    std::vector<BoundingBox> m_boundingBoxes;
};

#endif // IMAGE_HPP
