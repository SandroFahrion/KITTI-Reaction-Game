// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#include "kitti_dataset.hpp"

KittiDataset::KittiDataset(){}  // Standardkonstruktor
KittiDataset::~KittiDataset(){} // Standarddestruktor

KittiDataset::KittiDataset(int seq) :   // überladener Konstruktor
m_seq(seq){}                            // Initializer list

KittiDataset::KittiDataset(const std::string& imageDir, const std::string& labelFile) {
    currentIndex = -1;
    loadDataset(imageDir, labelFile);
}


// void KittiDataset::loadDataset(const std::string &path) {}

void KittiDataset::loadDataset(const std::string& imageDir, const std::string& labelFile) {
    std::ifstream file(labelFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open label file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream iss(line);
        std::string imagePath;
        int x, y, width, height;

        // Beispielhafte Extraktion der Daten
        iss >> imagePath >> x >> y >> width >> height;
        imagePaths.push_back(imageDir + "/" + imagePath);
        boundingBoxes.emplace_back(x, y, width, height);
    }

    file.close();
}

std::string KittiDataset::getNextImage() {
    currentIndex = (currentIndex + 1) % imagePaths.size();
    return imagePaths[currentIndex];
}

BoundingBox KittiDataset::getBoundingBox() {
    return boundingBoxes[currentIndex];
}