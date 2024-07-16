// umgeformte unterklasse für den Mode 2 - Color Change Reaction

#ifdef DEBUG_MODE
#include "../helpers/debug/debug.hpp"
#endif // DEBUG_MODE

#include "game_mode/mode_2_color_change.hpp"

Mode2ColorChange::Mode2ColorChange(const StartParams &params, const GUI &gui) : m_reactionTime(0), m_isKeyPressed(false), m_isRedBoxShown(false) {
    startGame(params, gui);
}

bool Mode2ColorChange::startGame(const StartParams &params, const GUI &gui) {
    
    Player player(params.getPlayerName());
    KittiDataset dataset(params.getSequence());
    m_turns = params.getNumTurns();

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
            startRound(img, boxes);
            
            if (getBoxDisplayCount() == SHOW_ALL_BOXES) {
                gui.displayImageWithBoundingBoxes(getCurrentImage(), getBoundingBoxes(), BLUE_COLOR);
                //gui.displayCountdown("Wait for the target...");
                //std::this_thread::sleep_for(std::chrono::seconds(2));
                gui.displayImageWithBoundingBox(getCurrentImage(), getBoundingBoxes().at(0), RED_COLOR);
                //gui.displayMessage("Go!");
            }
            else{
                for (int i = 0; i < getBoxDisplayCount(), i++;){

                }
            }

            int key;
            cv::Point cursorPos;
            float reactionTime = gui.measureReactionTime(key, cursorPos);

            processClick(cursorPos.x, cursorPos.y);

            dataset.setCurrentIndex(dataset.getCurrentIndex() + 1);

            if (!(i < m_turns)) end = true;
        }
    }
    
    return end;
}

void Mode2ColorChange::startRound(const Image& img, const std::vector<BoundingBox>& boxes) {
    currentImage = img;
    boundingBoxes = boxes;
    m_isKeyPressed = false;
    m_isRedBoxShown = false;
    
    if (boundingBoxes.empty()) {
        std::cerr << "No bounding boxes provided!" << std::endl;
        return;
    }

    // Zeige alle Boxen in Blau für 2 Sekunden
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Wähle zufällig eine Box und setze sie auf Rot
    int randomIndexUpperBound = static_cast<int>(boundingBoxes.size() - 1);
    targetBox = boundingBoxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];
    m_isRedBoxShown = true;
    m_startTime = std::chrono::high_resolution_clock::now();
}

void Mode2ColorChange::processClick(int x, int y) {
    if (m_isRedBoxShown && targetBox.contains(x, y)) {
        m_reactionTime = calculateReactionTime();
        std::cout << "Hit! Reaction time: " << m_reactionTime << " seconds" << std::endl;
    } else {
        m_reactionTime += m_penaltyTime;
        std::cout << "Miss! 5 second penalty!" << std::endl;
    }
}

void Mode2ColorChange::processKeyPress(int key) {
    if (key == ' ') { // Assuming space key is used for confirmation
        m_isKeyPressed = true;
    }
}

const std::vector<BoundingBox>& Mode2ColorChange::getBoundingBoxes() const {
    return boundingBoxes;
}

const Image& Mode2ColorChange::getCurrentImage() const {
    return currentImage;
}

float Mode2ColorChange::calculateReactionTime() {
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = endTime - m_startTime;
    return elapsed.count();
}
