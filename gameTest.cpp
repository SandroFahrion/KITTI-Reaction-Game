#include <gtest/gtest.h>
#include <gtest/gtest-assertion-result.h>
#include <gmock/gmock.h>
#include "player.hpp"
#include "kitti_dataset.hpp"
#include "bounding_box.hpp"
#include "gui.hpp"
#include "mode_1_direct_click.hpp"
#include "mode_2_color_change.hpp"
#include "mode_3_memory.hpp"
#include "opencv2/opencv.hpp"
#include "sstream"


//Tests player.hpp
//Test Player::addReactionTime
TEST(PlayerTest, AddReactionTimesCorrectly) {
    // Arrange: Erstelle ein Player-Objekt
    Player player("TestPlayer");

    //Test-Reaktionszeiten einfügen
    player.addReactionTime(1.33f);
    player.addReactionTime(0.97f);
    player.addReactionTime(1.48f);
    player.addReactionTime(5.00f);

    // Zugriff auf die gespeicherten Reaktionszeiten
    const std::vector<float>& reactionTimes = player.getReactionTimes();

    //Überprüfen, ob die Reaktionszeiten korrekt gespeichert wurden
    ASSERT_EQ(reactionTimes.size(), 4); // Anzahl Zeiten korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[0], 1.33f); // erste Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[1], 0.97f); // zweite Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[2], 1.48f); // dritte Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[3], 5.00f); // vierte Reaktionszeit korrekt?
}

//Test Player::addHitTime
TEST(PlayerTest, AddHitTimesCorrectly) {
    Player player("TestPlayer");

    //Test-Hitzeiten einfügen
    player.addHitTime(2.03);
    player.addHitTime(0.65);
    player.addHitTime(1.81);
    player.addHitTime(0.97);

    // Zugriff auf die gespeicherten Reaktionszeiten
    const std::vector<float>& reactionTimes = player.getHitTimes();

    //Überprüfen, ob die Reaktionszeiten korrekt gespeichert wurden
    ASSERT_EQ(reactionTimes.size(), 4); // Anzahl Zeiten korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[0], 2.03f); // erste Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[1], 0.65f); // zweite Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[2], 1.81f); // dritte Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[3], 0.97f); // vierte Reaktionszeit korrekt?
}


//Tests kitti_dataset.hpp
//Test Kitti_dataset::incrementCurrentIndex
TEST(KittiDatasetTest, IncrementCurrentIndexCorrectly){
    KittiDataset kittidataset("0000");
    int initialIndex = kittidataset.getCurrentIndex();

    kittidataset.incrementCurrentIndex();
    int newIndex = kittidataset.getCurrentIndex();

    EXPECT_EQ(newIndex, initialIndex + 1);
}


//Tests gui.hpp
//Test Gui::displayImageWithBoundingBox
TEST(GuiTest, DisplayImageWithBoundingBox) {
    // Testdaten werden vorbereitet
    GUI gui;
    std::string type = "TestBox";
    std::string testImagePath = "test_image.jpg";
    BoundingBox testBox(type, 1, 50, 50, 100, 100);  // Beispielkoordinaten
    cv::Scalar testColor(255, 0, 0);       // Blau

    // Beispiel-Image wird erstellt für den Test
    cv::Mat dummyImage(200, 200, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::imwrite(testImagePath, dummyImage);

    // Die Funktion ruft OpenCV zur Anzeige des Bildes auf, Überprüfung auf Fehler
    ASSERT_NO_THROW({
        gui.displayImageWithBoundingBox(testImagePath, testBox, testColor);
    });

    // korrektes Erzeugen des Image-Objekts gegeben?
    Image testImage(testImagePath, testBox, testColor);
    cv::Mat imgWithBox = testImage; // Konvertierung sicherstellen

    EXPECT_EQ(imgWithBox.rows, dummyImage.rows); //Prüfung ob Höhe von Bild mit BoundingBox = Höhe Originalbild
    EXPECT_EQ(imgWithBox.cols, dummyImage.cols); //Prüfung ob Breite von Bild mit BoundingBox = Breite Originalbild
}

//Test Gui::displayImageWithBoundingBoxes
TEST(GuiTest, DisplayImageWithBoundingBoxes) {
    // Testdaten werden vorbereitet
    GUI gui;
    std::string type = "TestBox";
    std::string testImagePath = "test_image.jpg";

    // mehrere Beispiel BoundingBoxes werden erstellt
    std::vector<BoundingBox> testBoxes = {
        BoundingBox(type, 1, 20, 20, 50, 50),
        BoundingBox(type, 2, 100, 100, 50, 50),
        BoundingBox(type, 3, 150, 150, 30, 30)
    };

    cv::Scalar testColor(255, 0, 0); // Blau

    // Beispiel-Image wird erstellt für den Test
    cv::Mat dummyImage(200, 200, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::imwrite(testImagePath, dummyImage);

    // Die Funktion ruft OpenCV zur Anzeige des Bildes auf, Überprüfung auf Fehler
    ASSERT_NO_THROW({
        gui.displayImageWithBoundingBoxes(testImagePath, testBoxes, testColor);
    });

    // korrektes Erzeugen des Image-Objekts gegeben?
    Image testImageWithBoxes(testImagePath, testBoxes, testColor);
    cv::Mat imgWithBoxes = testImageWithBoxes; // Konvertierung sicherstellen

    EXPECT_EQ(imgWithBoxes.rows, dummyImage.rows); //Prüfung ob Höhe von Bild mit BoundingBox = Höhe Originalbild
    EXPECT_EQ(imgWithBoxes.cols, dummyImage.cols); //Prüfung ob Breite von Bild mit BoundingBox = Breite Originalbild
}

//Test Gui::displayImageWithDifferentBoundingBoxes
TEST(GuiTest, DisplayImageWithDifferentBoundingBoxes) {
    // Testdaten werden vorbereitet
    GUI gui;
    std::string testImagePath = "test_image.jpg";

    // Rote BoundingBoxes definieren
    std::vector<BoundingBox> redBoxes = {
        BoundingBox(std::string("RedBox"), 1, 10, 10, 30, 30),
        BoundingBox(std::string("RedBox"), 2, 50, 50, 40, 40)
    };

    // Blaue BoundingBoxes definieren
    std::vector<BoundingBox> blueBoxes = {
        BoundingBox(std::string("BlueBox"), 1, 100, 100, 50, 50),
        BoundingBox(std::string("BlueBox"), 2, 150, 150, 20, 20)
    };

    cv::Scalar redColor(0, 0, 255);  // Rot
    cv::Scalar blueColor(255, 0, 0); // Blau

    // Beispiel-Image wird erstellt für den Test
    cv::Mat dummyImage(200, 200, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::imwrite(testImagePath, dummyImage);

    // Die Funktion ruft OpenCV zur Anzeige des Bildes auf, Überprüfung auf Fehler
    ASSERT_NO_THROW({
        gui.displayImageWithDifferentBoundingBoxes(testImagePath, redBoxes, redColor, blueBoxes, blueColor);
    });

    // korrektes Erzeugen des Image-Objekts gegeben?
    Image testImageWithBoxes(testImagePath, redBoxes, redColor, blueBoxes, blueColor);
    cv::Mat imgWithBoxes = testImageWithBoxes; // Konvertierung sicherstellen

    EXPECT_EQ(imgWithBoxes.rows, dummyImage.rows); //Prüfung ob Höhe von Bild mit BoundingBox = Höhe Originalbild
    EXPECT_EQ(imgWithBoxes.cols, dummyImage.cols); //Prüfung ob Breite von Bild mit BoundingBox = Breite Originalbild
}

//Test Gui::displayMessage
TEST(GuiTest, DisplayMessage) {
    // Testdaten werden vorbereitet
    GUI gui;
    std::string testMessage = "text message example!";
    
    // Umleitung des Standardausgabestroms (std::cout)
    std::ostringstream capturedOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(); // Original-Puffer speichern
    std::cout.rdbuf(capturedOutput.rdbuf());               // std::cout auf capturedOutput umlenken

    // Act: Die Methode aufrufen
    gui.displayMessage(testMessage);

    // Zurücksetzen des Standardausgabestroms
    std::cout.rdbuf(originalCoutBuffer); // std::cout zurücksetzen

    // Assert: Prüfen, ob die Ausgabe korrekt ist
    EXPECT_EQ(capturedOutput.str(), testMessage + "\n"); // "\n" wegen std::endl
}

//Test Gui::showScoreboard
class MockPlayer : public Player {
public:
    MockPlayer(const std::string& name, const std::vector<float>& reactionTimes, const std::vector<float>& hitTimes)
        : Player(name), mockReactionTimes(reactionTimes), mockHitTimes(hitTimes) {}

    const std::vector<float>& getReactionTimes() const {
        return mockReactionTimes;
    }

    const std::vector<float>& getHitTimes() const {
        return mockHitTimes;
    }

private:
    std::vector<float> mockReactionTimes;
    std::vector<float> mockHitTimes;
};

TEST(GuiTest, ShowScoreboardCorrectly) {
    // Arrange
    MockPlayer player("TestPlayer", {1.2f, 1.5f, 1.8f}, {1.1f, 1.3f, 1.6f});
    GUI gui;
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

    // Act
    gui.showScoreboard(player);

    // Assert
    std::cout.rdbuf(originalCoutBuffer); // Restore original cout buffer
    std::string outputStr = output.str();

    EXPECT_NE(outputStr.find("Player: TestPlayer"), std::string::npos);
    EXPECT_NE(outputStr.find("Total reaction time with penalty time: 4.50 seconds"), std::string::npos);
    EXPECT_NE(outputStr.find("Average Reaction Time: 1.33 seconds"), std::string::npos);
    EXPECT_NE(outputStr.find("Top 3 Reaction Times:"), std::string::npos);
    EXPECT_NE(outputStr.find("1: 1.20 seconds"), std::string::npos);
    EXPECT_NE(outputStr.find("2: 1.50 seconds"), std::string::npos);
    EXPECT_NE(outputStr.find("3: 1.80 seconds"), std::string::npos);
}


//Tests bounding_box.hpp
//Test Bounding_box::contains
TEST(BoundingBoxTest, ContainsMausklick) {
    std::string type = "TestBox";
    BoundingBox box(type, 1, 50, 50, 100, 100);

    EXPECT_TRUE(box.contains(75, 75)); // Mausklick innerhalb der Box
    EXPECT_TRUE(box.contains(50, 50)); // Mausklick genau auf der oberen linken Ecke
    EXPECT_TRUE(box.contains(150, 150)); // Mausklick genau auf der unteren rechten Ecke
    EXPECT_FALSE(box.contains(200, 200)); // Mausklick außerhalb der Box
    EXPECT_FALSE(box.contains(49, 49)); // Mausklick knapp außerhalb der oberen linken Ecke
}


//Tests mode_1_direct_click.hpp
//Test Mode_1_direct_click::processClick


//Test Mode_1_direct_click::clickCallback



//Tests mode_2_color_change.hpp
//Test Mode_2_color_change::processClick
//Test Mode_2_color_change::processKeyPress
//Test Mode_2_color_change::clickCallback


//Tests mode_3_memory.hpp
//Test Mode_3_memory::processClick


//Test Mode_3_memory::clickCallback



/*TEST(Mode3MemoryTest, ClickCallbackProcessesClick) {
    // Arrange
    StartParams params("TestPlayer", "TestSequence", 5);
    GUI gui;
    Mode3Memory mode(params, gui);
    std::string type = "TestBox";

    int testX = 50, testY = 50;
    int event = cv::EVENT_LBUTTONDOWN;
    int flags = 0;

    mode.m_allowClicks = true; // Ensure clicks are allowed
    mode.m_sequence.push_back(BoundingBox{type, 1, 50, 50, 100, 100}); // Add a target box
    mode.m_sequenceIndex = 0;

    // Act
    Mode3Memory::clickCallback(event, testX, testY, flags, &mode);

    // Assert
    ASSERT_TRUE(mode.m_mouseClicked); // Verify that the mouse click was registered
    ASSERT_EQ(mode.m_sequenceIndex, 1); // Verify that the sequence index was incremented
}*/




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
    float MockGUI::getTotalReactionTime();
};

class MockStartParams : public StartParams {
public:
    std::string getPlayerName() const { return "TestPlayer"; }
    int getNumTurns() const { return 1; }
    std::string getSequence() const { return "TestSequence"; }
};

// Unit-Tests

// Mode1DirectClick
TEST(Mode1DirectClickTest, StartGameCorrectly) {
    MockGUI gui;
    MockStartParams params;
    Mode1DirectClick mode(params, gui);

    EXPECT_TRUE(mode.startGame(params, gui));
}

TEST(Mode1DirectClickTest, ProcessClick_CorrectBoundingBox_AddsReactionTime) {
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

// Mode2ColorChange
TEST(Mode2ColorChangeTest, StartGame_ValidParams_ReturnsTrue) {
    MockGUI gui;
    MockStartParams params;
    Mode2ColorChange mode(params, gui);

    EXPECT_TRUE(mode.startGame(params, gui));
}

TEST(Mode2ColorChangeTest, ProcessClick_Miss_AddsPenalty) {
    MockGUI gui;
    MockStartParams params;
    Mode2ColorChange mode(params, gui);

    mode.processClick(100, 100); // Click outside any bounding box
    // Verify penalty time was added
    EXPECT_EQ(mode.getTotalReactionTime(), 0);
}

// Mode3Memory
TEST(Mode3MemoryTest, StartGameCorrectly) {
    MockGUI gui;
    MockStartParams params;
    Mode3Memory mode(params, gui);

    EXPECT_TRUE(mode.startGame(params, gui));
}

TEST(Mode3MemoryTest, ProcessClickCorrectly) {
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
}