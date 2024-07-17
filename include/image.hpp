// Erstellung der Bilder

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

    Image &operator=(const cv::Mat &mat);  // Zuweisungsoperator der cv::Mat akzeptiert

    // Überladener Konstruktor für Bilder mit 1 Box
    Image(const std::string &imagePath, const BoundingBox &box, cv::Scalar color);

    // für Bilder mit mehreren Boxen
    Image(const std::string &imagePath, const std::vector<BoundingBox> &boxes, cv::Scalar color);

    // Überladener Konstruktor für Bilder mit mehreren Boxen in verschiedenen Farben
    Image(const std::string &imagePath, const std::vector<BoundingBox> &redBoxes, cv::Scalar redColor, const std::vector<BoundingBox> &blueBoxes, cv::Scalar blueColor);
    
private:
    std::vector<BoundingBox> m_boundingBoxes; // Enthält Informationen zu validen Bounding Boxen

    void drawBoundingBoxes(const std::vector<BoundingBox> &boxes, cv::Scalar color); // Methode, welche die Bounding Boxen ins Bild malt
};

#endif // IMAGE_HPP
