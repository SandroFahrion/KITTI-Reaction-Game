// Organisiert Dateizugriffe auf die Datensätze

#ifndef KITTI_DATASET_HPP
#define KITTI_DATASET_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../helpers/member_util.hpp"
#include "../helpers/kitti_random.hpp"
#include "bounding_box.hpp"


class KittiDataset {
public:
    KittiDataset();     // Standardkonstruktor
    ~KittiDataset();    // Standarddestruktor

    KittiDataset(const std::string &seq); // Überladener Konstruktor

    std::string KittiDataset::getImageFilePathOfCurrentIndex(); // Methode, die den Pfad zum Bild des aktuellen Indexes zurückgibt
    std::vector<BoundingBox> KittiDataset::getBoundingBoxesOfCurrentFrame(); // Methode, die alle validen Boxen des aktuellen Indexes zurückgibt

    void incrementCurrentIndex() { m_currentIndex++; };

    // getter-Methoden
    int getCurrentIndex() const{ return m_currentIndex; }
    int getTotalImages() const { return static_cast<int>(m_imageFilePaths.size()); }

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_currentIndex, m_imageFilePaths, m_boundingBoxes)

private:
    // setter-Methode
    void setCurrentIndex(int index) { m_currentIndex = index; }

    // Member Variablen
    int m_currentIndex = 0;
    std::vector<std::string> m_imageFilePaths;
    std::vector<BoundingBox> m_boundingBoxes;

    // Beladen der Vektoren m_imagePaths und m_boundingBoxes
    void loadDataset(const std::string &seq);
    void loadImagePaths(const std::string &seq);
    void loadBoxDataset(const std::string &seq);

    void setRandomStartIndex(); // Methode, die den Startindex zufällig wählt

    // Zur korrekten Formatierung der Dateipfade
    std::string formatImageFilePath(int index, const std::string &seq);
    std::string formatLabelFilePath(const std::string &seq);

    KittiRandom random; // Objekt zur Nutzung der Random-Methoden
};

#endif // KITTI_DATASET_HPP
