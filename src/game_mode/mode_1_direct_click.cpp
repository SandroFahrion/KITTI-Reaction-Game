// umgeformte unterklasse für den Mode 1 - Direct Click Reaction:

#include "game_mode/mode_1_direct_click.hpp"
#include <iostream>
#include <random>

Mode1DirectClick::Mode1DirectClick() : m_reactionTime(0) {}

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

void Mode1DirectClick::startRound(const Image& img, const std::vector<BoundingBox>& boxes) {
    currentImage = img;
    boundingBoxes = boxes;
    
    if (boundingBoxes.empty()) {
        std::cerr << "No bounding boxes provided!" << std::endl;
        return;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, boundingBoxes.size() - 1);
    boundingBox = boundingBoxes[dis(gen)];
    
    m_startTime = std::chrono::high_resolution_clock::now();
}

const std::vector<BoundingBox>& Mode1DirectClick::getBoundingBoxes() const {
    return boundingBoxes;
}

const Image& Mode1DirectClick::getCurrentImage() const {
    return currentImage;
}

float Mode1DirectClick::calculateReactionTime() {
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = endTime - m_startTime;
    return elapsed.count();
}
