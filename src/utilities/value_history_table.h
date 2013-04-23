#ifndef VALUE_HISTORY_TABLE_H
#define VALUE_HISTORY_TABLE_H

using namespace std;

class ValueHistoryTable
{
private:
    // Private Members
    double m_uBound, m_lBound;// Lowest and Highest values inserted
    int m_index;                // Current position for iteration
    int m_movAvgRes;            // Resolution of the moving average calculation
    int m_maxValuesCount;       // Number of values to maintain (Never grow past)
    vector<double> *m_values;   // Our internal table of values

    // Private Methods
    void setup(int length, int movAvgRes);  // local constructor
    void add(double val);       // Inserts a value into the array
    void update_bounds(double); // Updates upper and lower bounds
    void reset_iteration();     // Gets the class ready to begin an interation
    bool at_end();              // returns true is index is outside the bounds of array
    void increment(int c = 1);  // Increments the index by c
    double get_value();         // returns the value at the current index
    void remove();              // removes the element at the current position
    void remove_oldest();       // removes the oldest element from the array
    double calc_moving_avg();   // Calculates moving average from the current index

public:
    // Constructor / Destructor
    ValueHistoryTable(int length) { setup(length, -1); }    // -1 will be changed to default in setup
    ValueHistoryTable(int length, int movAvgRes) { setup(length, movAvgRes); }
    ~ValueHistoryTable();

    // Public Interfaces
    // -- Add Values
    void    Add(double val);    // Adds val to the array

    // -- Iteration
    void    StartIter();    // Gets us ready to iterate
    double  NextValue();    // Gets the current value and then increments the iter
    double  InspectValue(); // Returns the current value, does not increment
    void    Step();         // Increments index by 1
    bool    AtEnd();        // True is iteration is now done

    // -- Calculation during iteration
    double  CalculateMovingAvg();   // Returns the moving avg at index

    // -- Table Info
    // Returns the largest value inserted
    inline  double  GetUpperBound() { return m_uBound; }
    // Returns the smallest value inserted
    inline  double  GetLowerBound() { return m_lBound; }
    // Returns an element at the index.  Beware this is not the intended usage of this class
    inline  double  At(int i)   { return m_values->at(i); }
    // Returns the number of elements currently stored
    inline  int     Count()     { return int(m_values->size()); }
};

#endif
