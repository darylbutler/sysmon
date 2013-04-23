// This was a sample file from google test sources.  I modified it to work for
// my project.

#include <limits.h>
#include <string>
#include <vector>
#include <iostream>
#include "../src/utilities/param_list.h"
#include "gtest/gtest.h"

// This is a really simple class.  Just a few tests.

TEST(ParamList, IterationTest)
{
    ParamList *l = new ParamList();

    l->Add("0Name", "0Value");
    l->Add("1Name", "1Value");
    l->Add("2Name", "2Value");
    l->Add("3Name", "3Value");
    l->Add("4Name", "4Value");
    l->Add("5Name", "5Value");
    l->Add("6Name", "6Value");
    l->Add("7Name", "7Value");
    l->Add("8Name", "8Value");
    l->Add("9Name", "9Value");

    int loopCount = 0;

    l->StartIter();
    while (l->Next())
    {
        ASSERT_TRUE(loopCount < 11);
        loopCount++;
    }

    EXPECT_EQ(loopCount, 10);

    delete l;
    l = 0;
}

TEST(ParamList, SizeTest)
{
    ParamList *l = new ParamList();

    l->Add("0Name", "0Value");
    l->Add("1Name", "1Value");
    l->Add("2Name", "2Value");
    l->Add("3Name", "3Value");
    l->Add("4Name", "4Value");
    l->Add("5Name", "5Value");
    l->Add("6Name", "6Value");
    l->Add("7Name", "7Value");
    l->Add("8Name", "8Value");
    l->Add("9Name", "9Value");

    EXPECT_EQ(10, l->Count());

    delete l;
    l = 0;
}


TEST(ParamList, StorageTest)
{
    ParamList *l = new ParamList();

    l->Add("0Name", "0Value");
    l->Add("1Name", "1Value");
    l->Add("2Name", "2Value");
    l->Add("3Name", "3Value");
    l->Add("4Name", "4Value");

    int loopCount = 0;

    l->StartIter();
    while (l->Next())
    {
        ASSERT_TRUE(loopCount < 6);

        // What we should expect the value to be
        string ex_n = "", ex_v = "";
        switch(loopCount)
        {
            case 0:
                ex_n = "0Name";
                ex_v = "0Value";
                break;
            case 1:
                ex_n = "1Name";
                ex_v = "1Value";
                break;
            case 2:
                ex_n = "2Name";
                ex_v = "2Value";
                break;
            case 3:
                ex_n = "3Name";
                ex_v = "3Value";
                break;
            case 4:
                ex_n = "4Name";
                ex_v = "4Value";
                break;
            default:
                ex_n = "OhShit";
                ex_v = "OhNoes";
        }

        EXPECT_EQ(ex_n, l->GetName());
        EXPECT_EQ(ex_v, l->GetValue());

        loopCount++;
    }
    EXPECT_EQ(loopCount, 5);

    delete l;
    l = 0;
}

TEST(ParamList, MarkTest)
{
    ParamList *l = new ParamList();

    l->Add("0Name", "0Value");
    l->Add("1Name", "1Value");
    l->Add("2Name", "2Value");
    l->Add("3Name", "3Value");
    l->Add("4Name", "4Value");

    int loopCount = 0;

    l->StartIter();

    l->Next();
    l->Mark();  // Mark position 0

    l->Next();
    l->Next();
    l->Mark();  // Mark position 2

    l->Next();
    l->Next();
    l->Mark();  // Mark position 4


    l->StartIter();
    while (l->Next())
    {
        ASSERT_TRUE(loopCount < 3);

        // What we should expect the value to be
        string ex_n = "", ex_v = "";
        switch(loopCount)
        {
            case 0:
                ex_n = "1Name";
                ex_v = "1Value";
                break;
            case 1:
                ex_n = "3Name";
                ex_v = "3Value";
                break;
            default:
                ex_n = "OhShit";
                ex_v = "OhNoes";
        }

        EXPECT_EQ(ex_n, l->GetName());
        EXPECT_EQ(ex_v, l->GetValue());

        loopCount++;
    }
    EXPECT_EQ(loopCount, 2);

    delete l;
    l = 0;
}

