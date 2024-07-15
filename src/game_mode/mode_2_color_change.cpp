// umgeformte unterklasse für den Mode 2 - Color Change Reaction

#include "game_mode/mode_2_color_change.hpp"
#include <iostream>
#include <random>
#include <thread>

Mode2ColorChange::Mode2ColorChange() : m_reactionTime(0), m_isKeyPressed(false), m_isRedBoxShown(false) {}

void Mode2ColorChange::processClick(int x, int y) {
    if (m_isKeyPressed && m_isRedBoxShown && targetBox.contains(x, y)) {
        m_reactionTime = calculateReactionTime();
        std::cout << "Hit! Reaction time: " << m_reactionTime << " seconds" << std::endl;
    } else {
        m_reactionTime += m_penaltyTime;
        std::cout << "Miss! 5 second penalty!" << std::endl;
    }
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, boundingBoxes.size() - 1);
    targetBox = boundingBoxes[dis(gen)];
    m_isRedBoxShown = true;
    m_startTime = std::chrono::high_resolution_clock::now();
}

void Mode2ColorChange::processKeyPress(int key) {
    if (key == ' ') { // Assuming space key is used for confirmation
        m_isKeyPressed = true;
        std::cout << "Key pressed! You can now click on the target." << std::endl;
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
