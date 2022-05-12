#include "stdafx.h"

#include "Types/CCollection.h"

#include "gtest/gtest.h"

TEST(UsefulTypesCCollectionTest, ClassInstantiation)
{
    NSTypes::CCollection<int>* collection = new NSTypes::CCollection<int>();

    EXPECT_TRUE(collection);

    SAFE_DELETE(collection);
}

TEST(UsefulTypesCCollectionTest, PushItems)
{
    NSTypes::CCollection<int>* collection = new NSTypes::CCollection<int>();

    collection->FPushFront(8);

    EXPECT_EQ(collection->FCount(), 1);

    collection->FPushBack(16);

    EXPECT_EQ(collection->FCount(), 2);

    SAFE_DELETE(collection);
}

TEST(UsefulTypesCCollectionTest, CheckSize)
{
    NSTypes::CCollection<int>* collection = new NSTypes::CCollection<int>();

    collection->FPushFront(64);

    EXPECT_EQ(collection->FSize(), sizeof(int) * collection->FCount());

    collection->FPushBack(128);

    EXPECT_EQ(collection->FSize(), sizeof(int) * collection->FCount());

    SAFE_DELETE(collection);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
