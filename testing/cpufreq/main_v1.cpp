/*
 * Testing the fastest way to read a complex proc file.
 * Example is /proc/cpuinfo, which has a lot of data we don't care about, so
 * there is quite a bit of seeking.
 *
 * This implementation uses the std::readline and std::string compare functions
 *
 * First run: 46.1s
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    ifstream file("/proc/cpuinfo");
    vector<double> cores_freq;

    if (file.is_open())
    {
        string  line = "",
                key  = "cpu MHz",
                freq = "";
        while (file.good())
        {
            getline(file, line);

            if (line.compare(0, key.length(), key) == 0)
            {
                // Extract the substring we care about
                int pos = line.find(':');
                pos += 2;  // ignore the colon and the space after it
                double value = stod(line.substr(pos));
                cores_freq.push_back(value);
            }
        }
    }
    else
        cerr << "Error opening /proc/cpuinfo" << endl;

    file.close();

    //for (auto iter : cores_freq)
        //cout << "Read:  " << iter << endl;
}
