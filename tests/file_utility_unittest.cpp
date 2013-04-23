// This was a sample file from google test sources.  I modified it to work for
// my project.

#include <limits.h>
#include <string>
#include <vector>
#include <iostream>
#include "../src/utilities/file_utility.h"
#include "gtest/gtest.h"

// --- TEST SPLITSTRING() -----------------------------------------------------

// Empty seperatorq
TEST(FileUtility_SplitString, SimpleStringTest)
{
    // Setup
    FileUtility file;
    vector<string> want;
    want.push_back("Hello,");
    want.push_back("World!");

    vector<string> ret = file.SplitString("Hello, World!", ' ');

    // Test
    EXPECT_TRUE(want == ret);

}

// Tests factorial of 0.
TEST(FileUtility_SplitString, EmptyStringTest) {
    // Setup
    FileUtility *file = new FileUtility();

    // Test with an empty string, the returned vector should be empty
    EXPECT_EQ(0, (int) file->SplitString("", ' ').size());

    // Cleanup
    delete file;
    file = 0;
}

// Test a long split
TEST(FileUtility_SplitString, ComplicatedSplitTest)
{
    // Setup
    FileUtility file;
    vector<string> want;
    want.push_back("Co mpl");
    want.push_back(" cat ed spl");
    want.push_back("t on ");
    want.push_back("'s !!!");

    vector<string> ret = file.SplitString("Co mpli cat ed split on i's !!!", 'i');

    EXPECT_TRUE(want == ret);
}

// Test Double Sep
TEST(FileUtility_SplitString, DoubleSeparatorTest)
{
    FileUtility file;

    vector<string> ret = file.SplitString("should  be  only  five  elements", ' ');

    EXPECT_EQ(5, (int) ret.size());
}

// --- TEST GETFILE() ---------------------------------------------------------

// NOTE: These tests use file_utility_get_file.test as their sample input.
// It should equal:
//
// line  1 2 3 4 5 6 7 8 9 10
// line1 1 2 3 4 5 6 7 8 9 10
// line2 10 12 13 14 15 16 17 18 19 20
// random lines from here on out
// 2134 2345 6898 23432342355465 342 4 56667 23
// 4567 89238723 89 0923485871234 9082309834 23040 2934

const string test_file_path = "/share/projects/sysmon/src/tests/file_utility_get_file.test";

// Empty path
TEST(FileUtility_GetFile, EmptyPathTest)
{
    // Setup
    FileUtility file;
    vector<string> *ret;
    ret = file.GetFile("");

    EXPECT_TRUE(0 == (int) ret->size());
}

// Read Test
TEST(FileUtility_GetFile, GeneralReadTest)
{
    FileUtility file;
    vector<string> want, *ret;

    // Setup
    want.push_back("line  1 2 3 4 5 6 7 8 9 10");
    want.push_back("line1 1 2 3 4 5 6 7 8 9 10");
    want.push_back("line2 10 12 13 14 15 16 17 18 19 20");
    want.push_back("random lines from here on out");
    want.push_back("2134 2345 6898 23432342355465 342 4 56667 23");
    want.push_back("4567 89238723 89 0923485871234 9082309834 23040 2934");

    ret = file.GetFile(test_file_path);

    EXPECT_TRUE(want == *ret);
}

// Test key
TEST(FileUtility_GetFile, ReadOnlyKeyTest)
{
    FileUtility file;
    vector<string> want, *ret;

    // Setup
    want.push_back("line  1 2 3 4 5 6 7 8 9 10");
    want.push_back("line1 1 2 3 4 5 6 7 8 9 10");
    want.push_back("line2 10 12 13 14 15 16 17 18 19 20");

    ret = file.GetFile(test_file_path, "line");

    EXPECT_TRUE(want == *ret);
}

// --- TEST SUM_ARRAY() -------------------------------------------------------
const string test_array[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

// Test Empty Array
TEST(FileUtility_SumArray, EmptyArrayTest)
{
    vector<string> *empty_vector = new vector<string>(20);
    FileUtility file;

    EXPECT_EQ(0, file.SumArray(empty_vector));
}

// Test Total Sum
TEST(FileUtility_SumArray, TotalSumTest)
{
    FileUtility file;
    vector<string> input(test_array, test_array + sizeof(test_array) / sizeof(string));

    EXPECT_EQ(55, file.SumArray(&input));
}

// Test subtotal of sum
TEST(FileUtility_SumArray, OffsetSumTest)
{
    FileUtility file;
    vector<string> input(test_array, test_array + sizeof(test_array) / sizeof(string));

    EXPECT_EQ(10, file.SumArray(&input, 0, 3));
}

// Test subtotal out-of-range index
TEST(FileUtility_SumArray, OffsetOutOfRangeSumTest)
{
    FileUtility file;
    vector<string> input(test_array, test_array + sizeof(test_array) / sizeof(string));

    EXPECT_EQ(15, file.SumArray(&input, -1, 4));
    EXPECT_EQ(19, file.SumArray(&input, 8, 200));
}

// Test Subtotal Subset
TEST(FileUtility_SumArray, SubSetTotalTest)
{
    FileUtility file;
    vector<string> input(test_array, test_array + sizeof(test_array) / sizeof(string));

    EXPECT_EQ(15, file.SumArray(&input, 3, 5));
}


