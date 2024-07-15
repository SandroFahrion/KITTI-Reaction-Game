// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#ifndef NAME_OF_THE_GAME
#define NAME_OF_THE_GAME "KITTI Reaction Game"
#endif // NAME_OF_THE_GAME

#include "gui.hpp"

StartParams::StartParams() {}   // Standardkonstruktor
StartParams::~StartParams() {}  // Standarddestruktor

StartParams::StartParams(const std::string &name, int turns, const std::string &seq, int mode)  // Überladener Konstruktor
: m_playerName(name), m_numTurns(turns), m_sequence(seq), m_gameMode(mode) { // Initializer List

    _putenv("OPENCV_LOG_LEVEL=SILENT"); // Set OpenCV log level to silent
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
}

GUI::GUI(){}    // Standardkonstruktor
GUI::~GUI(){}   // Standarddestruktor

Player GUI::showScoreboard() {
    return Player("DummyPlayer");
}

void GUI::displayImage(Image &image) {
    cv::imshow(NAME_OF_THE_GAME, image.getImage());
}

void GUI::displayImageWithBoundingBox(const Image &image, const BoundingBox &box, cv::Scalar color) const {
    cv::Mat imgWithBox = image.getImage();
    cv::rectangle(imgWithBox, cv::Point(box.getCoordX(), box.getCoordY()), cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);

    // add box type as plain text
    std::string boxType = box.getType();
    cv::putText(imgWithBox, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);

    cv::imshow(NAME_OF_THE_GAME, imgWithBox); // Finale Bildausgabe
}

// allowing for more than 1 bounding boxes to be displayed
void GUI::displayImageWithBoundingBoxes(const Image& img, const std::vector<BoundingBox>& boxes, cv::Scalar color) const {
    cv::Mat imgWithBoxes = img.getImage();

    for (const auto& box : boxes) {
        cv::rectangle(imgWithBoxes, cv::Point(box.getCoordX(), box.getCoordY()), cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), color, 2);
        
        // add box type as plain text
        std::string boxType = box.getType();
        cv::putText(imgWithBoxes, boxType, cv::Point(box.getCoordX(), box.getCoordY() - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    }

    cv::imshow(NAME_OF_THE_GAME, imgWithBoxes);
}

void GUI::displayCountdown(const std::string &message) {
    cv::Mat img = cv::Mat::zeros(100, 400, CV_8UC3);
    cv::putText(img, message, cv::Point(30, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    cv::imshow(NAME_OF_THE_GAME, img);
    cv::waitKey(1000);
}

void GUI::displayMessage(const std::string &message) {
    cv::Mat img = cv::Mat::zeros(100, 400, CV_8UC3);
    cv::putText(img, message, cv::Point(30, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    cv::imshow(NAME_OF_THE_GAME, img);
    cv::waitKey(1000);
}

float GUI::measureReactionTime(int &key, cv::Point &cursorPos) const {
    m_startTime = std::chrono::high_resolution_clock::now();
    key = cv::waitKey(3000); // Warte 3 Sekunden auf einen Tastendruck

    if (key == cv::EVENT_LBUTTONDOWN) {
        // setMouseCallback Funktion Nutzen
        cursorPos = cv::Point(0, 0); // Beispielkoordinaten, anpassen entsprechend der Implementierung
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> reactionTime = endTime - m_startTime;
    return reactionTime.count();
}

std::string GUI::formatSequenceInput(const std::string &seq){
    std::string formattedSeq = seq;

    formattedSeq.erase(0, formattedSeq.find_first_not_of('0')); // Entferne führende Nullen (Bsp.:"0000010")
    
    // Wenn das Ergebnis leer ist (d.h. es wurde der 0. Datensatz gewählt), setze es auf "0"
    if (formattedSeq.empty()) {
        formattedSeq = "0";
    }

    // mit führenden Nullen füllen
    if (formattedSeq.size() < 4) {
        formattedSeq.insert(formattedSeq.begin(), 4 - formattedSeq.size(), '0');
    }

    return formattedSeq;
}

bool GUI::showMenu(StartParams &params) {
    const int maxSeq = 20;
    const int maxMode = 2;

    std::cout << "\nWelcome to the KITTI Reaction Game! You will be shown an image from the KITTI dataset,\
 a training set from the KIT (Karlsruhe Institute of Technology) about the recognition of objects in street traffic.\
 Depending on the game mode, the reaction time of your interaction with the shown data is measured in different ways.\n";

    // Spielername
    fflush(stdin);  // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "\nFirst, please enter your name: ";
    std::string playerName;
    std::cin >> playerName;
    params.setPlayerName(playerName);

    // Spielmodus
    fflush(stdin);
    std::cout << "\nThere are " << maxMode << " available game modes: \n1: Direct Click\n2: Color Change\nChoose a game mode by entering the number: ";
    int gameMode;
    std::cin >> gameMode;

    if (gameMode > maxMode || gameMode < 1) {   // Input auf Fehler prüfen
        std::cout << "\nInvalid input: There are " << maxMode << " game modes. Your input was: " << gameMode << ". The program will shut down without launching the game.\n";
        return false; // Programmabbruch folgt
    }
    params.setGameMode(gameMode);

    // zu spielende Sequenz
    fflush(stdin);
    std::cout << "\nEnter the dataset/sequence you want to play. Choose between 0 and " << maxSeq << ": ";
    int sequence;
    std::cin >> sequence;

    if (sequence > maxSeq || sequence < 0) {    // Input auf Fehler prüfen
        std::cout << "\nInvalid input: There are 0 - " << maxSeq << " datasets. Your input was: " << sequence << ". The program will shut down without launching the game.\n";
        return false; // Programmabbruch folgt
    }
    params.setSequence(formatSequenceInput(std::to_string(sequence)));

    // Anzahl der "Spielzüge"
    fflush(stdin);
    std::cout << "\nEnter the amount of turns you want to play: ";
    int numTurns;
    std::cin >> numTurns;

    if (numTurns < 1) {  // Input auf Fehler prüfen
        std::cout << "\nInvalid Input. The program will shut down without launching the game.\n";
        return false; // Programmabbruch folgt
    }
    params.setNumTurns(numTurns);

    return true; // Spielstart folgt
}
