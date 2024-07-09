// verwaltet das vorbereitete bild des aktuellen datensatzes
// verwaltet die vorbereitete bounding box des aktuellen datensatzes
// zusammensetzen von bild und bounding box

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>

#include "bounding_box.hpp"

#include <opencv2/opencv.hpp>

class Image {
public:
    Image();    // Standardkonstruktor
    ~Image();   // Standarddestruktor
    Image(const std::string& imagePath);    // Überladener Konstruktor

    cv::Mat getImage() const;

    void loadImage(const std::string &path);    // Datensatz muss wahrscheinlich im Projekt zwischengespeichert werden
        
    // setter-Methode
    // wichtig: bestimmt für das aktuelle Bild den Index der zugehörigen Bounding Box, fordert die Daten mit
    // der getter-Methode von der dataset-Klasse an und setzt für das BoundingBox-Objekt die aktuell benötigten Werte
    void setBoundingBoxes(const std::vector<BoundingBox> &boxes);

    void joinDataset(); // Bild und Box zusammenfügen. evtl nicht nötig, wenn es mit GUI displayImage() gut lösbar ist
    
private:
    cv::Mat image;

    int m_images;
    std::string m_filePath;
    std::vector<BoundingBox> m_boundingBoxes;
};

#endif // IMAGE_HPP
