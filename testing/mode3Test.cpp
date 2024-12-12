#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mode_3_memory.hpp"
#include "opencv2/opencv.hpp"


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
   // float MockGUI::getTotalReactionTime();

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

//Test Mode_3_memory::processClick
/*TEST(Mode3MemoryTest, ProcessClickedCorrectSequence) {
    MockGUI gui;
    MockStartParams params;
    Mode3Memory mode(params, gui);
    //std::string type = "TestBox";

    // Start game to initialize sequence
    mode.startGame(params, gui);

    // Mock clicks based on the initialized sequence (assume known sequence for simplicity)
    mode.processClick(20, 20); // First box
    mode.processClick(70, 70); // Second box

    EXPECT_EQ(mode.getCurrentSequenceIndex(), 2); // All boxes clicked in sequence
}*/

TEST(Mode3MemoryTest, ProcessClick_Hit) {
    MockGUI gui;
    MockStartParams params;
    //float MockGUI::getTotalReactionTime();
    Mode3Memory mode(params, gui);
    std::string type = "TestBox";
    

    BoundingBox box(type, 1, 10, 10, 50, 50);
    mode.processClick(20, 20); // Click within the bounding box
    
    // Check if reaction time was recorded (mock the timer if needed)
    EXPECT_GT(mode.getTotalReactionTime(), 0);
}

TEST(ModeMemoryTest, ProcessClick_Miss) {
    MockGUI gui;
    MockStartParams params;
    Mode3Memory mode(params, gui);

    float expectedTime = mode.getReactionTime() + mode.getPenaltyTime();
    mode.processClick(100, 100); // Click outside any bounding box
    // Verify penalty time was added
    EXPECT_EQ(mode.getTotalReactionTime(), expectedTime);
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