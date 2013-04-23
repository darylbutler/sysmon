    /*
     * This is a helper class that manages a rolling history of double values.
     * It was designed with a CpuGraph in mind.
     *
     * When you create this table, you tell it how many values it should ever
     * contain.  It could contain less, but never more.
     * When you call Add(), it first checks the length of the internal array.
     * If it is at its maximum length, it prunes the very first element (The
     * olded value added) and pushes the new value on to the opposite end.
     *
     * The array is intended to be access sequentially and able to be extended
     * to support storage of multiple values at a single point in time (one x,
     * multiple y's).  I'm not sure how I will achieve this (A single array with
     * each element a separate array) or seperate arrays for each item to be
     * stored.  Either way, it is intended to be iterated over as such:
     *
     * - table->StartIter();  // This sets the local iterator to the first value
     * - table->NextValue();  // returns the value at the current position and
     *                           moves to the next.
     * - table->InspectValue();   // returns the current value but does not
     *                               increment the current index in the array.
     * - Table->Step();       // Manually iterates the index by 1
     * - Table->AtEnd();      // Returns true when iterated to last element
     *
     * The reason we do this is that the table also supports the moving average.
     * When it is set (default is 2), while iterating (So, the index has a
     * value), table->CalculateMovingAvg(); returns the average of the last
     * 2 (Or whatever the moving avg resolution is set to) values.
     *
     * Other calculations can be implemented in a similiar fashion
     *
     * Also, the Table was designed with the ability to help a graph set a
     * dynamic scale.  The table tracks the lowest and highest values inserted
     * into it, so
     * - table->GetUpperBound()
     *   and
     * - table->GetLowerBound()
     * return the highest and lowest values in the table, respectively.
     *
     */

#include <vector>
#include "value_history_table.h"
// ----------------------------------------------------------------------------
// -- Constructors
// ----------------------------------------------------------------------------
void ValueHistoryTable::setup(int length, int movAvgRes)
{
    // Setup array
    m_values = new vector<double>(length);
    // Assign values and defaults
    m_uBound = 0;   // We do not have to worry about a default value.  When add
    m_lBound = 0;   // is called, if the array is empty, then it updates these
    m_index  = -1;  // -1 = we are not setup to iterate
    m_movAvgRes = movAvgRes > 0 ? movAvgRes : 2; // Cannot be negative, default is 2
    m_maxValuesCount = length > 0 ? length : 1; // Is this a sane default?
}
ValueHistoryTable::~ValueHistoryTable()
{
    // Free the std::vector we created
    delete m_values;
    m_values = 0;
}


// ----------------------------------------------------------------------------
// -- Private Methods ---------------------------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -- Function    : private add(val)
// --
// -- Takes       : val = the value to add to the array
// --
// -- Purpose     : Adds a value to the array, making sure the array never
//                  becomes larger than m_maxValueCount
void ValueHistoryTable::add(double val)
{
    // Make sure the array size is 1 less than the max count
    if (int(m_values->size()) >= m_maxValuesCount)
    {
        // We need to prune the array by removing the oldest value
        remove_oldest();
    }

    // Add the value to the end of the array
    m_values->push_back(val);

    // Update the bounds
    update_bounds(val);
}

// ----------------------------------------------------------------------------
// -- Function    : private update_bounds(val)
// --
// -- Takes       : val = the value added to the array
// --
// -- Purpose     : Checks value against our upper and lower bounds.  If it is
//                  less or greater than, then we need to update them
void ValueHistoryTable::update_bounds(double val)
{
    // Special case.  If there is only one item in the array, then this is the
    // that item, probably the first to be added, so it is both bounds
    if (int(m_values->size()) == 1)
    {
        m_uBound = val;
        m_lBound = val;
    }

    // Check the Upper Bound
    if (m_uBound < val)
        m_uBound = val;

    // Check the Lower Bound
    if (val < m_lBound)
        m_lBound = val;
}

// ----------------------------------------------------------------------------
// -- Function    : private reset_iteration()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : This prepares the class to be iterated.
void ValueHistoryTable::reset_iteration()
{
    m_index = 0;
}

// ----------------------------------------------------------------------------
// -- Function    : private at_end()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Returns true is index is one past the last element in
//                  the array.  It should return true is the array is now
//                  un-iteratorable.
bool ValueHistoryTable::at_end()
{
    return m_index == int(m_values->size());
}

// ----------------------------------------------------------------------------
// -- Function    : private increment(c)
// --
// -- Takes       : c = the amount to increment (default is 1)
// --
// -- Purpose     : Increments the internal index by c for iteration.  Should
//                  set the index to one past the end of the array if c is
//                  outside the bounds of the array
void ValueHistoryTable::increment(int c)
{
    if ((m_index + c) >= int(m_values->size()))
        m_index = int(m_values->size()); // 1 past the end
    else
        m_index += c;
}

// ----------------------------------------------------------------------------
// -- Function    : get_value()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : returns the value at the current index of the array
//                  increment can push the index past the end of the array,
//                  so check if it is past the end and, if so, return the last
//                  element.
double ValueHistoryTable::get_value()
{
    if (m_index >= int(m_values->size()))
        return *(m_values->end() - 1);

    return m_values->at(m_index);
}

// ----------------------------------------------------------------------------
// -- Function    : remove()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Removes the value from the array at the current index position
void ValueHistoryTable::remove()
{
    m_values->erase(m_values->begin() + m_index);
}

// ----------------------------------------------------------------------------
// -- Function    : remove_oldest()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Removes the oldest value from the list.  In the case of the
//                  currently implemented vector, this is the first element
void ValueHistoryTable::remove_oldest()
{
    m_values->erase(m_values->begin());
}

// ----------------------------------------------------------------------------
// -- Function    : calc_moving_avg()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Uses m_movAvgRes to calculate the moving avg from the
//                  current position in the array
double ValueHistoryTable::calc_moving_avg()
{
    // The resolution is the count of elements to avg, but we're already at the
    // first.  So below, res will equal the number of times we will have to
    // read back in the array to get our measurement.
    int res = m_movAvgRes - 1;

    // Check to see if we have values as far back as the resolution
    // if not, we need to return 0 (There is no moving avg at this pos with
    // this resolution)
    if (m_index - res < 0)
        return 0;

    // Sum each value, incrementing offset until it has reached the number of
    // total values we want avg (The resolution)
    double sum = get_value();

    for (int offset = 1; offset <= res; offset++)
        sum += m_values->at(m_index - offset);

    // Now we avg the set by dividing by the count, which is the instance
    // variable m_movAvgRes
    double avg = sum / double(m_movAvgRes);

    return avg;
}

// ----------------------------------------------------------------------------
// -- PUBLIC METHODS ----------------------------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -- Function    : Add(val)
// --
// -- Takes       : val = a value to add to the array
// --
// -- Purpose     : Adds the value to the array while keeping it from growing
//                  past the supplied array length
void ValueHistoryTable::Add(double val)
{
    add(val);
}


// ----------------------------------------------------------------------------
// -- Function    : StartIter()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Sets up the instance for iteration
void ValueHistoryTable::StartIter()
{
    reset_iteration();
}

// ----------------------------------------------------------------------------
// -- Function    : NextValue()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : returns the value at the CURRENT m_index, increments the
//                  index, then returns the first value.  It is important that
//                  this order is kept because of how at_end() check to see
//                  if the index is past the last element.
//
//                  I guess it equals that this should be used in a while()
//                  loop and not a do while() loop.
double ValueHistoryTable::NextValue()
{
    // grab the value
    double val = get_value();
    // step the index forward
    increment();
    // return the value
    return val;
}

// ----------------------------------------------------------------------------
// -- Function    : InspectValue()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Returns the current value.  Does nothing to the position
//                  of iteration.
double ValueHistoryTable::InspectValue()
{
    return get_value();
}

// ----------------------------------------------------------------------------
// -- Function    : Step()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Steps the array forward, ignores value.  Will not step past
//                  the end of the array
void ValueHistoryTable::Step()
{
    increment();
}

// ----------------------------------------------------------------------------
// -- Function    : AtEnd()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Returns true if the index is now past the last element
bool ValueHistoryTable::AtEnd()
{
    return at_end();
}

// ----------------------------------------------------------------------------
// -- Function    : CalculateMovingAvg()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Returns the moving average for the instance's supplied
//                  resolution.
double ValueHistoryTable::CalculateMovingAvg()
{
    return calc_moving_avg();
}



