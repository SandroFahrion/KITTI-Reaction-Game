// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#ifndef KITTI_DATASET_HPP
#define KITTI_DATASET_HPP

// Quelle für KITTI-Daten
#ifndef PATH_TO_REPO
#define PATH_TO_REPO "C:/Git/KittiReactionGame_Projekt/CPP_Projekt_Klos_Fahrion"
#endif // PATH_TO_REPO

// Pfad zu Bildern
#ifndef PATH_TO_IMAGES
#define PATH_TO_IMAGES "/data/data_tracking_image_2/training/image_02/"
#endif // PATH_TO_IMAGES

// Pfad zu Labels
#ifndef PATH_TO_LABELS
#define PATH_TO_LABELS "/data/data_tracking_label_2/training/label_02/"
#endif // PATH_TO_Labels

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

    KittiDataset(const std::string &seq); // Überladener Konstruktor

    std::string formatImageFilePath(const std::string &baseDir, const std::string &seq);

    std::string formatLabelFilePath(const std::string &baseDir, const std::string &seq);

    void loadDataset(const std::string &baseDir, const std::string &seq); // Beladen der Vektoren m_imagePaths und m_boundingBoxes

    std::string KittiDataset::getImageFilePathOfCurrentIndex();

    BoundingBox KittiDataset::getBoundingBoxOfCurrentIndex();

    // getter-Methode
    int getCurrentIndex() const{ return m_currentIndex; }

    // setter-Methode
    void setCurrentIndex(int index) { m_currentIndex = index; }

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_currentIndex, m_imageFilePaths, m_boundingBoxes)

private:
    int m_currentIndex = 0; // Startwert 0
    std::vector<std::string> m_imageFilePaths;
    std::vector<BoundingBox> m_boundingBoxes;
};

#endif // KITTI_DATASET_HPP
