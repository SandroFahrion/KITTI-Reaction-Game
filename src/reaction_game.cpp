// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#include "reaction_game.hpp"

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

//ReactionGame::ReactionGame(const StartParams &params)
//: player(params.getPlayerName()), dataset(params.getSequence()), gameMode(nullptr), m_turns(params.getNumTurns()), params(params) {}

ReactionGame::ReactionGame(const StartParams &params)
: player(params.getPlayerName()), dataset("path/to/images", "path/to/0010.txt"), gameMode(nullptr), m_turns(params.getNumTurns()), params(params) {}


bool ReactionGame::startGame(GUI &gui) {
    // wird erst true, wenn das Spiel abgeschlossen ist
    // falls außerplanmäßig ein return durchlaufen wird, wird somit false zurückgegeben
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
            
            std::string imagePath = dataset.getNextImage();
            BoundingBox box = dataset.getBoundingBox();
            Image img(imagePath);
            gui.displayImageWithBoundingBox(img, box);

            // Reaction time measurement
            int key;
            cv::Point cursorPos;
            double reactionTime = gui.measureReactionTime(key, cursorPos);

            if (box.contains(cursorPos.x, cursorPos.y)) {
                std::cout << "Hit! Reaction Time: " << reactionTime << " seconds" << std::endl;
            } else {
                std::cout << "Miss! Penalty applied." << std::endl;
            }

            end = true;
        }
    }

    return end;
}
