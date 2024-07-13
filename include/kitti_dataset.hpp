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
#include <random>

#include "../helpers/member_util.hpp"
#include "bounding_box.hpp"


class KittiDataset {
public:
    KittiDataset();     // Standardkonstruktor
    ~KittiDataset();    // Standarddestruktor

    KittiDataset(const std::string &seq); // Überladener Konstruktor

    std::string KittiDataset::getImageFilePathOfCurrentIndex();
    std::vector<BoundingBox> KittiDataset::getBoundingBoxesOfCurrentFrame(); // Methode zum Abrufen der Bounding Boxes des aktuellen Frames


    // getter-Methoden
    int getCurrentIndex() const{ return m_currentIndex; }
    int getTotalImages() const { return static_cast<int>(m_imageFilePaths.size()); }

    // setter-Methode
    void setCurrentIndex(int index) { m_currentIndex = index; }

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_currentIndex, m_imageFilePaths, m_boundingBoxes)

private:
    // Member Variablen
    int m_currentIndex = 0;
    std::vector<std::string> m_imageFilePaths;
    std::vector<BoundingBox> m_boundingBoxes;

    // Beladen der Vektoren m_imagePaths und m_boundingBoxes
    void loadDataset(const std::string &seq);
    void loadImagePaths(const std::string &seq);
    void loadBoxDataset(const std::string &seq);

    void setRandomStartIndex();
    std::string formatImageFilePath(int index, const std::string &seq);
    std::string formatLabelFilePath(const std::string &seq);
};

#endif // KITTI_DATASET_HPP
