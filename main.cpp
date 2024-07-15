// Programmstart

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "gui.hpp"
#include "reaction_game.hpp"


int main(int argc, char* argv[]) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT); // Set OpenCV log level to silent

    // Debugging tool
    #ifdef DEBUG_MODE
        for (int i = 1; i < argc; ++i) {    // Überprüfen, ob der --debug-Parameter übergeben wurde
            if (std::string(argv[i]) == "--debug") {
                g_debug_mode = true;
                Debugger::log("Debugging mode activated\n");
            }
        }
    #endif // DEBUG_MODE

    GUI gui;                    // Instanziierung des Menüs
    StartParams startParams;    // Instanziierung eines Objektes für die Startparameter
    Player player;
    
    if (!gui.showMenu(startParams)) {   // Falls der showMenu-Aufruf false zurückgibt

        #ifdef DEBUG_MODE
            if (g_debug_mode) Debugger::log("showMenu returned false");
        #endif // DEBUG_MODE

        return 0;   // Programmende
    }

    ReactionGame game(startParams); // Instanziierung der Spielverwaltung als Objekt "game" mit dem Konstruktor, der die Startparameter übergibt
    if (!game.startGame(gui)){   // Spielstart -> alle weitere funktionen werden durch die Spielverwaltungsklasse ReactionGame aufgerufen
        
        #ifdef DEBUG_MODE
            if (g_debug_mode) Debugger::log("startGame function closed unexpectedly");
        #endif // DEBUG_MODE

        return 0;
    }

    #ifdef DEBUG_MODE
        if (g_debug_mode) Debugger::log(game, "Game State");
    #endif // DEBUG MODE
    #ifdef DEBUG_MODE
        if (g_debug_mode) Debugger::log(startParams, "startParams");
    #endif // DEBUG MODE

    return 0;   // Programmende
}
