// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung



#ifndef KITTI_DATASET_HPP
#define KITTI_DATASET_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../helpers/member_util.hpp"
#include "bounding_box.hpp"
#include "image.hpp"

class KittiDataset {
public:
    KittiDataset();     // Standardkonstruktor
    ~KittiDataset();    // Standarddestruktor

    KittiDataset(int seq);  // überladener Konstruktor
    KittiDataset(const std::string& imageDir, const std::string& labelFile); // Überladener KOnstruktor

    //void loadDataset(const std::string &path);  // lädt einen Datensatz aus dem Verzeichnis
    void KittiDataset::loadDataset(const std::string& imageDir, const std::string& labelFile);

    //getter-Methoden
    std::string KittiDataset::getNextImage();

    BoundingBox KittiDataset::getBoundingBox();   // Rückgabe einer einzelnen Bounding Box 

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_seq)

private:
    int m_seq;
    int currentIndex;
    std::vector<std::string> imagePaths;
    std::vector<BoundingBox> boundingBoxes;
};

#endif // KITTI_DATASET_HPP
