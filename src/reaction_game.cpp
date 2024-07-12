// game
// Spielverwaltung
// ruft die benötigten klassen und funktionen auf zur Erstellung der Instanzen auf

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "reaction_game.hpp"

ReactionGame::ReactionGame(const StartParams &params)
: player(params.getPlayerName()), dataset(params.getSequence()), gameMode(nullptr), m_turns(params.getNumTurns()) {}

bool ReactionGame::startGame(GUI &gui) { // Umbennenn in gameLoop() ??

    // wird erst true, wenn das Spiel abgeschlossen ist
    // falls außerplanmäßig ein return durchlaufen wird, wird somit false zurückgegeben
    end = false;

    while (!end) {
        for (int i = 1; i <= m_turns; ++i) {

            #ifdef DEBUG_MODE
            if (g_debug_mode) {
                Debugger::log(end, "Game End Status is");
                Debugger::log(i, "Turn nr");
                Debugger::log(dataset.getImageFilePathOfCurrentIndex(), "current img path");
                Debugger::log(dataset.getCurrentIndex(), "current index");

            }
            #endif // DEBUG_MODE
            
            BoundingBox box = dataset.getBoundingBoxOfCurrentIndex();
            Image img(dataset.getImageFilePathOfCurrentIndex());

            gui.displayImageWithBoundingBox(img, box);



            // Refactoring in die gameMode-Klassen
            int key;
            cv::Point cursorPos;
            double reactionTime = gui.measureReactionTime(key, cursorPos);

            if (box.contains(cursorPos.x, cursorPos.y)) {
                std::cout << "Hit! Reaction time: " << reactionTime << " seconds" << std::endl;
            } else {
                std::cout << "Miss! 5 second penalty!" << std::endl;
            }
            // Refactoring in die gameMode-Klassen

            dataset.setCurrentIndex(dataset.getCurrentIndex() + 1);

            if (!(i < m_turns)) end = true;
        }
    }

    return end;
}
