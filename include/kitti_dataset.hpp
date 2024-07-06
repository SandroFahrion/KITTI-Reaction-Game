// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#ifndef KITTI_DATASET_HPP
#define KITTI_DATASET_HPP

#include <string>
#include <vector>
#include <filesystem>

#include "bounding_box.hpp"
#include "image.hpp"

class KittiDataset {
    public:
        KittiDataset();                             // Standardkonstruktor
        KittiDataset(int seq);                      // Konstruktor
        
        void loadDataset(const std::string &path);  // lädt einen Datensatz aus dem Verzeichnis
        
        Image getImage(int index);                  // getter-Methode zur Rückgabe eines einzelnen Bildes (Kapselung, Abstraktion)
        
        std::vector<BoundingBox> getBoundingBoxes(int index);    // getter-Methode zur Rückgabe einer eizelnen Bounding Box (Kapselung, Abstraktion)

        // debugging
        auto getMembers() const {
            return std::make_tuple(m_seq);
        }

        std::vector<std::string> getMemberNames() const {
            return {"m_seq"};
        }

        friend std::ostream& operator<<(std::ostream& os, const KittiDataset& dataset);

    
    private:
        int m_seq;
};

#endif // KITTI_DATASET_HPP
