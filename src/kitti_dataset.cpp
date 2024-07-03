// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#include "kitti_dataset.hpp"

KittiDataset::KittiDataset(int seq) :       // Konstruktor
m_seq(seq){ // Initializer list

}

void KittiDataset::loadDataset(const std::string &path) {   // 
    
}

Image KittiDataset::getImage(int index) {
    // Rückgabe des Bildes am angegebenen Index
    return {};
    //return images.at(index); // 'at' verwendet, um eine Grenzenüberprüfung durchzuführen
}

std::vector<BoundingBox> KittiDataset::getBoundingBoxes(int index) {
    
    return {};
    //return images.at(index).getBoundingBoxes();
}
