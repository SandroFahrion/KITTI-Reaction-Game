#include <gtest/gtest.h>
#include "player.hpp"


//Tests player
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
    player.addHitTime(2.03f);
    player.addHitTime(0.65f);
    player.addHitTime(1.81f);
    player.addHitTime(0.97f);

    // Zugriff auf die gespeicherten Reaktionszeiten
    const std::vector<float>& reactionTimes = player.getHitTimes();

    //Überprüfen, ob die Reaktionszeiten korrekt gespeichert wurden
    ASSERT_EQ(reactionTimes.size(), 4); // Anzahl Zeiten korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[0], 2.03f); // erste Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[1], 0.65f); // zweite Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[2], 1.81f); // dritte Reaktionszeit korrekt?
    EXPECT_FLOAT_EQ(reactionTimes[3], 0.97f); // vierte Reaktionszeit korrekt?
}

