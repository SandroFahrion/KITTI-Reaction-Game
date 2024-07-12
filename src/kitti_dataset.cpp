// verwalten und vorbereiten des gesamten datensatzes
// zugriff auf das verzeichnis von kitti
// stellt einzelne bildobjekte für die weitere verarbeitung im spiel zur verfügung

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "kitti_dataset.hpp"

KittiDataset::KittiDataset(){}  // Standardkonstruktor
KittiDataset::~KittiDataset(){} // Standarddestruktor
KittiDataset::KittiDataset(const std::string &seq) {    // Überladener Konstruktor
    loadDataset(PATH_TO_REPO, seq);
}

std::string KittiDataset::formatImageFilePath(const std::string &repoDir, const std::string &seq){
    std::string formattedIndex = std::to_string(m_currentIndex);
    formattedIndex.erase(0, formattedIndex.find_first_not_of('0')); // Entferne führende Nullen
    
    if (formattedIndex.empty()) {
        formattedIndex = "0";
    }

    // mit führenden Nullen füllen
    if (formattedIndex.size() < 6) {
        formattedIndex.insert(formattedIndex.begin(), 6 - formattedIndex.size(), '0');
    }

    // Vollständigen Pfad erstellen
    std::string formattedImageFilePath = repoDir + PATH_TO_IMAGES + seq + "/" + formattedIndex + ".png";
    return formattedImageFilePath;
}

std::string KittiDataset::formatLabelFilePath(const std::string &repoDir, const std::string &seq){
    std::string formattedLabelFilePath = repoDir + PATH_TO_LABELS + seq + ".txt";
    return formattedLabelFilePath;
}

void KittiDataset::loadDataset(const std::string &repoDir, const std::string &seq) {

    std::ifstream labelFile(formatLabelFilePath(repoDir, seq));

    #ifdef DEBUG_MODE
        if (g_debug_mode) {
            if (!labelFile.is_open()) Debugger::log(formatLabelFilePath(repoDir, seq), "Could not open label file: ");
        }
    #endif // DEBUG_MODE

    std::string line;

    while (std::getline(labelFile, line)) {

        #ifdef DEBUG_MODE
            if (g_debug_mode) {
                Debugger::log(line, "Reading line: ");
            }
        #endif // DEBUG_MODE

        std::stringstream iss(line);

        int x, y, width, height;

        std::string type;

        //if (!(iss >> m_currentIndex >> x >> y >> width >> height)) {
            #ifdef DEBUG_MODE
                if (g_debug_mode) {
                    Debugger::log(line, "ERROR parsing line: ");
                }
            #endif // DEBUG_MODE
        //}

        m_imageFilePaths.push_back(formatImageFilePath(repoDir, seq));
        m_boundingBoxes.emplace_back(type, x, y, width, height);
        #ifdef DEBUG_MODE
                if (g_debug_mode) {
                    Debugger::log(m_imageFilePaths, "all img paths: ");
                }
        #endif // DEBUG_MODE
    }

    labelFile.close();
}

std::string KittiDataset::getImageFilePathOfCurrentIndex() {
    // sorgt dafür, dass der Index innerhalb der Grenzen der Größe des Vektors bleibt
    m_currentIndex = m_currentIndex % m_imageFilePaths.size();
    return m_imageFilePaths[m_currentIndex];
}

BoundingBox KittiDataset::getBoundingBoxOfCurrentIndex() {
    m_currentIndex = m_currentIndex % m_boundingBoxes.size();
    return m_boundingBoxes[m_currentIndex];
}