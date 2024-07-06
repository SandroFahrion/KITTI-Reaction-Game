// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#include "gui.hpp"

StartParams::StartParams() {}  // Standardkonstruktor

StartParams::StartParams(const std::string &name, int turns, int seq, int mode)  // Überladener Konstruktor
    : m_playerName(name), m_numTurns(turns), m_sequence(seq), m_gameMode(mode) {} // Initializer List

bool GUI::showMenu(StartParams &params) {
    const int maxImages = 1000;     // Muss noch abhängig von der Höchstzahl der spielbaren Datensätzen pro Sequenz gewählt werden
    const int maxSeq = 20;          // im KITTI-Datensatz nachschauen!!!!
    const int maxMode = 2;

    // Spielername
    fflush(stdin);  // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "Enter your name: ";
    std::cin >> params.m_playerName;

    // Spielmodus
    fflush(stdin);
    std::cout << "Choose a game mode by entering the number. Available: \n1: Direct Click\n2: Color Change\n";
    std::cin >> params.m_gameMode;

    if (params.m_gameMode > maxMode || params.m_gameMode < 1) {   // Input auf Fehler prüfen
        std::cout << "Invalid input: There are game modes from 0 - " << maxMode << " to choose from. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }

    // zu spielende Sequenz
    fflush(stdin);
    std::cout << "Enter the dataset/sequence you want to play. Choose between 0 and " << maxSeq << ": ";
    std::cin >> params.m_sequence;

    if (params.m_sequence > maxSeq || params.m_sequence < 0) {    // Input auf Fehler prüfen
        std::cout << "Invalid input: There are 0 - " << maxSeq << " datasets. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }

    // Anzahl der "Spielzüge"
    fflush(stdin);
    std::cout << "Enter the amount of turns you want to play (turn = react to a box): ";
    std::cin >> params.m_numTurns;

    if (params.m_numTurns < 1) {  // Input auf Fehler prüfen
        std::cout << "Invalid Input. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }

    return true; // Spielstart folgt
}

Player GUI::showScoreboard() {
    return Player("DummyPlayer");
}

void GUI::displayImage(Image &image) {

}
