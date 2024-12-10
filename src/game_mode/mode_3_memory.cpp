// Spielmodus 3 - Memory

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#ifndef NAME_OF_THE_GAME
#define NAME_OF_THE_GAME "KITTI Reaction Game"
#endif // NAME_OF_THE_GAME

#include "game_mode/mode_3_memory.hpp"

//Konstruktor
Mode3Memory::Mode3Memory(const StartParams &params, const GUI &gui) : m_reactionTime(0), m_isKeyPressed(false), m_isRedBoxShown(false), m_allowClicks(false), gui(gui), m_sequenceIndex(0) {
    startGame(params, gui);
}

bool Mode3Memory::startGame(const StartParams &params, const GUI &gui) {
    //Player player(params.getPlayerName());
    m_player.setName(params.getPlayerName());
    // KittiDataset Konstruktor enthält
    // loadBoxDataset(seq);
    // loadImagePaths(seq);
    // setRandomStartIndex();
    KittiDataset dataset(params.getSequence());

//Scheife, um die Anzahl der gewünschten Spielzüge zu wiederholen, kann bei Fehler unterbrochen werden
m_turns = params.getNumTurns();
bool end = false;
while (!end){
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
        BoundingBox targetBox = boxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];
            
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


        m_sequence.clear();
        for (int i = 0; i < 5; ++i) { // Beispiel: 5 Boxen pro Runde
            m_sequence.push_back(boxes[KittiRandom::selectIntRandom(0, boxes.size() - 1)]);
        }
        m_sequenceIndex = 0;

        for (const auto &box : m_sequence) {
            m_allowClicks = false;

            gui.displayImageWithBoundingBoxes(dataset.getImageFilePathOfCurrentIndex(), boxes, BLUE_COLOR);
            Time::timeDelay(1.0f); // Blau für 1 Sekunde anzeigen

            std::vector<BoundingBox> redBox = {box};
            gui.displayImageWithDifferentBoundingBoxes(dataset.getImageFilePathOfCurrentIndex(), redBox, RED_COLOR, boxes, BLUE_COLOR);
            Time::timeDelay(0.5f); // Rot für halbe Sekunde anzeigen
        
            // Zeige die Boxen wieder in Blau
            gui.displayImageWithBoundingBoxes(dataset.getImageFilePathOfCurrentIndex(), boxes, BLUE_COLOR);
            timer.timeMeasureBegin();
        }
        m_allowClicks = true;
        gui.displayMessage("Click the boxes in the correct sequence!");

        while (m_sequenceIndex < m_sequence.size()) {
            if (cv::waitKey(1) == 27) { // Escape zum Verlassen
                return false;
            }
            if (m_mouseClicked) {
                m_mouseClicked = false; // Nächsten Klick erwarten
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





void Mode3Memory::clickCallback(int event, int x, int y, int flags, void *userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        auto mode = static_cast<Mode3Memory*>(userdata);
        mode->processClick(x, y);
        mode->m_mouseClicked = true;
    }
}

void Mode3Memory::processClick(int x, int y) { // Verarbeitung eines Mausklicks
    
    if (!m_allowClicks) {
        return; // Ignore clicks if not allowed
    }
    
    
    if (m_sequenceIndex < m_sequence.size() && m_sequence[m_sequenceIndex].contains(x, y)) {
        m_reactionTime = timer.timeMeasureEnd();
        m_player.addHitTime(m_reactionTime);
        m_reactionTime += m_penaltyTime * m_missedClicks;
        m_totalTime += m_reactionTime;
        m_player.addReactionTime(m_reactionTime);        // Reaktionszeit speichern
        m_missedClicks = 0;
        timer.timeMeasureBegin();
        gui.displayMessage("\nHit! Reaction time: " + std::to_string(m_reactionTime) + " seconds\n");
        ++m_sequenceIndex;
    } else {
        m_missedClicks++;
        gui.displayMessage("\nMiss! 5 seconds penalty.\n");    
    }

     
}



// Verarbeitung eines Tastaturanschlags
void Mode3Memory::processKeyPress(int key) {
    if (key == ' ') { // Assuming space key is used for confirmation
        m_isKeyPressed = true;
    }
}

