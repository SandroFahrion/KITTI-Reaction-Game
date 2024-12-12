#include <gtest/gtest.h>
#include "kitti_dataset.hpp"

//Tests kitti_dataset
//Test Kitti_dataset::incrementCurrentIndex
TEST(KittiDatasetTest, IncrementCurrentIndexCorrectly){
    KittiDataset kittidataset("0000");
    int initialIndex = kittidataset.getCurrentIndex();

    kittidataset.incrementCurrentIndex();
    int newIndex = kittidataset.getCurrentIndex();

    EXPECT_EQ(newIndex, initialIndex + 1);
}