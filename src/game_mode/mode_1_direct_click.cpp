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

            std::vector<BoundingBox> boxes = dataset.getBoundingBoxesOfCurrentFrame();
            if (boxes.empty()) {
                std::cerr << "No valid bounding box found in remaining images." << std::endl;
                return end;
            }
            int randomIndexUpperBound = static_cast<int>(boxes.size() - 1);
            BoundingBox box = boxes[KittiRandom::selectIntRandom(0, randomIndexUpperBound)];

            std::string imagePath = dataset.getImageFilePathOfCurrentIndex();
            Image img(imagePath);

            gui.displayImageWithBoundingBox(img, box, RED_COLOR);
            
            startTurn(img, boxes);

            dataset.setCurrentIndex(dataset.getCurrentIndex() + 1);

            if (!(i < m_turns)) end = true;
        }
    }
    
    return end;
}

void Mode1DirectClick::startTurn(const Image &img, const std::vector<BoundingBox>& boxes) {
    m_startTime = std::chrono::high_resolution_clock::now();
    
    cv::Point cursorPos;
 
    processClick(cursorPos.x, cursorPos.y);
}

void Mode1DirectClick::processClick(int x, int y) {
    if (boundingBox.contains(x, y)) {
        m_reactionTime = calculateReactionTime();
        std::cout << "Hit! Reaction time: " << m_reactionTime << " seconds" << std::endl;
    } else {
        m_reactionTime += m_penaltyTime;
        std::cout << "Miss! 5 second penalty!" << std::endl;
    }
}

void Mode1DirectClick::processKeyPress(int key) {
    // Keine Tastatureingabe in diesem Modus
}

const std::vector<BoundingBox>& Mode1DirectClick::getBoundingBoxes() const {
    return boundingBoxes;
}

const Image& Mode1DirectClick::getCurrentImage() const {
    return currentImage;
}

float Mode1DirectClick::calculateReactionTime() {
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> reactionTime = endTime - m_startTime;
    return reactionTime.count();
}
