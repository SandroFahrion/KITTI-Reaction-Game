// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#include "gui.hpp"

StartParams::StartParams(const std::string &name, int num, int seq, int mode):   // Überladener Konstruktor
m_playerName(name), m_numImages(num), m_sequence(seq), m_gameMode(mode) { // Initializer List

}

bool GUI::showMenu(StartParams &params){
    const int maxImages = 10;   // Muss noch abhängig von der Höchstzahl der spielbaren Datensätzen pro Sequenz gewählt werden
    const int maxSeq = 5;   // im KITTI-Datensatz nachschauen!!!!
    const int maxMode = 2;

    // Spielername
    fflush(stdin);  // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "Enter your name: ";
    std::cin >> params.m_playerName;

    // Spielmodus
    fflush(stdin);
    std::cout << "Choose a game mode by entering the number. Available: \n1: Direct Click\n2:Color Change";
    std::cin >> params.m_gameMode;
    if (params.m_gameMode > maxMode){
        std::cout << "Invalid Input: There are only " << maxMode << " game modes to choose from. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }

    // zu spielende Sequenz
    fflush(stdin);
    std::cout << "Enter the dataset/sequence you want to play. Choose between 0 and " << maxSeq << ": ";
    std::cin >> params.m_sequence;
    if (params.m_sequence > maxSeq){
        std::cout << "Invalid Input: There are only " << maxSeq << " datasets. The program will shut down without launching the game.";
        return false; // Programmabbruch folgt
    }

    // Anzahl der "Spielzüge"
    fflush(stdin);
    std::cout << "Enter the amount of iterations you want to play: ";
    std::cin >> params.m_numImages;
    if (params.m_numImages > maxImages){
        params.m_numImages = maxImages;
        std::cout << "The chosen dataset only contains " << maxImages << "images. Iteration number has been set to that amount.";
    }

    // Instanziierung des Startparameter-Objektes "params" mit dem Konstruktor und den abgefragten Werten
    //params = StartParams(params.m_playerName, params.m_numImages, params.m_sequence, params.m_gameMode);
    return true; // Spielstart folgt
}

Player GUI::showScoreboard(){
    return Player("DummyPlayer");
}

void GUI::displayImage(const Image &image){

}