// game
// Spielverwaltung

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "reaction_game.hpp"

ReactionGame::ReactionGame(const StartParams &params)
: player(params.getPlayerName()), dataset(params.getSequence()), m_turns(params.getNumTurns()) {
    // Spielmodus initialisieren
    switch (params.getGameMode()) {
        case 1:
            gameMode = new Mode1DirectClick();
            break;
        case 2:
            gameMode = new Mode2ColorChange();
            break;
        default:
            gameMode = nullptr;
            break;
    }
}

bool ReactionGame::startGame(GUI &gui) { // Umbennenn in gameLoop() ??

    // wird erst true, wenn das Spiel abgeschlossen ist
    // falls außerplanmäßig ein return durchlaufen wird, wird somit false zurückgegeben
    bool end = false;

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

            std::vector<BoundingBox> boxes = dataset.getBoundingBoxesOfCurrentFrame();
            std::string imagePath = dataset.getImageFilePathOfCurrentIndex();

            if (boxes.empty()) {
                std::cerr << "No valid bounding box found in remaining images." << std::endl;
                return end;
            }

            Image img(imagePath);
            gameMode->startRound(img, boxes);
            
            if (gameMode->getBoxDisplayCount() == SHOW_ALL_BOXES) {
                gui.displayImageWithBoundingBoxes(gameMode->getCurrentImage(), gameMode->getBoundingBoxes(), BLUE_COLOR);
                //gui.displayCountdown("Wait for the target...");
                //std::this_thread::sleep_for(std::chrono::seconds(2));
                gui.displayImageWithBoundingBox(gameMode->getCurrentImage(), gameMode->getBoundingBoxes().at(0), RED_COLOR);
                //gui.displayMessage("Go!");
            } else {
                gui.displayImageWithBoundingBox(gameMode->getCurrentImage(), gameMode->getBoundingBoxes().at(0), RED_COLOR);
            }

            int key;
            cv::Point cursorPos;
            float reactionTime = gui.measureReactionTime(key, cursorPos);

            if (key != -1) {
                gameMode->processKeyPress(key);
            }
            gameMode->processClick(cursorPos.x, cursorPos.y);

            dataset.setCurrentIndex(dataset.getCurrentIndex() + 1);

            if (!(i < m_turns)) end = true;
        }
    }

    return end;
}