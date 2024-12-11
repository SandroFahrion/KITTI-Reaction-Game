#include "../../googletest/googletest/include/gtest/gtest.h"
#include "../../googletest/googletest/include/gtest/gtest-assertion-result.h"
#include "player.hpp"
#include "kitti_dataset.hpp"
#include "bounding_box.hpp"
#include "gui.hpp"
#include "image.hpp"
#include "mode_1_direct_click.hpp"
#include "mode_2_color_change.hpp"
#include "mode_3_memory.hpp"
#include <opencv2/opencv.hpp>
#include <sstream>


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


//Tests image.hpp




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




//Tests bounding_box.hpp
//Test Bounding_box::contains

/*TEST(BoundingBoxTest, DefaultConstructor) {
    BoundingBox box;
    EXPECT_EQ(box.getCoordX(), 0);
    EXPECT_EQ(box.getCoordY(), 0);
    EXPECT_EQ(box.getWidthX(), 0);
    EXPECT_EQ(box.getHeightY(), 0);
    EXPECT_EQ(box.getType(), "");
    EXPECT_EQ(box.getFrame(), 0);
}

TEST(BoundingBoxTest, ParameterizedConstructor) {
    std::string type = "TestBox";
    BoundingBox box(type, 10, 100, 200, 50, 60);

    EXPECT_EQ(box.getCoordX(), 100);
    EXPECT_EQ(box.getCoordY(), 200);
    EXPECT_EQ(box.getWidthX(), 50);
    EXPECT_EQ(box.getHeightY(), 60);
    EXPECT_EQ(box.getType(), "TestBox");
    EXPECT_EQ(box.getFrame(), 10);
}*/

TEST(BoundingBoxTest, ContainsMausklick) {
    std::string type = "TestBox";
    BoundingBox box(type, 1, 50, 50, 100, 100);

    EXPECT_TRUE(box.contains(75, 75)); // Mausklick innerhalb der Box
    EXPECT_TRUE(box.contains(50, 50)); // Mausklick genau auf der oberen linken Ecke
    EXPECT_TRUE(box.contains(150, 150)); // Mausklick genau auf der unteren rechten Ecke
    EXPECT_FALSE(box.contains(200, 200)); // Mausklick außerhalb der Box
    EXPECT_FALSE(box.contains(49, 49)); // Mausklick knapp außerhalb der oberen linken Ecke
}


//Tests game_mode.hpp
//Tests mode_1_direct_click.hpp
//Tests mode_2_color_change.hpp
//Tests mode_3_memory.hpp