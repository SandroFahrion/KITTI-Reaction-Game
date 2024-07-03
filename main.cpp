// Programmstart

#include "include/gui.hpp"
#include "include/reaction_game.hpp"

int main() {
    GUI gui;    // Instanziierung des Menüs
    StartParams startParams("", 0, 0, 0); // Initialisierung mit leeren Werten
    
    if (!gui.showMenu(startParams)) {
        // Falls der showMenu-Aufruf false zurückgibt, beenden wir das Programm
        return 0;   // Programmende
    }

    ReactionGame game(startParams); // Instanziierung der Spielverwaltung als Objekt "game" mit dem Konstruktor, der die Startparameter übergibt
    game.startGame();   //Spielstart  -> alle weitere funktionen werden über die Spielverwaltungsklasse ReactionGame aufgerufen 
    
    return 0;   // Programmende
}
