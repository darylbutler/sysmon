/**
 * This file handles the reading and parsing of string and files into vectors
 *
 * Pretty simple.
 */

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "file_utility.h"

using namespace std;

// Splits a string around sep
vector<string> FileUtility::SplitString(string str, char sep)
{
    // This is the vector we will return
    vector<string> split;
    split.clear();

    // Special case -- Empty input string
    if (str == "")
        return split;

    // Iterate through the string array a character at a time
    // If the char is not the sep char, add it to the stringstream
    // If the char is the sep char, move the stringstream to the array and
    //      clear it, so we can start another string.
    stringstream curr_string;       // Builds the current string
    string::iterator curr_char;     // Iterator for loop
    for (curr_char = str.begin(); curr_char != str.end(); ++curr_char)
    {
        if (*curr_char == sep)
        {
            // Ensure curr_string isn't empty
            if (!curr_string.str().empty())
                split.push_back(curr_string.str());

            // Gotta be a better way...
            curr_string.str("");
        }
        else
            curr_string << *curr_char;
    }

    // Add the contents of the curr_string to the vector
    if (!curr_string.str().empty())
        split.push_back(curr_string.str());

    // return the completed array
    return split;
}

// ----------------------------------------------------------------------------
// -- Function    : GetFile(string, string)
// --
// -- Takes       : string path = location of file to read
//                  string key (optional) = If this string is present, then we
//                      will only read lines that begin with $key.
// --
// -- Purpose    : This function is intended to read /proc/ files, which normally
//  have a lot of information seperated by spaces.  For example, /proc/stats
//  holds all of the processor jitters spent on various cpu task types.  This
//  function reads this file and returns their contents in a vector
vector<string> *FileUtility::GetFile(string path, string key)
{
    vector<string>  *lines = new vector<string>();
    string          line;

    if (path == "") return lines;

    ifstream file (path.c_str());

    if (file.is_open())
    {
        while (file.good())
        {
            // Read in the current line
            getline(file, line);

            // If the key is set, we only care if this line starts with it
            if ((key == "") ||    // If we don't care what the line starts with...
                (key != "" && line.compare(0, key.size(), key) == 0)) // line should start with $key
            {
                // Avoid empty lines
                if (line != "")
                    lines->push_back(line);
            }
        }
    }
    else
    {
        // File does not exists
        cerr << "In FileUtility::GetFile(), Could not open file:" << endl;
        cerr << '\t' << path << endl << "Skipping..." << endl;
    }

    // Close the file
    file.close();

    // Return the file
    return lines;
}

// ----------------------------------------------------------------------------
// -- Function    : SumArray
// --
// -- Takes       : array = point to a vector of strings
//                  start = (optional) first index of vector to begin addition
//                  end = (optional) last index (inclusive) to end addition
// --
// -- Purpose     : We're rading files like /proc/stat, so we need to be able
//                  to sum a sequence of string ints.
double FileUtility::SumArray(vector<string> *array, int start, int end)
{
    // Make sure we have a pointer to somewhere
    if (array == 0) // null pointer
    {
        cerr << "In FileUtility::SumArray, null pointer recieved instead of array" << endl;
        return -1;
    }

    // Bounds control
    if (start < 0)
        start = 0;
    if (end >= (int) array->size() || end < 0)
        end = (int) array->size() - 1;

    // Return value
    double ret = 0;

    // Loop through the array, summing the values
    for (int loopX = start ; loopX <= end; loopX++)
    {
        ret += atoi(array->at(loopX).c_str());
    }

    // return the value
    return ret;
}



