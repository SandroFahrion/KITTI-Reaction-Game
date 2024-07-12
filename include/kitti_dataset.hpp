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

    KittiDataset(const std::string &baseDir, const std::string &seq); // Überladener Konstruktor

    std::string formatImageFilePath(const std::string &baseDir, const std::string &seq);

    std::string formatLabelFilePath(const std::string &baseDir, const std::string &seq);

    void loadDataset(const std::string &baseDir, const std::string &seq); // Beladen der Vektoren m_imagePaths und m_boundingBoxes

    std::string KittiDataset::getImageFilePathOfCurrentIndex();

    BoundingBox KittiDataset::getBoundingBoxOfCurrentIndex();

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_seq)

private:
    int m_seq;
    int m_currentIndex = 0; // Startwert 0
    std::vector<std::string> m_imageFilePaths;
    std::vector<BoundingBox> m_boundingBoxes;
};

#endif // KITTI_DATASET_HPP
