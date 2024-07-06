// Programmstart

#include "gui.hpp"
#include "reaction_game.hpp"

#ifdef DEBUG_MODE
#include "debug.hpp"
Debugger* g_debugger = new Debugger(false); // Define g_debugger
#endif // DEBUG_MODE

int main(int argc, char* argv[]) {
    // Debugging tools
    #ifdef DEBUG_MODE
        for (int i = 1; i < argc; ++i) {    // Überprüfen, ob der --debug-Parameter übergeben wurde
            if (std::string(argv[i]) == "--debug") {
                g_debugger->m_debug_boolean = true;
                Debugger::log("Debugging mode activated");
            }
        }
    #endif // DEBUG_MODE

    GUI gui;                    // Instanziierung des Menüs
    StartParams startParams;    // Instanziierung eines Objektes für die Startparameter
    
    if (!gui.showMenu(startParams)) {   // Falls der showMenu-Aufruf false zurückgibt
        #ifdef DEBUG_MODE
            if (g_debugger->m_debug_boolean) Debugger::log("showMenu returned false");
        #endif // DEBUG_MODE
        return 0;   // Programmende
    }

    ReactionGame game(startParams); // Instanziierung der Spielverwaltung als Objekt "game" mit dem Konstruktor, der die Startparameter übergibt
    if (!game.startGame(gui)){   //Spielstart  -> alle weitere funktionen werden über die Spielverwaltungsklasse ReactionGame aufgerufen
        #ifdef DEBUG_MODE
            if (g_debugger->m_debug_boolean) Debugger::log("startGame function closed unexpectedly");
        #endif // DEBUG MODE
        return 0;
    }
    #ifdef DEBUG_MODE
        if (g_debugger->m_debug_boolean) g_debugger->log(game, "Game State");
    #endif // DEBUG MODE

    return 0;   // Programmende
}
