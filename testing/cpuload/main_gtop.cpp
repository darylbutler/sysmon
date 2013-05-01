//
// This tests the speed and ease of using gtop.
//
// 1: 21.56     2: 21.16    3: 21.20
// Avg Time: 21.31
//
#include <iostream>
#include <vector>
#include <string>

#include <glib-2.0/glib.h>
#include <glibtop.h>
#include <glibtop/cpu.h>


extern "C"{
void glibtop_get_cpu(glibtop_cpu*);
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
    glibtop_cpu cpuinfo;
    glibtop_get_cpu(&cpuinfo);

    // Emulate a return vector for comparison
    vector<double> core_totals;

    core_totals.push_back(cpuinfo.total);

    for (int x = 0; x < 3; x++)
        core_totals.push_back(cpuinfo.xcpu_total[x]);

    //for (auto iter : core_totals)
        //cout << "Read: " << iter << endl;
}

