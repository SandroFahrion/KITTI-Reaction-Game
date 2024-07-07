// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#include "kitti_dataset.hpp"

KittiDataset::KittiDataset(){}  // Standardkonstruktor
KittiDataset::~KittiDataset(){} // Standarddestruktor

KittiDataset::KittiDataset(int seq) :   // überladener Konstruktor
m_seq(seq){}                            // Initializer list


void KittiDataset::loadDataset(const std::string &path) {
    
}

Image KittiDataset::getImage(int index) {
    // Rückgabe des Bildes am angegebenen Index
    
    return {};
}

std::vector<BoundingBox> KittiDataset::getBoundingBoxes(int index) {
    
    return {};
}