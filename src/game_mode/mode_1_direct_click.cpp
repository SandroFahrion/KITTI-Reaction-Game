// Spielmodus 1 - Direct Click Reaction

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#ifndef NAME_OF_THE_GAME
#define NAME_OF_THE_GAME "KITTI Reaction Game"
#endif // NAME_OF_THE_GAME

#include <iostream>

#include "game_mode/mode_1_direct_click.hpp"

// Konstruktor
Mode1DirectClick::Mode1DirectClick(const StartParams &params, const GUI &gui) : m_reactionTime(0), gui(gui) {
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

    // Maus-Callback registrieren
    cv::setMouseCallback(NAME_OF_THE_GAME, clickCallback, this);

    // Bild für 3 Sekunden anzeigen
    Time::timeDelay(3.0f);

}

void Mode1DirectClick::clickCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        auto mode = static_cast<Mode1DirectClick*>(userdata);
        mode->processClick(x, y);
    }
}

// Verarbeitung eines Mausklicks
void Mode1DirectClick::processClick(int x, int y) {
    if (boundingBox.contains(x, y)) {
        m_reactionTime = timer.timeMeasureEnd();
        std::cout << "Hit! Reaction time: " << std::to_string(m_reactionTime) << " seconds";
        //gui.displayMessage("Hit! Reaction time: " + std::to_string(m_reactionTime) + " seconds");
    } else {
        m_reactionTime += m_penaltyTime;
        std::cout << "Miss! 5 second penalty!";
        //gui.displayMessage("Miss! 5 second penalty!");
    }

    // Reaktionszeit speichern
    player.addReactionTime(m_reactionTime);
}

void Mode1DirectClick::processKeyPress(int key) {
    // Keine Tastatureingabe in diesem Modus
}
