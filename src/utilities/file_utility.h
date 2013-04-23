#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

using namespace std;

struct FileUtility
{
    // Splits a string based on provided split char.  Returns a vector.
    vector<string> SplitString(string str, char sep);

    // Parses the internal file into a vector, lines split by spaces
    // If key is provided, only lines that begin with the key are read
    vector<string> *GetFile(string path, string key = "");

    // Sums an array of string
    double SumArray(vector<string>* array, int start = -1, int end = -1);
};

#endif
