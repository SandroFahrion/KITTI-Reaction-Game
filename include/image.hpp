// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "bounding_box.hpp"

class Image : public cv::Mat{
public:
    Image();    // Standardkonstruktor
    ~Image();   // Standarddestruktor

    Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color);    // Überladener Konstruktor für Bilder mit 1 Box

    Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color, int boxAmount) // für Bilder mit mehreren Boxen

    cv::Mat getImage() const;
        
    void setBoundingBoxes(const std::vector<BoundingBox> &boxes);
    
private:
    std::vector<BoundingBox> m_boundingBoxes;
};

#endif // IMAGE_HPP
