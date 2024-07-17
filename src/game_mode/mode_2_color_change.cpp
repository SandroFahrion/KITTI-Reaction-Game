// Spielmodus 2 - Color Change Reaction

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#ifndef NAME_OF_THE_GAME
#define NAME_OF_THE_GAME "KITTI Reaction Game"
#endif // NAME_OF_THE_GAME

#include "game_mode/mode_2_color_change.hpp"

// Konstruktor
Mode2ColorChange::Mode2ColorChange(const StartParams &params, const GUI &gui) : m_reactionTime(0), m_isKeyPressed(false), m_isRedBoxShown(false), gui(gui) {
    startGame(params, gui);
}

bool Mode2ColorChange::startGame(const StartParams &params, const GUI &gui) {
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
            
            std::string imagePath = dataset.getImageFilePathOfCurrentIndex();

            // Bild wird gezeigt, Spielzug beginnt
            gui.displayImageWithBoundingBoxes(imagePath, boxes, BLUE_COLOR);
            startTurn(boxes, gui);

            dataset.incrementCurrentIndex();

            if (!(i < m_turns)) end = true;
        }
    }
    
    return end;
}

// Spielzug, Verarbeitung von Spieler-Input
void Mode2ColorChange::startTurn(const std::vector<BoundingBox>& boxes, const GUI &gui) {
    boundingBoxes = boxes;
    m_isKeyPressed = false;
    m_isRedBoxShown = false;
    
    if (boundingBoxes.empty()) {
        gui.displayMessage("No bounding boxes provided!");
        return;
    }

    // Zeige alle Boxen in Blau für 2 Sekunden
    Time::timeDelay(2.0f);

    // Wähle zufällig eine Box und setze sie auf Rot
    int randomIndexUpperBound = static_cast<int>(boundingBoxes.size() - 1);
    targetBox = boundingBoxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];
    m_isRedBoxShown = true;
    
    // Maus-Callback registrieren
    cv::setMouseCallback(NAME_OF_THE_GAME, clickCallback, this);

    timer.timeMeasureBegin();

}

void Mode2ColorChange::clickCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        auto mode = static_cast<Mode2ColorChange*>(userdata);
        mode->processClick(x, y);
    }
}

// Verarbeitung eines Mausklicks
void Mode2ColorChange::processClick(int x, int y) {
    if (m_isRedBoxShown && targetBox.contains(x, y)) {
        m_reactionTime = timer.timeMeasureEnd();
        //gui.displayMessage("Hit! Reaction time: " + std::to_string(m_reactionTime) + " seconds");
    } else {
        m_reactionTime += m_penaltyTime;
        //gui.displayMessage("Miss! 5 second penalty!");
    }
    
    // Reaktionszeit speichern
    player.addReactionTime(m_reactionTime);
}

// Verarbeitung eines Tastaturanschlags
void Mode2ColorChange::processKeyPress(int key) {
    if (key == ' ') { // Assuming space key is used for confirmation
        m_isKeyPressed = true;
    }
}

