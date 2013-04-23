// This was a sample file from google test sources.  I modified it to work for
// my project.

#include <limits.h>
#include <string>
#include <vector>
#include <iostream>
#include "../src/utilities/value_history_table.h"
#include "gtest/gtest.h"

// --- TEST STORAGE OF VALUES -------------------------------------------------
//
// NOTE THAT THESE TESTS ARE ITERATION INDEPENDANT!!


// Easy test.  Does it store the items in the order we added them?
TEST(ValueHistoryTable, SimpleStorageTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    // Check each element that it is in order
    for (double i = 0; i < 5; i++)
        EXPECT_EQ(i, tbl->At(int(i)));

    delete tbl;
    tbl = 0;
}

// Same as above, except that we want it to keep only 3 elements
TEST(ValueHistoryTable, PruningTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(3);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    // Table should only have 3 elements, other wise: epic fail.
    ASSERT_EQ(3, tbl->Count());

    // The first two values added (0 & 1) should not be present in array
    EXPECT_EQ(2, tbl->At(0));
    EXPECT_EQ(3, tbl->At(1));
    EXPECT_EQ(4, tbl->At(2));

    delete tbl;
    tbl = 0;
}

// --- TEST ITERATION ---------------------------------------------------------

// We tested above that the items added stayed in order, so they should also
// be in order when we iterate them, and we should be able to iterate all the
// way to the end.
TEST(ValueHistoryTable, IterationTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    tbl->StartIter();
    double loopX = 0.0;
    while (!tbl->AtEnd())
    {
        // Loop should never be able to grow past 5
        ASSERT_TRUE(loopX < 6);

        // LoopX should equal the value at this position
        EXPECT_EQ(loopX, tbl->NextValue());
        loopX++;
    }

    EXPECT_EQ(loopX, 5);

    delete tbl;
    tbl = 0;
}

// Testing the Step() and InspectValues() [Manual Iteration]
TEST(ValueHistoryTable, ManualIterationTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    tbl->StartIter();
    double loopX = 0.0;
    while (!tbl->AtEnd())
    {
        // Loop should never be able to grow past 5
        ASSERT_TRUE(loopX < 6);

        // LoopX should equal the value at this position
        EXPECT_EQ(loopX, tbl->InspectValue()); // Not iterating...
        tbl->Step();    // Iterating
        loopX++;
    }

    delete tbl;
    tbl = 0;
}

// Test the Step can never go past the last value
TEST(ValueHistoryTable, StepTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    tbl->StartIter();
    for (int loopX = 0; loopX < 20; loopX++)
        tbl->Step();

    // Should never past the last value, which is 4
    EXPECT_EQ(4.0, tbl->InspectValue());

    delete tbl;
    tbl = 0;
}

// --- TEST BOUNDS ------------------------------------------------------------

// Easy test, check to make sure it keeps track of the largest and smalled values
TEST(ValueHistoryTable, SimpleUpperBoundTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    EXPECT_EQ(4.0, tbl->GetUpperBound());

    delete tbl;
    tbl = 0;
}
TEST(ValueHistoryTable, SimpleLowerBoundTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(0);
    tbl->Add(1);
    tbl->Add(2);
    tbl->Add(3);
    tbl->Add(4);

    EXPECT_EQ(0.0, tbl->GetLowerBound());

    delete tbl;
    tbl = 0;
}

// Out of order bounds test
TEST(ValueHistoryTable, RealisticUpperBoundTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(10);
    tbl->Add(1);
    tbl->Add(222);
    tbl->Add(3);
    tbl->Add(4);

    EXPECT_EQ(222.0, tbl->GetUpperBound());

    delete tbl;
    tbl = 0;
}
TEST(ValueHistoryTable, RealisticLowerBoundTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(5);
    tbl->Add(10);
    tbl->Add(1);
    tbl->Add(222);
    tbl->Add(3);
    tbl->Add(-4);

    EXPECT_EQ(-4.0, tbl->GetLowerBound());

    delete tbl;
    tbl = 0;
}

// Moving Average Test
TEST(ValueHistoryTable, MovingAverageTest)
{
    // Setup
    ValueHistoryTable *tbl = new ValueHistoryTable(10, 2);
    for (double i = 0.0; i < 10; i++)
        tbl->Add(i);

    // We'll do this manually, without a loop, so I can think through this
    tbl->StartIter();

    // At index 0, we should no be able to calc a moving avg, so we should get
    // 0 back.
    EXPECT_EQ(0.0, tbl->CalculateMovingAvg());

    tbl->Step();    // 1
    // Avg should = 0 + 1 / 2 == 0.5
    EXPECT_EQ(0.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 2
    // Avg should = 1 + 2 / 2 == 1.5
    EXPECT_EQ(1.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 3
    // Avg = 2 + 3 / 2 == 2.5
    EXPECT_EQ(2.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 4
    // Avg = 3 + 4 / 2 == 3.5
    EXPECT_EQ(3.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 5
    // Avg = 4 + 5 / 2 == 4.5
    EXPECT_EQ(4.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 6
    // Avg = 5 + 6 / 2 == 5.5
    EXPECT_EQ(5.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 7
    // Avg = 6 + 7 / 2 == 6.5
    EXPECT_EQ(6.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 8
    // Avg = 7 + 8 / 2 == 7.5
    EXPECT_EQ(7.5, tbl->CalculateMovingAvg());

    tbl->Step();    // 9
    // AVG = 8 + 9 / 2 == 8.5
    EXPECT_EQ(8.5, tbl->CalculateMovingAvg());

    tbl->Step();    // End of array

    delete tbl;
    tbl = 0;
}


