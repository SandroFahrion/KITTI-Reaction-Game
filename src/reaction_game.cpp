// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#include "reaction_game.hpp"

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

ReactionGame::ReactionGame(const StartParams &params)  // siehe header-file für doku
    : player(params.m_playerName), dataset(params.m_sequence), gameMode(nullptr), m_turns(params.m_numTurns) {}

// Spielablauf durch Aufruf der Funktionen in einer Schleife
bool ReactionGame::startGame(GUI &gui) {
    bool end = false;

    #ifdef DEBUG_MODE
        if (g_debug_mode) {
            Debugger::log(m_turns, "m_turns");
        }
    #endif // DEBUG_MODE

    while (!end) {
        for (int i = 0; i < m_turns; ++i) {
            #ifdef DEBUG_MODE
            if (g_debug_mode) {
                Debugger::log(end, "Game End Status");
            }
            #endif // DEBUG_MODE
            image = dataset.getImage(i);
            image.setBoundingBoxes(dataset.getBoundingBoxes(i));
            gui.displayImage(image);
            // gameMode->processClick();
            // reaction times
            // stats ausgeben
            end = true;
        }
    }

    return end;
}
