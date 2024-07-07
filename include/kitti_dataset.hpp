// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung



#ifndef KITTI_DATASET_HPP
#define KITTI_DATASET_HPP

#include <string>
#include <vector>
#include <filesystem>

#include "../helpers/member_util.hpp"
#include "bounding_box.hpp"
#include "image.hpp"

class KittiDataset {
public:
    KittiDataset();     // Standardkonstruktor
    ~KittiDataset();    // Standarddestruktor

    KittiDataset(int seq);  // überladener Konstruktor

    void loadDataset(const std::string &path);  // lädt einen Datensatz aus dem Verzeichnis

    //getter-Methoden
    Image getImage(int index);  // Rückgabe eines einzelnen Bildes

    std::vector<BoundingBox> getBoundingBoxes(int index);   // Rückgabe einer einzelnen Bounding Box 

    // Debugging tool
    GENERATE_MEMBER_FUNCTIONS(m_seq)

private:
    int m_seq;
};

#endif // KITTI_DATASET_HPP
