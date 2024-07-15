// Programmstart

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "gui.hpp"
#include "game_mode/game_mode.hpp"
#include "game_mode/mode_1_direct_click.hpp"
#include "game_mode/mode_2_color_change.hpp"


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
    
    if (!gui.showMenu(startParams)) {   // Falls der showMenu-Aufruf false zurückgibt

        #ifdef DEBUG_MODE
            if (g_debug_mode) Debugger::log("showMenu returned false");
        #endif // DEBUG_MODE

        return 0;   // Programmende
    }

    GameMode *gameMode;

    switch(startParams.getGameMode()){
        case 1:
            gameMode = new Mode1DirectClick(startParams, gui);
            break;
        case 2:
            gameMode = new Mode2ColorChange(startParams, gui);
            break;
        default:
            gameMode = nullptr;
            break;
    }

    #ifdef DEBUG_MODE
        if (g_debug_mode) Debugger::log(startParams, "startParams");
    #endif // DEBUG MODE

    return 0;   // Programmende
}
