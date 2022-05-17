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

    EXPECT_EQ(collection->FGet(0), 1);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    collection->FSet(2, 0);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    
    EXPECT_EQ(collection->FGet(0), 2);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    collection->FInsertAt(collection->FGet(0) + 1, 0);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    EXPECT_EQ(collection->FGet(0), 3);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FGet(1), 2);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    collection->FInsertAt(4, 1);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    EXPECT_EQ(collection->FFront(), 3);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FBack(), 2);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    SAFE_DELETE(collection);
}

TEST(UsefulTypesCCollectionTest, EraseAndRemove)
{
    NSTypes::CCollection<int>* collection = new NSTypes::CCollection<int>();

    collection->FPushBack(1);

    EXPECT_EQ(collection->FGet(0), 1);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FCount(), 1);

    collection->FErase(0);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);

    EXPECT_EQ(collection->FCount(), 1);
    EXPECT_EQ(collection->FActiveCount(), 0);

    collection->FPushBack(2);

    EXPECT_EQ(collection->FGet(0), 0);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FCount(), 1);
    EXPECT_EQ(collection->FActiveCount(), 1);

    EXPECT_EQ(collection->FRemove(2), 1);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FCount(), 1);
    EXPECT_EQ(collection->FActiveCount(), 0);

    collection->FPushBack(1);
    collection->FPushBack(2);
    collection->FPushBack(1);

    EXPECT_EQ(collection->FCount(), 4);
    EXPECT_EQ(collection->FActiveCount(), 3);

    EXPECT_EQ(collection->FRemove(1), 2);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FCount(), 4);
    EXPECT_EQ(collection->FActiveCount(), 1);
    EXPECT_EQ(collection->FRemove(2), 1);
    EXPECT_EQ(collection->FGetLastError(), NSTypes::EError::EE_OK);
    EXPECT_EQ(collection->FCount(), 4);
    EXPECT_EQ(collection->FActiveCount(), 0);

    SAFE_DELETE(collection);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
