// game
// Spielverwaltung

#ifdef DEBUG_MODE
#include "debug.hpp"
#endif // DEBUG_MODE

#include "reaction_game.hpp"

ReactionGame::ReactionGame(const StartParams &params)
: player(params.getPlayerName()), dataset(params.getSequence()), gameMode(nullptr), m_turns(params.getNumTurns()) {}

bool ReactionGame::startGame(GUI &gui) { // Umbennenn in gameLoop() ??

    std::random_device rd;   // Zufälliger Seed
    std::mt19937 gen(rd());  // Zufallszahlengenerator

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
                return false;
            }

            // Wählen Sie eine zufällige Bounding Box aus
            std::uniform_int_distribution<size_t> dis(0, boxes.size() - 1);
            BoundingBox box = boxes[dis(gen)];

            Image img(imagePath);
            gui.displayImageWithBoundingBox(img, box);

            int key;
            cv::Point cursorPos;
            double reactionTime = gui.measureReactionTime(key, cursorPos);

            if (box.contains(cursorPos.x, cursorPos.y)) {
                std::cout << "Hit! Reaction time: " << reactionTime << " seconds" << std::endl;
            } else {
                std::cout << "Miss! 5 second penalty!" << std::endl;
            }

            dataset.setCurrentIndex(dataset.getCurrentIndex() + 1);

            if (!(i < m_turns)) end = true;
        }
    }

    return end;
}
