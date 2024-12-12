#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "gui.hpp"
#include "opencv2/opencv.hpp"

//Tests gui
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