// Programmstart

#include "gui.hpp"
#include "reaction_game.hpp"
#define DEBUG_MODE

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

int main(int argc, char* argv[]) {
// Debugging tools
    #ifdef DEBUG_MODE
        bool debug = false;
    #endif // DEBUG_MODE
    for (int i = 1; i < argc; ++i) {    // Überprüfen, ob der --debug-Parameter übergeben wurde
        if (std::string(argv[i]) == "--debug") {
            #ifdef DEBUG_MODE   // Nur definiert, wenn mit ENABLE_DEBUG=ON CMake ausgeführt wurde
                debug = true;
                Debugger::log("Debugging mode activated");
            #endif // DEBUG_MODE
        }
    }

    GUI gui;    // Instanziierung des Menüs

    StartParams startParams("", 0, 0, 0);   // Initialisierung mit leeren Werten
    
    if (!gui.showMenu(startParams)) {   // Falls der showMenu-Aufruf false zurückgibt
        #ifdef DEBUG_MODE
            if (debug) Debugger::log("showMenu returned false");
        #endif // DEBUG_MODE
        return 0;   // Programmende
    }

    ReactionGame game(startParams); // Instanziierung der Spielverwaltung als Objekt "game" mit dem Konstruktor, der die Startparameter übergibt
    game.startGame();   //Spielstart  -> alle weitere funktionen werden über die Spielverwaltungsklasse ReactionGame aufgerufen
    
    #ifdef DEBUG_MODE
        if (debug) Debugger::logReactionGame(game);
    #endif // DEBUG_MODE

    return 0;   // Programmende
}
