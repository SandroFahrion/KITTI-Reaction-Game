// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#include "kitti_dataset.hpp"

void KittiDataset::loadDataset(const std::string &path) {
    
}

Image KittiDataset::getImage(size_t index) {
    // Rückgabe des Bildes am angegebenen Index
    //return images.at(index); // 'at' verwendet, um eine Grenzenüberprüfung durchzuführen
}

std::vector<BoundingBox> KittiDataset::getBoundingBoxes(size_t index) {

    //return images.at(index).getBoundingBoxes();
}
