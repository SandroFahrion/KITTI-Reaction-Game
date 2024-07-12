// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#include "kitti_dataset.hpp"

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

KittiDataset::KittiDataset(){}  // Standardkonstruktor
KittiDataset::~KittiDataset(){} // Standarddestruktor

std::string KittiDataset::formatImageFilePath(const std::string &baseDir, const std::string &seq){
    std::string reFormattedSeq;

    reFormattedSeq.erase(0, reFormattedSeq.find_first_not_of('0')); // Entferne führende Nullen (für Eingabe Bsp.:"0000010")
    
    // Wenn das Ergebnis leer ist (d.h. es wurde der 0. Datensatz gewählt), setze es auf "0"
    if (reFormattedSeq.empty()) {
        reFormattedSeq = "0";
    }

    // Variable wird mit führenden Nullen aufgefüllt
    if (reFormattedSeq.size() < 6) {
        reFormattedSeq.insert(reFormattedSeq.begin(), 6 - reFormattedSeq.size(), '0');
    }

    std::string formattedImageFilePath = baseDir + "/data/data_tracking_image_2/training/image_02/" + seq + "/" + reFormattedSeq + ".png";

    return formattedImageFilePath;
}

std::string KittiDataset::formatLabelFilePath(const std::string &baseDir, const std::string &seq){
    std::string formattedLabelFilePath = baseDir + "/data/data_tracking_label_2/training/label_02/" + seq + ".txt";

    return formattedLabelFilePath;
}

KittiDataset::KittiDataset(const std::string &baseDir, const std::string &seq) {
    loadDataset(baseDir, seq);
}

void KittiDataset::loadDataset(const std::string &baseDir, const std::string &seq) {

    std::ifstream file(formatLabelFilePath(baseDir, seq));

    #ifdef DEBUG_MODE
        if (g_debug_mode) {
            if (!file.is_open()) Debugger::log(formatLabelFilePath(baseDir, seq), "Could not open label file: ");
        }
    #endif // DEBUG_MODE

    std::string line;

    while (std::getline(file, line)) {

        #ifdef DEBUG_MODE
            if (g_debug_mode) {
                Debugger::log(line, "Reading line: ");
            }
        #endif // DEBUG_MODE

        std::stringstream iss(line);

        int x, y, width, height;

        if (!(iss >> m_currentIndex >> x >> y >> width >> height)) {
            #ifdef DEBUG_MODE
                if (g_debug_mode) {
                    Debugger::log(line, "ERROR parsing line: ");
                }
            #endif // DEBUG_MODE
        }

        m_imageFilePaths.push_back(formatImageFilePath(baseDir, seq));
        m_boundingBoxes.emplace_back(x, y, width, height);
    }

    file.close();
}

std::string KittiDataset::getImageFilePathOfCurrentIndex() {
    m_currentIndex = m_currentIndex % m_imageFilePaths.size();
    return m_imageFilePaths[m_currentIndex];
}

BoundingBox KittiDataset::getBoundingBoxOfCurrentIndex() {
    return m_boundingBoxes[m_currentIndex];
}