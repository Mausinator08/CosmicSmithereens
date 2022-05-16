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

    EXPECT_EQ(collection->FPopFront(), 64);

    EXPECT_EQ(collection->FActiveSize(), sizeof(int) * collection->FActiveCount());

    EXPECT_EQ(collection->FPopFront(), 128);

    EXPECT_EQ(collection->FActiveSize(), sizeof(int) * collection->FActiveCount());

    SAFE_DELETE(collection);
}

TEST(UsefulTypesCCollectionTest, SetAndGetItem)
{
    NSTypes::CCollection<int>* collection = new NSTypes::CCollection<int>();

    collection->FPushBack(1);
    int item = 0;
    collection->FGet(0, &item);

    EXPECT_EQ(item, 1);

    collection->FSet(2, 0);
    collection->FGet(0, &item);

    EXPECT_EQ(item, 2);

    collection->FInsertAt(item + 1, 0);
    int insertedItem = 0;
    collection->FGet(0, &insertedItem);
    collection->FGet(1, &item);

    EXPECT_EQ(insertedItem, 3);
    EXPECT_EQ(item, 2);

    collection->FInsertAt(4, 1);

    int front, back = 0;
    collection->FFront(&front);
    collection->FBack(&back);

    EXPECT_EQ(front, 3);
    EXPECT_EQ(back, 2);

    SAFE_DELETE(collection);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
