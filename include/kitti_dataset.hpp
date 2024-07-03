// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#ifndef KITTI_DATASET_HPP
#define KITTI_DATASET_HPP

#include <string>
#include <vector>
#include "bounding_box.hpp"
#include "image.hpp"

class KittiDataset {
    public:
        KittiDataset(int seq);  // Konstruktor
        
        void loadDataset(const std::string &path);  // lädt einen Datensatz aus dem Verzeichnis
        
        Image getImage(int index);   // getter-Methode zur Rückgabe eines einzelnen Bildes (Kapselung, Abstraktion)
        
        std::vector<BoundingBox> getBoundingBoxes(int index);    // getter-Methode zur Rückgabe einer eizelnen Bounding Box (Kapselung, Abstraktion)
    
    private:
        int m_seq;
};

#endif // KITTI_DATASET_HPP
