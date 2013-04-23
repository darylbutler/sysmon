/*
 * This class implements a key - value list of string values.
 *
 * It is intended to facilitate the transfer from xml parameters to widget
 * setups.  When the user creates a widget in xml, he will quickly set whatever
 * parameters he wants, allowing all other to fall back on defaults.  However,
 * the xml parser and layout creation module will have no knowledge of what
 * options / parameters a widget listens to, so we send it to them in this
 * list.
 *
 * If you look at the widget classes, you can see there is functionality built
 * into each level in the widget inheritance chain / tree.  The problem here
 * is that, since each level implements separate things, it would be
 * absolutely cumbersome for every derived class to set his options AND the
 * options of all his parents.
 *
 * Therefore, this class facilitates the 'marking' of a parameter after it
 * has been parsed.  It is intended to be used as such:
 * -) A widget is created and is passed this ParamList.
 * -) That widget, since it does know who its parents are at design time,
 *          passes this ParamList to each parent's method that parses this
 *          list.
 * -) That parent iterates through the list, and if the iter matches a string
 *          of an option he implements, he parses the value and then 'marks'
 *          that option.  When the option has been marked, it is skipped over
 *          during future iterations (So, in essence, the list continually gets
 *          smaller).
 * -) Once all possible paramlist parsing methods have been called, the list
 *          should be iterated once more, this time printing to cerr the
 *          param name and value and saying it does not support that option.
 *
 * It should be noted that performance shouldn't matter as much in this design
 * because this is a single step in the startup of the program.  While we want
 * the program to start as quickly as possible, I think it is worth the speed
 * cost for the code clarity since it is only incurred once.
 */

#include <vector>
#include <string>

#include "param_list.h"

using namespace std;

// ----------------------------------------------------------------------------
// -- Constructor & Destructor
ParamList::ParamList()
{
    m_values = new vector<Param*>();
    m_reset = false;
}
ParamList::~ParamList()
{
    for (iter = m_values->begin(); iter != m_values->end(); iter++)
        delete *iter;

    delete m_values;
}

// ----------------------------------------------------------------------------
// -- Private Functions
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -- Function    : Add(name, value)
// --
// -- Takes       : Name and Value are the values of the new param to add
// --
// -- Purpose     : Adds a new param to the internal vector
void ParamList::add(string name, string value)
{
    m_values->push_back(new Param(name, value));
}

// ----------------------------------------------------------------------------
// -- Function  : reset_iteration()
// --
// -- Takes     : Nothing
// --
// -- Purpose   : Moves the internal iter to the front of our vector
void ParamList::reset_iteration()
{
    iter = m_values->begin();
    m_reset = true;
}

// ----------------------------------------------------------------------------
// -- Function  : at_end()
// --
// -- Takes     : Nothing
// --
// -- Purpose   : Returns true if the iter is past the end of the vector
bool ParamList::at_end()
{
    return iter == m_values->end();
}

// ----------------------------------------------------------------------------
// -- Function  : next()
// --
// -- Takes     : Nothing
// --
// -- Purpose   : Increments the iterator to the next unmarked param
void ParamList::next()
{
    // If reset is true, don't move the iter...
    if (m_reset)
        m_reset = false;
    else
        iter++;

    // Unless the first element is marked
    while (iter != m_values->end() && (*iter)->marked)
        iter++;
}

// ----------------------------------------------------------------------------
// -- Function  : get_name()
// --
// -- Takes     : Nothing
// --
// -- Purpose   : Returns the name of the param at the current positon
string ParamList::get_name()
{
    return (*iter)->name;
}

// ----------------------------------------------------------------------------
// -- Function  : get_value()
// --
// -- Takes     : Nothing
// --
// -- Purpose   : Returns the value of the param at the current position
string ParamList::get_value()
{
    return (*iter)->value;
}

// ----------------------------------------------------------------------------
// -- Function  : mark()
// --
// -- Takes     : Nothing
// --
// -- Purpose   : marks the current param so it will not be iterated over in the
//                future.
void ParamList::mark()
{
    (*iter)->marked = true;
}

// ----------------------------------------------------------------------------
// -- Public Functions
// ----------------------------------------------------------------------------

// These functions just reveal our internal methods.  No comments, you can
// handle it.
void ParamList::Add(string n, string v)
{
    add(n, v);
}
void ParamList::StartIter()
{
    reset_iteration();
}
string ParamList::GetName()
{
    return get_name();
}
string ParamList::GetValue()
{
    return get_value();
}
void ParamList::Mark()
{
    mark();
}
bool ParamList::Next()
{
    next();
    return !at_end(); // that is, return NOT at_end().  Returns true if we can
                      // access element
}
bool ParamList::AtEnd()
{
    return at_end();
}





