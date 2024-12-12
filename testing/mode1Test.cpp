#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mode_1_direct_click.hpp"
#include "opencv2/opencv.hpp"


class MockGUI : public GUI {
public:
    void displayMessage(const std::string &message) {
        lastMessage = message;
    }

    void displayImageWithBoundingBoxes(const std::string &imagePath, const std::vector<BoundingBox> &boxes, const cv::Scalar &color) {
        lastImagePath = imagePath;
        lastBoxes = boxes;
        lastColor = color;
    }

    std::string lastMessage;
    std::string lastImagePath;
    std::vector<BoundingBox> lastBoxes;
    cv::Scalar lastColor;
   // float MockGUI::getTotalReactionTime();

};

class MockStartParams : public StartParams {
public:
    std::string getPlayerName() const { return "TestPlayer"; }
    int getNumTurns() const { return 1; }
    std::string getSequence() const { return "TestSequence"; }
};

// Unit-Tests

//Tests mode_1_direct_click
//Test Mode_1_direct_click::startGame
TEST(Mode1DirectClickTest, StartGameCorrectly) {
    MockGUI gui;
    MockStartParams params;
    Mode1DirectClick mode(params, gui);

    EXPECT_TRUE(mode.startGame(params, gui));
}

//Test Mode_1_direct_click::processClick
TEST(Mode1DirectClickTest, ProcessClick_Hit) {
    MockGUI gui;
    MockStartParams params;
    //float MockGUI::getTotalReactionTime();
    Mode1DirectClick mode(params, gui);
    std::string type = "TestBox";
    

    BoundingBox box(type, 1, 10, 10, 50, 50);
    mode.processClick(20, 20); // Click within the bounding box
    
    // Check if reaction time was recorded (mock the timer if needed)
    EXPECT_GT(mode.getTotalReactionTime(), 0);
}

TEST(Mode1DirectClickTest, ProcessClick_Miss) {
    MockGUI gui;
    MockStartParams params;
    Mode1DirectClick mode(params, gui);

    float expectedTime = mode.getReactionTime() + mode.getPenaltyTime();
    mode.processClick(100, 100); // Click outside any bounding box
    // Verify penalty time was added
    EXPECT_EQ(mode.getTotalReactionTime(), expectedTime);
}
