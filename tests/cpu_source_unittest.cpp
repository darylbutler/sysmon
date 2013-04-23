// This was a sample file from google test sources.  I modified it to work for
// my project.

#include <limits.h>
#include <string>
#include <vector>
#include <iostream>
#include "../src/data_sources/cpu_source.h"
#include "gtest/gtest.h"

// --- TEST CPUSOURCE() -----------------------------------------------------

// NOTE this is a private class.  There is no easy way to test it.
// However, what we can do is modify the file it will read from.
// If we setup a sequence of files, we can manually calculate the load
// between each of the files and call the DoWork entry method and
// check it's GetValueAsNumber to check its accuracy.

// File 1:
// cpu  352090 11601 101603 4104439 18826 1 752 0 0 0   = 465294 / 4589312
// cpu0 122198 4393 32997 1369505 2247 0 132 0 0 0      = 159588 / 1531472
// cpu1 110123 4016 30302 1387142 1849 0 70 0 0 0       = 144441 / 1533502
//
// File 2:
// cpu  353590 11606 102083 4124298 18861 1 755 0 0 0   = 467279 / 4611194
// cpu0 122709 4394 33169 1376122 2248 0 132 0 0 0      = 160272 / 1538774
// cpu1 110579 4017 30440 1393858 1853 0 71 0 0 0       = 145036 / 1540818
//
// File 3:
// cpu  354772 11609 102430 4135745 18875 1 756 0 0 0   = 468811 / 4624188
// cpu0 123169 4395 33291 1379885 2249 0 133 0 0 0      = 160855 / 1543122
// cpu1 110917 4017 30540 1397784 1854 0 71 0 0 0       = 145474 / 1545183
//
// File 1 -> File 2:
// cpu  : 0.090713      =  9%
// cpu0 : 0.093672      =  9%
// cpu1 : 0.081328      =  8%
//
// File 2 -> File 3:
// cpu  : 0.117900      = 12%
// cpu0 : 0.134084      = 13%
// cpu1 : 0.100343      = 10%
//
// File 1 -> File 3:
// cpu  : 0.100842      = 10%
// cpu0 : 0.108755      = 11%
// cpu1 : 0.088434      = 9%
//
// Someone needs to check my math

const string proj_path = "/share/projects/sysmon/src/tests/dummy_input_files/";
const string file1 = proj_path + "cpu_source_1.test";
const string file2 = proj_path + "cpu_source_2.test";
const string file3 = proj_path + "cpu_source_3.test";

TEST(CpuSource_UnitTest, File1ToFile2)
{
    CpuSource *cpu = new CpuSource(file1);

    // Interval's up, check our false /proc/stat.  It should have no value yet.
    cpu->DoWork();

    // Change our file to represent a change in /proc/stat
    cpu->setFilePath(file2);

    // Interval's Up, check our false /proc/stat.
    cpu->DoWork();

    // Now, it should have values.  Check them, one by one.
    string cpu_agg  = cpu->GetValue("all");
    string cpu0     = cpu->GetValue("cpu0");
    string cpu1     = cpu->GetValue("cpu1");

    EXPECT_EQ("9.07%", cpu_agg);
    EXPECT_EQ("9.37%", cpu0);
    EXPECT_EQ("8.13%", cpu1);
}

TEST(CpuSource_UnitTest, File2ToFile3)
{
    CpuSource *cpu = new CpuSource(file2);

    // Interval's up, check our false /proc/stat.  It should have no value yet.
    cpu->DoWork();

    // Change our file to represent a change in /proc/stat
    cpu->setFilePath(file3);

    // Interval's Up, check our false /proc/stat.
    cpu->DoWork();

    // Now, it should have values.  Check them, one by one.
    string cpu_agg  = cpu->GetValue("all");
    string cpu0     = cpu->GetValue("cpu0");
    string cpu1     = cpu->GetValue("cpu1");

    EXPECT_EQ("11.79%", cpu_agg);
    EXPECT_EQ("13.41%", cpu0);
    EXPECT_EQ("10.03%", cpu1);
}

TEST(CpuSource_UnitTest, File1ToFile3)
{
    CpuSource *cpu = new CpuSource(file1);

    // Interval's up, check our false /proc/stat.  It should have no value yet.
    cpu->DoWork();

    // Change our file to represent a change in /proc/stat
    cpu->setFilePath(file3);

    // Interval's Up, check our false /proc/stat.
    cpu->DoWork();

    // Now, it should have values.  Check them, one by one.
    string cpu_agg  = cpu->GetValue("all");
    string cpu0     = cpu->GetValue("cpu0");
    string cpu1     = cpu->GetValue("cpu1");

    EXPECT_EQ("10.08%", cpu_agg);
    EXPECT_EQ("10.88%", cpu0);
    EXPECT_EQ("8.84%", cpu1);
}

