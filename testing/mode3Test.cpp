#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game_mode/mode_3_memory.hpp"
#include "opencv2/opencv.hpp"
#include "sstream"


// Mock-Klassen für Abhängigkeiten
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


//Tests mode_3_memory
//Test Mode_3_memory::startGame
TEST(Mode3MemoryTest, StartGameCorrectly) {
    MockGUI gui;
    MockStartParams params;
    Mode3Memory mode(params, gui);

    EXPECT_TRUE(mode.startGame(params, gui));
}

TEST(Mode3MemoryTest, ProcessClick_Hit) {
    MockGUI gui;
    MockStartParams params;
    Mode3Memory mode(params, gui);
    std::string type = "TestBox";
    

    BoundingBox box(type, 1, 10, 10, 50, 50);
    mode.processClick(20, 20);      // innerhalb der Box klicken 
    
    EXPECT_GT(mode.getTotalReactionTime(), 0); //prüfen ob Zeit>0
}

TEST(ModeMemoryTest, ProcessClick_Miss) {
    MockGUI gui;
    MockStartParams params;
    Mode3Memory mode(params, gui);

    float expectedTime = mode.getReactionTime() + mode.getPenaltyTime();
    mode.processClick(100, 100);    // außerhalb der Box klicken
    
    EXPECT_EQ(mode.getTotalReactionTime(), expectedTime);   //entspricht Zeit der erwarteten Zeit inklusive Strafzeit?
}

/*TEST(Mode3MemoryTest, ClickCallbackProcessesClick) {
    // Arrange
    StartParams params("TestPlayer", "TestSequence", 5);
    GUI gui;
    Mode3Memory mode(params, gui);
    std::string type = "TestBox";

    int testX = 50, testY = 50;
    int event = cv::EVENT_LBUTTONDOWN;
    int flags = 0;

    bool m_allowClicks = true;
    mode.getClicksAllowed(); // Ensure clicks are allowed
    mode.m_sequence.push_back(BoundingBox{type, 1, 50, 50, 100, 100}); // Add a target box
    mode.getCurrentSequenceIndex(0);

    // Act
    Mode3Memory::clickCallback(event, testX, testY, flags, &mode);

    // Assert
    ASSERT_TRUE(mode.m_mouseClicked); // Verify that the mouse click was registered
    ASSERT_EQ(mode.m_sequenceIndex, 1); // Verify that the sequence index was incremented
}*/

