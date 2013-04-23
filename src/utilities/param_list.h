#ifndef PARAM_LIST_H
#define PARAM_LIST_H

using namespace std;

// We will have a vector of these
struct Param
{
    string name;    // Param Name, something the widget should understand
    string value;   // The value of said param.  No type guarantees.
    bool marked;    // If true, this Param should be skiped over on the iteration

    Param(string n, string v)
        { this->name = n; this->value = v; this->marked = false; }
};

// The actual collection class
class ParamList
{
private:
    // -- Private Members
    vector<Param*>::iterator iter;  // Our internal iterator
    vector<Param*> *m_values;       // Collection of Params
    bool m_reset;         // When this is true, Next() will not increment the iter

    // -- Private Methods
    void add(string name, string value);    // We manage the memory of the vector
    void reset_iteration();     // Readies iteration
    bool at_end();              // return true if index is past last param
    void next();                // Moves index to the next, nonmarked, param
    string get_name();          // Used to get the current Param.
    string get_value();         // Note that neither of these move the iterator
    void mark();                // Marks the current iterated param

public:
    // -- Constructor & Destructor
    ParamList();
    ~ParamList();   // This class will delete all Params in m_values!

    // Public Methods
    void    Add(string n, string v); // Adds a param to the array
    inline int Count() { return int(m_values->size()); }
    void    StartIter();    // Sets us up to start iteration
    string  GetName();      // Gets the current param's name
    string  GetValue();     // Gets the current param's value
    void    Mark();         // Marks the current param
    bool    Next();         // Move iter to the next nonmarked param
    bool    AtEnd();        // Returns true when iteration is done
};

#endif
