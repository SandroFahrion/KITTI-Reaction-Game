#include <gtest/gtest.h>
#include "bounding_box.hpp"
#include "sstream"

//Tests bounding_box
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

