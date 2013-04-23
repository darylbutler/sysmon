//
// This tests the speed and ease of using gtop.
// This file is the base we will compare gtop to
// it reads /proc/loadavg and parses the three values into the three variables

#include <iostream>
#include <fstream>

#include <glib-2.0/glib.h>
#include <glibtop.h>
#include <glibtop/loadavg.h>


extern "C"{
void glibtop_get_loadavg(glibtop_loadavg*);
}

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
    // Grab the structure and have gtop populate it
    glibtop_loadavg loadavg;
    glibtop_get_loadavg(&loadavg);

    string laOne = to_string(loadavg.loadavg[0]);
    string laFive = to_string(loadavg.loadavg[1]);
    string laFifteen = to_string(loadavg.loadavg[2]);

    //cout << "1: " << laOne << " 5: " << laFive << " 15: " << laFifteen << endl;
}

