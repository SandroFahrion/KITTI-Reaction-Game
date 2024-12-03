// Organisiert Dateizugriffe auf die Datensätze

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

// Quelle für KITTI-Daten
#ifndef PATH_TO_DATA_SOURCE
#define PATH_TO_DATA_SOURCE "C:/Users/User/Git/KITTI_Reaction_Game_workspace/CPP_Projekt_Klos_Fahrion/"
#endif // PATH_TO_DATA_SOURCE

// Pfad zu Bildern
#ifndef PATH_TO_IMAGES
#define PATH_TO_IMAGES "data/data_tracking_image_2/training/image_02/"
#endif // PATH_TO_IMAGES

// Pfad zu Labels
#ifndef PATH_TO_LABELS
#define PATH_TO_LABELS "data/data_tracking_label_2/training/label_02/"
#endif // PATH_TO_Labels

#include "kitti_dataset.hpp"

KittiDataset::KittiDataset(){}  // Standardkonstruktor
KittiDataset::~KittiDataset(){} // Standarddestruktor
KittiDataset::KittiDataset(const std::string &seq) {    // Überladener Konstruktor
    loadDataset(seq);
}

void KittiDataset::loadDataset(const std::string &seq) {
    loadBoxDataset(seq);
    loadImagePaths(seq);
    setRandomStartIndex();
}

void KittiDataset::loadBoxDataset(const std::string &seq) {
    std::ifstream labelFile(formatLabelFilePath(seq));

    if (!labelFile.is_open()) {
        std::cerr << "Could not open label file: " << formatLabelFilePath(seq) << std::endl;
        return;
    }

    std::string line;
    while (std::getline(labelFile, line)) { // Dateistream öffnen
        std::istringstream iss(line);

        // Variablen zur Datenextraktion erstellen
        int frame, trackId, truncation, occlusion;
        float obsAngle, bb_left, bb_top, bb_right, bb_bottom;
        std::string type;
        
        // Parse line according to the KITTI label format
        if (!(iss >> frame >> trackId >> type >> truncation >> occlusion >> obsAngle >> bb_left >> bb_top >> bb_right >> bb_bottom)) {
            std::cerr << "ERROR parsing line: " << line << std::endl;

            continue; // while-Schleife verlassen
        }

        // Bounding Boxen vom Typ "DontCare" herausfiltern
        if (type == "DontCare") {

            #ifdef DEBUG_MODE
                if (g_debug_mode) Debugger::log(frame, "Skipping DontCare BoundingBox for frame:");
            #endif // DEBUG_MODE

            continue; // while-Schleife verlassen
        }

        // Breite und Höhe der Box ermitteln
        int width = static_cast<int>(bb_right - bb_left);
        int height = static_cast<int>(bb_bottom - bb_top);

        // Bounding Box-Objekt erstellen und dem Vektor hinzufügen
        BoundingBox box(type, frame, static_cast<int>(bb_left), static_cast<int>(bb_top), width, height);
        m_boundingBoxes.push_back(box);

        #ifdef DEBUG_MODE
            if (g_debug_mode) {
                Debugger::log(frame, "Loaded BoundingBox for frame:");
                Debugger::log(type, "Type:");
            }
        #endif // DEBUG_MODE
    }

    labelFile.close(); // Dateistream schließen
}

void KittiDataset::loadImagePaths(const std::string &seq) {
    int index = 0;
    while (true) {
        std::string imagePath = formatImageFilePath(index, seq);

        if (!std::filesystem::exists(imagePath)) {
            break;
        }

        // Überprüfen, ob das Bild mindestens eine gültige Bounding Box hat
        bool hasValidBoundingBox = std::any_of(m_boundingBoxes.begin(), m_boundingBoxes.end(), [index](const BoundingBox& box){ return box.getFrame() == index; });

        if (hasValidBoundingBox) {
            m_imageFilePaths.push_back(imagePath); // Bildpfad dem Vektor hinzufügen

            #ifdef DEBUG_MODE
                if (g_debug_mode) Debugger::log(index, "img index has valid Bounding Box:");
            #endif // DEBUG_MODE

        }
        #ifdef DEBUG_MODE
            else if (g_debug_mode) Debugger::log(index, "img index does not have valid Bounding Box:");
        #endif // DEBUG_MODE

        index++;
    }
}

std::string KittiDataset::formatImageFilePath(int index, const std::string &seq){
    std::string formattedIndex = std::to_string(index);
    
    formattedIndex.insert(formattedIndex.begin(), 6 - formattedIndex.size(), '0');  // Mit führenden Nullen füllen

    // Vollständigen Pfad erstellen
    std::string formattedImageFilePath = std::string(PATH_TO_DATA_SOURCE) + std::string(PATH_TO_IMAGES) + seq + "/" + formattedIndex + ".png";

    return formattedImageFilePath;
}

std::string KittiDataset::formatLabelFilePath(const std::string &seq){
    std::string formattedLabelFilePath = std::string(PATH_TO_DATA_SOURCE) + std::string(PATH_TO_LABELS) + seq + ".txt";

    return formattedLabelFilePath;
}

void KittiDataset::setRandomStartIndex() {
    if (!m_imageFilePaths.empty()) {
        int randomIndexUpperBound = static_cast<int>(m_imageFilePaths.size() - 1); // Obere Grenze in int umwandeln
        m_currentIndex = KittiRandom::selectIntRandom(0, randomIndexUpperBound);  // Zufälligen Index innerhalb der Grenzen wählen
    }
}

std::string KittiDataset::getImageFilePathOfCurrentIndex() {
    // Sorgt dafür, dass der Index innerhalb der Grenzen der Größe des Vektors bleibt
    m_currentIndex = m_currentIndex % m_imageFilePaths.size();
     
    return m_imageFilePaths[m_currentIndex];
}

std::vector<BoundingBox> KittiDataset::getBoundingBoxesOfCurrentFrame() {
    std::vector<BoundingBox> boxesOfCurrentFrame;
    int currentFrame;

    // Sorgt dafür, dass der Index innerhalb der Grenzen der Größe des Vektors bleibt
    currentFrame = m_currentIndex % m_imageFilePaths.size();

    // Alle Boxen mit dem korrekten Frame-index dem Vektor hinzugüen
    for (const auto &box : m_boundingBoxes) {
        if (box.getFrame() == currentFrame) {
            boxesOfCurrentFrame.push_back(box);
        }
    }

    return boxesOfCurrentFrame;
}
