// Programmstart
/*
#include <iostream>

int main(){
    // menü / gui aufrufen

    if (gameMode == "1") {
        
    } else if (gameMode == "2") {
        
    } else { // Fehlerausgabe, falls kein valider Spielmodus gewählt wurde
        std::cerr << "Invalid game mode selected!" << std::endl;
        return -1;
    }

    game.start();
    return 0;
}
*/
#include "gui.hpp"
#include "reaction_game.hpp"

int main() {
    GUI gui;    // Instanziierung des Menüs
    auto startParams = gui.showMenu(); //Aufruf des Menüs

    ReactionGame game(startParams); // Instanziierung der Spielverwaltung als Objekt "game" mit dem Konstruktor, der die Startparameter übergibt
    game.startGame();   //Spielstart  -> alle weitere funktionen werden über die Spielverwaltungsklasse ReactionGame aufgerufen 
    
    return 0;
}
