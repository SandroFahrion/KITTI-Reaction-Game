// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#include <iostream>

#include "gui.hpp"

StartParams::StartParams() {}   // Standardkonstruktor
StartParams::~StartParams() {}  // Standarddestruktor

StartParams::StartParams(const std::string &name, int turns, int seq, int mode)  // Überladener Konstruktor
: m_playerName(name), m_numTurns(turns), m_sequence(seq), m_gameMode(mode) {} // Initializer List

GUI::GUI(){}    // Standardkonstruktor
GUI::~GUI(){}   // Standarddestruktor


Player GUI::showScoreboard() {
    return Player("DummyPlayer");
}

void GUI::displayImage(Image &image) {
    cv::imshow("Display window", image.getImage());
}

void GUI::displayImageWithBoundingBox(const Image &image, const BoundingBox &box) {
    cv::Mat imgWithBox = image.getImage().clone();
    cv::rectangle(imgWithBox, cv::Point(box.getCoordX(), box.getCoordY()), cv::Point(box.getCoordX() + box.getWidthX(), box.getCoordY() + box.getHeightY()), cv::Scalar(0, 0, 255), 2);
    cv::imshow("Display window", imgWithBox);
    cv::waitKey(1000); // Warte 1 Sekunde
    cv::imshow("Display window", imgWithBox);
}

double GUI::measureReactionTime(int &key, cv::Point &cursorPos) {
    startTime = std::chrono::high_resolution_clock::now();
    key = cv::waitKey(0); // Warte unendlich lange auf einen Tastendruck

    if (key == cv::EVENT_LBUTTONDOWN) {
        // Platzhalter für Mauskoordinaten, da OpenCV solche Funktionen nicht direkt anbietet
        cursorPos = cv::Point(0, 0); // Beispielkoordinaten, anpassen entsprechend der Implementierung
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> reactionTime = endTime - startTime;
    return reactionTime.count();
}

bool GUI::showMenu(StartParams &params) {
    const int maxImages = 1000;     // Muss noch abhängig von der Höchstzahl der spielbaren Datensätzen pro Sequenz gewählt werden
    const int maxSeq = 20;          // im KITTI-Datensatz nachschauen!!!!
    const int maxMode = 2;

    // Spielername
    fflush(stdin);  // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "Enter your name: ";
    std::string playerName;
    std::cin >> playerName;
    params.setPlayerName(playerName);

    // Spielmodus
    fflush(stdin);
    std::cout << "Choose a game mode by entering the number. Available: \n1: Direct Click\n2: Color Change\n";
    int gameMode;
    std::cin >> gameMode;

    if (gameMode > maxMode || gameMode < 1) {   // Input auf Fehler prüfen
        std::cout << "Invalid input: There are game modes from 0 - " << maxMode << " to choose from. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }
    params.setGameMode(gameMode);

    // zu spielende Sequenz
    fflush(stdin);
    std::cout << "Enter the dataset/sequence you want to play. Choose between 0 and " << maxSeq << ": ";
    int sequence;
    std::cin >> sequence;

    if (sequence > maxSeq || sequence < 0) {    // Input auf Fehler prüfen
        std::cout << "Invalid input: There are 0 - " << maxSeq << " datasets. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }
    params.setSequence(sequence);

    // Anzahl der "Spielzüge"
    fflush(stdin);
    std::cout << "Enter the amount of turns you want to play (turn = react to a box): ";
    int numTurns;
    std::cin >> numTurns;

    if (numTurns < 1) {  // Input auf Fehler prüfen
        std::cout << "Invalid Input. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }
    params.setNumTurns(numTurns);

    return true; // Spielstart folgt
}
