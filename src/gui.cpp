// funktion zur aufruf der konsole als "menüführung" vor beginn des spiels
// funktion zur darstellung des spielfensters

#include "gui.hpp"

StartParams::StartParams(const std::string& name, int num, const std::string& seq, int mode):    // Überladener Konstruktor
m_playerName(name), m_numImages(num), m_sequence(seq), m_gameMode(mode) {                        // Initializer List

}

StartParams GUI::showMenu(){
    std::string playerName;
    int amountImages, gameMode, sequence;
    const int maxAmount = 10;// Muss noch abhängig von der Höchstzahl der spielbaren Datensätzen pro Sequenz gewählt werden
    fflush(stdin);  // Input-Buffer leeren (Anfälligkeit für Eingabefehler reduzieren)
    std::cout << "Bitte geben Sie Ihren Namen ein: ";
    std::cin >> playerName;
    fflush(stdin);
    std::cout << "Bitte die zu spielende Sequenz wählen: ";
    std::cin >> sequence;

    if (sequence > 5){
        std::cout << "Es gibt nur 5 verschiedene Sequenzen, die Eingabe ist somit ungültig und das Programm wird ohne Spielstart beendet";
        // Abbruch einbauen (evtl return-Wert für showMenu() einbauen)
    }
    fflush(stdin);
    std::cout << "Anzahl der zu spielenden Bilder wählen: ";
    std::cin >> amountImages;
    if (amountImages > maxAmount){
        amountImages = maxAmount;
        std::cout << "Die Anzahl der spielbaren Bilder im Datensatz dieser Sequenz beträgt " << maxAmount << ", die Anzahl wurde auf dieses Maximum gesetzt";
    }
    fflush(stdin);
    std::cout << "Wählen Sie den Spielmodus (1 für Direct Click): ";
    std::cin >> gameMode;
}

Player GUI::showScoreboard(){

}

void GUI::displayImage(const Image &image){

}