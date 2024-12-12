// Programmstart

#ifdef DEBUG_MODE
#include "helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "include/gui.hpp"
#include "game_mode/game_mode.hpp"
#include "game_mode/mode_1_direct_click.hpp"
#include "game_mode/mode_2_color_change.hpp"
#include "game_mode/mode_3_memory.hpp"



int main(int argc, char* argv[]) {

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
    StartParams startParams;    // Instanziierung des Startparameter-Objektes
    
    if (!gui.showMenu(startParams)) {   // Falls der showMenu-Aufruf false zurückgibt

        #ifdef DEBUG_MODE
            if (g_debug_mode) Debugger::log("showMenu returned false");
        #endif // DEBUG_MODE

        return 0;   // Programmende
    }

    GameMode *gameMode;

    switch(startParams.getGameMode()){
        case 1: // Spielmodus 1 wird gestartet
            gameMode = new Mode1DirectClick(startParams, gui);
            break;

        case 2: // Spielmodus 2 wird gestartet
            gameMode = new Mode2ColorChange(startParams, gui);
            break;

        case 3: //Spielmodus 3 wird geststartet
            gameMode = new Mode3Memory(startParams, gui);

        default:
            gameMode = nullptr;
            break;
    }

    #ifdef DEBUG_MODE
        if (g_debug_mode) Debugger::log(startParams, "startParams");
    #endif // DEBUG MODE

    return 0;   // Programmende
}
