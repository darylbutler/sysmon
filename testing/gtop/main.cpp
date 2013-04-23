//
// This tests the speed and ease of using gtop.
// This file is the base we will compare gtop to
// it reads /proc/loadavg and parses the three values into the three variables

#include <iostream>
#include <fstream>

using namespace std;

// Prototype
void ReadFile();

int main()
{
    for (int x = 0 ; x < 1000000; x++)
        ReadFile();

    return 1;
}

void ReadFile()
{
    // Open the file
    ifstream file("/proc/loadavg");

    // We expect 3 load averaged (1min, 5min, 15min)
    string laOne, laFive, laFifteen;
    double dOne, dFive, dFifteen;
    bool read = false;

    if (file.is_open())
    {
        // Read into strings
        getline(file, laOne, ' ');
        getline(file, laFive, ' ');
        getline(file, laFifteen, ' ');

        // Convert them to doubles
        dOne        = stod(laOne);
        dFive       = stod(laFive);
        dFifteen    = stod(laFifteen);
        read = true;
    }
    else
    {
        cerr << "Error opening /proc/loadavg!" << endl;
    }

    file.close();
}

