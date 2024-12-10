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
    //Player m_player(params.getPlayerName());
    m_player.setName(params.getPlayerName());
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

            // Alle validen Boxen des aktuellen Indexes auslesen
            std::vector<BoundingBox> boxes = dataset.getBoundingBoxesOfCurrentFrame();
            if (boxes.empty()) {
                gui.displayMessage("No valid bounding box found in remaining images.");
                return end;
            }
            // Zufällig rote Box auswählen
            int randomIndexUpperBound = static_cast<int>(boxes.size() - 1);
            targetBox = boxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];
            
            std::string imagePath = dataset.getImageFilePathOfCurrentIndex();

            
            cv::namedWindow(NAME_OF_THE_GAME);

            // Maus-Callback registrieren
            m_mouseClicked = false;
            m_isKeyPressed = false;
            m_isRedBoxShown = false;
            cv::setMouseCallback(NAME_OF_THE_GAME, clickCallback, this);

            // Bild mit allen Bounding Boxen (blau) wird gezeigt
            gui.displayImageWithBoundingBoxes(imagePath, boxes, BLUE_COLOR);

            // Zeige alle Boxen in Blau für 2 Sekunden
            Time::timeDelay(2.0f);

            // Zeige rote Box, Spielzug beginnt
            m_isRedBoxShown = true;
            std::vector<BoundingBox> redBoxes = {targetBox};
            gui.displayImageWithDifferentBoundingBoxes(imagePath, redBoxes, RED_COLOR, boxes, BLUE_COLOR);
            gui.displayMessage("\n\nTurn Nr. " + std::to_string(i) + " has begun!");
            timer.timeMeasureBegin();

            // Hier auf Mausklick warten
            while (true) {
                if (cv::waitKey(1) == 27) { // Escape zum Verlassen
                    break;
                }
                if (m_mouseClicked) {
                    break;
                }
            }

            cv::setMouseCallback(NAME_OF_THE_GAME, nullptr, nullptr);

            dataset.incrementCurrentIndex();

            if (!(i < m_turns)) end = true;
        }
    }
    gui.showScoreboard(m_player);
    return end;
}

void Mode2ColorChange::clickCallback(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        auto mode = static_cast<Mode2ColorChange*>(userdata);
        mode->processClick(x, y);
        mode->m_mouseClicked = true;
    }
}

void Mode2ColorChange::processClick(int x, int y) { // Verarbeitung eines Mausklicks
    if (targetBox.contains(x, y)) {
       
        m_reactionTime = timer.timeMeasureEnd();

        m_player.addHitTime(m_reactionTime);
        
        m_totalTime += m_reactionTime;
        m_player.addReactionTime(m_reactionTime);

        
        timer.timeMeasureBegin();
        gui.displayMessage("\nHit! Reaction time: " + std::to_string(m_reactionTime) + " seconds\n");
    } else {
       // m_reactionTime = timer.timeMeasureEnd();
        //timer.timeMeasureBegin();
        m_reactionTime = m_penaltyTime;

        m_totalTime += m_reactionTime;
        m_player.addReactionTime(m_reactionTime);

        gui.displayMessage("\nMiss! 5 second penalty! Reaction time: " + std::to_string(m_reactionTime) + "\n");
    }
    //m_totalTime += m_reactionTime;
    m_reactionTime = timer.timeMeasureEnd();
}

// Verarbeitung eines Tastaturanschlags
void Mode2ColorChange::processKeyPress(int key) {
    if (key == ' ') { // Assuming space key is used for confirmation
        m_isKeyPressed = true;
    }
}

