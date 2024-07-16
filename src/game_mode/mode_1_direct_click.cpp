// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "game_mode/mode_1_direct_click.hpp"

Mode1DirectClick::Mode1DirectClick(const StartParams &params, const GUI &gui) : m_reactionTime(0) {
    startGame(params, gui);
}

bool Mode1DirectClick::startGame(const StartParams &params, const GUI &gui) {
   
    Player player(params.getPlayerName());

    // KittiDataset Konstruktor enthält
    // loadBoxDataset(seq);
    // loadImagePaths(seq);
    // setRandomStartIndex();
    KittiDataset dataset(params.getSequence());
    
    m_turns = params.getNumTurns();
    bool end = false;
    while (!end) {
        for (int i = 1; i <= m_turns; ++i) {

            #ifdef DEBUG_MODE
            if (g_debug_mode) {
                Debugger::log(i, "Turn nr");
                Debugger::log(dataset.getImageFilePathOfCurrentIndex(), "current img path");
                Debugger::log(dataset.getCurrentIndex(), "current index");
            }
            #endif // DEBUG_MODE

            // Get all valid boxes of current index, then select one randomly
            std::vector<BoundingBox> boxes = dataset.getBoundingBoxesOfCurrentFrame();
            if (boxes.empty()) {
                gui.displayMessage("No valid bounding box found in remaining images.");
                return end;
            }
            int randomIndexUpperBound = static_cast<int>(boxes.size() - 1);
            BoundingBox box = boxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];

            // Create image object
            std::string imagePath = dataset.getImageFilePathOfCurrentIndex();
            Image img(imagePath, box, RED_COLOR);

            // Image gets shown, turn begins
            gui.displayImageWithBoundingBox(img, box, RED_COLOR);
            startTurn(img, boxes);

            dataset.incrementCurrentIndex();

            if (!(i < m_turns)) end = true;
        }
    }
    
    return end;
}

void Mode1DirectClick::startTurn(const Image &img, const std::vector<BoundingBox>& boxes, const GUI &gui) {
    timer.timeMeasureBegin();

    cv::Point cursorPos;
 
    processClick(cursorPos.x, cursorPos.y);
}

void Mode1DirectClick::processClick(int x, int y, const GUI &gui) {
    if (boundingBox.contains(x, y)) {
        m_reactionTime = timer.timeMeasureEnd();
        gui.displayMessage("Hit! Reaction time: " + m_reactionTime + " seconds");
    } else {
        m_reactionTime += m_penaltyTime;
        gui
        gui.displayMessage("Miss! 5 second penalty!");
    }
}

void Mode1DirectClick::processClick(int event, int x, int y, int, void*, const GUI &gui) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        gui.displayMessage("Linke Maustaste gedrückt bei (" + x + ", " + y + ")");
    } else if (event == cv::EVENT_MOUSEMOVE) {
        gui.displayMessage("Maus bewegt zu (" + x + ", " + y + ")");
    }
}

void Mode1DirectClick::processKeyPress(int key) {
    // Keine Tastatureingabe in diesem Modus
}
