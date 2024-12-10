// Sämtliche Funktionen zur Interaktion mit dem Spieler (=User Interface)

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#ifndef NAME_OF_THE_GAME
#define NAME_OF_THE_GAME "KITTI Reaction Game"
#endif // NAME_OF_THE_GAME

#include "gui.hpp"

StartParams::StartParams() {}   // Standardkonstruktor
StartParams::~StartParams() {}  // Standarddestruktor

StartParams::StartParams(const std::string &name, int turns, const std::string &seq, int mode)  // Überladener Konstruktor
: m_playerName(name), m_numTurns(turns), m_sequence(seq), m_gameMode(mode) { // Initializer List

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR); // Nur OpenCV-Fehler zeigen
    
    #ifdef DEBUG_MODE
        if (g_debug_mode) cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_INFO); // OpenCV-Logs wieder aktivieren
    #endif  // DEBUG_MODE
}

GUI::GUI(){}    // Standardkonstruktor
GUI::~GUI(){}   // Standarddestruktor

void GUI::showScoreboard(const Player &player) const {
    // Display player's name
    std::cout << "Player: " << player.getName() << std::endl;

    // Get reaction times
    const std::vector<float>& times = player.getReactionTimes();

    // If there are no reaction times, display a message and return
    if (times.empty()) {
        std::cout << "No reaction times recorded." << std::endl;
        return;
    }

    // Calculate and display the total reaction time
    float sum = std::accumulate(times.begin(), times.end(), 0.0f);
    std::cout << "Total reaction time with penalty time: " << std::fixed << std::setprecision(2) << sum << " seconds" << std::endl;

    const std::vector<float>& hittimes = player.getHitTimes();

    // If there are no  hittimes, display a message and return
    if (hittimes.empty()) {
        std::cout << "No hittimes recorded." << std::endl;
        return;
    }

    sum = std::accumulate(hittimes.begin(), hittimes.end(), 0.0f);
    float average = sum / hittimes.size();
    std::cout << "Average Reaction Time: " << std::fixed << std::setprecision(2) << average << " seconds" << std::endl;


    // Sort the reaction times in ascending order
    std::vector<float> sortedTimes = times;
    std::sort(sortedTimes.begin(), sortedTimes.end());

    // Display the top 3 reaction times
    std::cout << "Top 3 Reaction Times: " << std::endl;
    for (size_t i = 0; i < std::min<size_t>(3, sortedTimes.size()); ++i) {
        std::cout << i + 1 << ": " << std::fixed << std::setprecision(2) << sortedTimes[i] << " seconds" << std::endl;
    }
}

void GUI::displayImage(const Image &image) {
    cv::imshow(NAME_OF_THE_GAME, image);
}

void GUI::displayImageWithBoundingBox(const std::string &imagepath, const BoundingBox &box, cv::Scalar color) const {
    Image img(imagepath, box, color);
    cv::Mat imgWithBox = img;     // Bild-Objekt mit Box erstellen
    cv::imshow(NAME_OF_THE_GAME, imgWithBox);   // Bild in openCV öffnen
    cv::waitKey(1);
}

void GUI::displayImageWithBoundingBoxes(const std::string &imagepath, const std::vector<BoundingBox> &boxes, cv::Scalar color) const {
    Image imgWithBoxes(imagepath, boxes, color);    // Bild-Objekt mit allen Boxen erstellen
    cv::imshow(NAME_OF_THE_GAME, imgWithBoxes);     // Bild in openCV öffnen
    cv::waitKey(1);
}

void GUI::displayImageWithDifferentBoundingBoxes(const std::string &imagePath, const std::vector<BoundingBox> &redBoxes, cv::Scalar redColor, const std::vector<BoundingBox> &blueBoxes, cv::Scalar blueColor) const {
    Image imgWithBoxes(imagePath, redBoxes, redColor, blueBoxes, blueColor);    // Bild-Objekt mit allen Boxen erstellen
    cv::imshow(NAME_OF_THE_GAME, imgWithBoxes);     // Bild in openCV öffnen
    cv::waitKey(1);
}

void GUI::displayCountdown(const std::string &message) {
}

void GUI::displayMessage(const std::string &message) const {
    std::cout << message << std::endl;
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
    const int maxMode = 3;

    std::cout << "\nWelcome to the KITTI Reaction Game! You will be shown an image from the KITTI dataset,\
 a training set from the KIT (Karlsruhe Institute of Technology) about the recognition of objects in street traffic.\
 Depending on the game mode, the reaction time of your interaction with the shown data is measured in different ways.\n";

    // Spielername
    std::string playerName;
    fflush(stdin); // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "\nFirst, please enter your name: ";
    std::getline(std::cin, playerName);
    params.setPlayerName(playerName);

    // Spielmodus
    int gameMode;
    fflush(stdin);
    std::cout << "\nThere are " << maxMode << " available game modes: \n1: Direct Click\n2: Color Change\n3: Memory\nChoose a game mode by entering the number: ";
    std::cin >> gameMode;

    if (gameMode > maxMode || gameMode < 1) { // Input auf Fehler prüfen
        std::cout << "\nInvalid input: There are " << maxMode << " game modes. Your input was: " << gameMode << ". The program will shut down without launching the game.\n";
        return false; // Programmabbruch folgt
    }
    params.setGameMode(gameMode);

    // zu spielende Sequenz
    int sequence;
    fflush(stdin);
    std::cout << "\nEnter the dataset/sequence you want to play. Choose between 0 and " << maxSeq << ": ";
    std::cin >> sequence;

    if (sequence > maxSeq || sequence < 0) { // Input auf Fehler prüfen
        std::cout << "\nInvalid input: There are 0 - " << maxSeq << " datasets. Your input was: " << sequence << ". The program will shut down without launching the game.\n";
        return false; // Programmabbruch folgt
    }
    params.setSequence(formatSequenceInput(std::to_string(sequence)));

    // Anzahl der Spielzüge
    int numTurns;
    fflush(stdin);
    std::cout << "\nEnter the amount of turns you want to play: ";
    std::cin >> numTurns;

    if (numTurns < 1) {  // Input auf Fehler prüfen
        std::cout << "\nInvalid Input. The program will shut down without launching the game.\n";
        return false; // Programmabbruch folgt
    }
    params.setNumTurns(numTurns);

    return true; // Spielstart folgt
}
