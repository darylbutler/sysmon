/*
 * Testing the fastest way to read a complex proc file.
 * Example is /proc/cpuinfo, which has a lot of data we don't care about, so
 * there is quite a bit of seeking.
 *
 * This implementation uses a fixed offset method.  It is not desirable because the
 * file may not be the same on all systems.
 *
 * First run:  40.64 s
 * Second run: 39.82 s
 * Third run:  39.97 s
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

// Prototype
void ReadFile();
const int core_count = 3;

int main()
{
    for (int x = 0 ; x < 1000000; x++)
        ReadFile();

    return 1;
}

void ReadFile()
{
    ifstream file("/proc/cpuinfo");
    vector<double> cores_freq;
    double* freq_ary = (double*) malloc(sizeof(double) * core_count);

    if (file.is_open())
    {
        int max = 800;
        int line_pos = 8;
        int cpu_lines = 18;
        string value = "";

        double* freqs = freq_ary;

        while (file.good() && !file.eof())
        {
            // get to the line
            for (int x = 0; x < line_pos; x++)
            {
                file.ignore(max, ':');
            }
            if (file.eof()) break;
            // ignore the space
            file.ignore(1);
            // Get the freq
            getline(file, value);
            // Add to the array
            *freqs = stod(value);
            freqs++;

            // Skip to next occurance
            for (int y = 0; y < cpu_lines; y++)
            {
                file.ignore(max, ':');
            }
        }
    }
    else
        cerr << "Error opening /proc/cpuinfo" << endl;

    file.close();

    for (int x = 0; x < core_count; x++)
        cores_freq.push_back( *(freq_ary + x) );

    //for (auto iter : cores_freq)
        //cout << "Read:  " << iter << endl;
}
