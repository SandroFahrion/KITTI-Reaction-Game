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
        void loadDataset(const std::string &path);
        Image getImage(size_t index);
        std::vector<BoundingBox> getBoundingBoxes(size_t index);
};

#endif // KITTI_DATASET_HPP
