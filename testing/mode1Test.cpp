#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game_mode/mode_1_direct_click.hpp"
#include "opencv2/opencv.hpp"
#include "sstream"


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
    Mode1DirectClick mode(params, gui);
    std::string type = "TestBox";
    

    BoundingBox box(type, 1, 10, 10, 50, 50);
    mode.processClick(20, 20);      // innerhalb der Box klicken
    
    EXPECT_GT(mode.getTotalReactionTime(), 0);      //prüfen ob Zeit>0
}

TEST(Mode1DirectClickTest, ProcessClick_Miss) {
    MockGUI gui;
    MockStartParams params;
    Mode1DirectClick mode(params, gui);

    float expectedTime = mode.getReactionTime() + mode.getPenaltyTime();
    mode.processClick(100, 100);        // außerhalb der Box klicken
    
    EXPECT_EQ(mode.getTotalReactionTime(), expectedTime);       //entspricht Zeit der erwarteten Zeit inklusive Strafzeit?
}

