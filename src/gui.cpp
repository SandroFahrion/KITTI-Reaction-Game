// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#include "include/gui.hpp"

StartParams::StartParams(const std::string &name, int num, int seq, int mode):   // Überladener Konstruktor
m_playerName(name), m_numImages(num), m_sequence(seq), m_gameMode(mode) { // Initializer List

}

bool GUI::showMenu(StartParams &params){
    const int maxImages = 10;   // Muss noch abhängig von der Höchstzahl der spielbaren Datensätzen pro Sequenz gewählt werden
    const int maxSeq = 5;   // im KITTI-Datensatz nachschauen!!!!
    const int maxMode = 2;

    // Spielername
    fflush(stdin);  // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "Bitte geben Sie Ihren Namen ein: ";
    std::cin >> params.m_playerName;

    // Spielmodus
    fflush(stdin);
    std::cout << "Wählen Sie den Spielmodus (1 für Direct Click): ";
    std::cin >> params.m_gameMode;
    if (params.m_gameMode > maxMode){
        std::cout << "Es gibt nur " << maxMode << " Spielmodi, die Eingabe ist somit ungültig und das Programm wird ohne Spielstart beendet";
        return false; // Programmabbruch folgt
    }

    // zu spielende Sequenz
    fflush(stdin);
    std::cout << "Bitte die zu spielende Sequenz wählen: ";
    std::cin >> params.m_sequence;
    if (params.m_sequence > maxSeq){
        std::cout << "Es gibt nur " << maxSeq << " verschiedene Sequenzen, die Eingabe ist somit ungültig und das Programm wird ohne Spielstart beendet";
        return false; // Programmabbruch folgt
    }

    // Anzahl der "Spielzüge"
    fflush(stdin);
    std::cout << "Anzahl der zu spielenden Bilder wählen: ";
    std::cin >> params.m_numImages;
    if (params.m_numImages > maxImages){
        params.m_numImages = maxImages;
        std::cout << "Die Anzahl der spielbaren Bilder im Datensatz dieser Sequenz beträgt " << maxImages << ", die Anzahl wurde auf dieses Maximum gesetzt";
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