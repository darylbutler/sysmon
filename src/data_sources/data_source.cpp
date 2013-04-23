/* DataSource - Base Class for all DataSources
 *  "I am your king!" - "Well, I didn't vote for you."
 *
 * This class is the base class for all of the data sources.  It simply
 * provides for the connection between a DataWidget type and a DataSource
 * and a connection between a DataSource and its DataManager (Class name
 * made up on spot.  Not final).
 *
 * The most important thing for a datasource is that it should provide
 * its value always, regardless if a thread is updating it.  My thinking
 * is that implementation may change, so I cannot assume this call will
 * always precede a gui update (I am afraid performance may be poor with
 * data collecting and I may need to thread the data sources, but we'll see)
 *
 * DataWidget -> DataSource
 *  - GetValue(a) && GetValues(a) returns a string and a string array,
 *  respectively.  The thinking here is that almost all data types can be
 *  stored in a string and retain its meaning (ie, 4 = "4", cool.
 *  "Hello!" = Not a number).
 *  - GetValueAsNumber(a) && GetValuesAsNumbers(a) should be implemented if
 *  possible since most data we will aggregate will be strings and doubles.
 *  If the data this source pulls is a string, then return -1 for these.
 *  NOTE: Both of these take a string as an optional argument.  It should
 *  be understood as the widget asking for a specific piece of information.
 *  For example, a single DataSource should exists for cpu data (Since it
 *  is all contained in a single file).  The widget might call
 *  GetValueAsNumber("cpu1") and you may return 0.23.  It is optional,
 *  so in this case, GetValueAsNumber() could default to the aggregate cpu0
 *  load %.
 *
 *  DataCollection -> DataSource
 *   - DoWork() means your update interval has ticked and you should update
 *   your internal value(s).  Remember the above connection to DataWidget
 *   and know that it may call during your update if the implementation
 *   changes.
 *
 *   As will all of my base widgets, pure virtual widgets are wastful in
 *   that testing them is impossible.  So, this widget will return a
 *   value when it is called (A hard coded value, it's simply for testing).
 *   NOTE: It will return both a double and a string depending on whether
 *   GetValue() or GetValeAsNumber() is called.  Your implementation
 *   probably will not have two separate values for these functions, that
 *   would be confusing.  It is my thought that GetValue() and
 *   GetValueAsNumber() should return the same DATA, just in different
 *   forms.  To me that makes more sense than trying to use both for
 *   different value.
 *
 *   It should be noted too that, in some instances, a DataWidget
 *   implementation will be very closely tied to its DataSource.  It may
 *   be a better idea to ignore the GetValue() functions above and
 *   implement a special call to a getvalue() returning, maybe, an address
 *   to a struct for example.  This seems to me to be sub-optimal, since
 *   I'm planning to construct all of this from XML, though this could be
 *   simpler because it should be a very specific case.
 */

#include <string>
#include <vector>
#include "data_source.h"

using namespace std;

// Constructor
DataSource::DataSource() {

}
DataSource::~DataSource() {

}


// -----------------------------------------------------------------
// Data Connections between DataSource and DataWidget
string DataSource::GetValue(string value) {
    // This is perfect for testing!
    if (value == "")
        return "Testing Value";
    else
        return value + "'s value";
}
string* DataSource::GetValues() {
    string *str = new string[3];

    str[0] = "Value 1";
    str[1] = "Value 2";
    str[2] = "Value 3";
    return str;
}
double DataSource::GetValueAsNumber(string value) {
    if (value.empty())
        return 2.9;
    return 9.2;
}
double* DataSource::GetValuesAsNumbers()
{
    double *arr = new double[2];

    arr[0] = 5;
    arr[1] = 4;


    return arr;
}

// ----------------------------------------------------------------------------
// Data connection between DataCollection and DataSource
// ----------------------------------------------------------------------------
void DataSource::DoWork() {
    // He he he I am working!
}
