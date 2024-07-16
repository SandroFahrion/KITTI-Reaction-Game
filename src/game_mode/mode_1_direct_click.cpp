// Spielmodus 1 - Direct Click Reaction

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "game_mode/mode_1_direct_click.hpp"

// Konstruktor
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
    
    // Schleife, um die Anzahl der gewünschten Spielzüge zu wiederholen, kann bei Fehler unterbrochen werden 
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

            // Alle validen Boxen des aktuellen Indexes auslesen, dann zufällig eine Box wählen
            std::vector<BoundingBox> boxes = dataset.getBoundingBoxesOfCurrentFrame();
            if (boxes.empty()) {
                gui.displayMessage("No valid bounding box found in remaining images.");
                return end;
            }
            int randomIndexUpperBound = static_cast<int>(boxes.size() - 1);
            BoundingBox box = boxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];
            
            std::string imagePath = dataset.getImageFilePathOfCurrentIndex();

            // Bild wird gezeigt, Spielzug beginnt
            gui.displayImageWithBoundingBox(imagePath, box, RED_COLOR);
            startTurn(boxes, gui);

            dataset.incrementCurrentIndex(); // Index hochzählen

            if (!(i < m_turns)) end = true;
        }
    }
    
    return end;
}

// Spielzug, Verarbeitung von Spieler-Input
void Mode1DirectClick::startTurn(const std::vector<BoundingBox>& boxes, const GUI &gui) {
    timer.timeMeasureBegin();

    cv::Point cursorPos;
 
    processClick(cursorPos.x, cursorPos.y, gui);
}

// Verarbeitung eines Mausklicks
void Mode1DirectClick::processClick(int x, int y, const GUI &gui) {
    if (boundingBox.contains(x, y)) {
        m_reactionTime = timer.timeMeasureEnd();
        gui.displayMessage("Hit! Reaction time: " + std::to_string(m_reactionTime) + " seconds");
    } else {
        m_reactionTime += m_penaltyTime;
        gui.displayMessage("Miss! 5 second penalty!");
    }
}

void Mode1DirectClick::processClick2(int event, int x, int y, int, void*, const GUI &gui) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        gui.displayMessage("Linke Maustaste gedrückt bei (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    } else if (event == cv::EVENT_MOUSEMOVE) {
        gui.displayMessage("Maus bewegt zu (" + std::to_string(x) + ", " + std::to_string(y) + ")");
    }
}

void Mode1DirectClick::processKeyPress(int key) {
    // Keine Tastatureingabe in diesem Modus
}
