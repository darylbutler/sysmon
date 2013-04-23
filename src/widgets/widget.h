#ifndef WIDGET_H
#define WIDGET_H

// Struct for geometry
struct Size
{
    // It is important to remember:
    // for any dimension, 0 signals that it wants to be resized (autosize mode)
    // -1 indicates it does not want to be drawn
    double x, y, width, height;

    // default constructors
    Size() { x = 0; y = 0; width = 0; height = 0; }
    Size(double iX, double iY) { x = iX; y = iY; width = 0; height = 0; }
    Size(double iX, double iY, double iW, double iH) { x = iX; y = iY; width = iW; height = iH; }
};

// Struct for margin / padding box model
struct Box
{
    double left, right, top, bottom;

    // default constructors
    Box() { left = right = top = bottom = 0; }
    Box(double i) { left = right = top = bottom = i; }
    Box(double iL, double iR, double iT, double iB) { left = iL; right = iR; top = iT; bottom = iB; }

    // Utility
    double total_horz() { return left + right; }
    double total_vert() { return top + bottom; }
};

/*
 * Represents the base class for all widgets we draw
 *
 * There are planned two type of widgets: Layout widgets, that can hold children, and
 * Visual[ization] widgets, which show data (No children).  This is the base class for
 * both of those widgets and serves to expose the Draw, Resize, and BeforeResize methods
 * because all widgets must have these functions.
 */
class Widget
{
protected:
    // -- Private Members
    // Geometry
    unique_ptr<Size> requested_size, size;              // Requested is read by this widget's parent (layout), and it sets the Size
    unique_ptr<Box>  margin, padding;                   // Every widget has a margin

    // Options
    unique_ptr<Color> background_color, border_color;   // Even layouts have a background that can be drawn
    bool draw_bg, draw_border;                // Do we draw the border or background?
    double border_width;                      // Border line width.  Comment for my OCD.

    // -- Private Methods
    // Base Constructor
    void setup_base();
    // Draws background and border
    virtual void draw_bg_and_border(Cairo::RefPtr<Cairo::Context> cr);
    // Returns a size of the space available for content.  Basically size
    // minus all the margins and padding and border_widths
    Size get_avail_rect();
    // This function parses a ParameterList and sets any parameters that pertain
    // to it.  These functions are ment to be called in a cascade, so the base
    // (This function) will handle all the options that it implements, while
    // descendant widgets will implement the parameters it introduces.
    // One thing to note here is that, in these functions, always 'mark'
    // the parameters that you understand.
    // TODO void set_parameters_base(ParamList params);
public:
    // -- Constructor & destructor
    Widget();
    // TODO Widget(ParamList params);
    ~Widget();
    // -- Accessors
    // get
    inline Size*    get_requested_size()    { return requested_size.get(); }
    inline Size*    get_size()              { return size.get(); }
    inline Box*     get_margin()            { return margin.get(); }
    inline Box*     get_padding()           { return padding.get(); }
    inline Color*   get_background_color()  { return background_color.get(); }
    inline Color*   get_border_color()      { return border_color.get(); }
    inline bool     get_draw_bg()           { return draw_bg; }
    inline bool     get_draw_border()       { return draw_border; }
    inline double   get_border_width()      { return border_width; }
    // set
    inline void set_requested_size(Size *s)     { requested_size.reset(s); }
    inline void set_size(Size *s)               { size.reset(s); }
    inline void set_margin(Box *b)              { margin.reset(b); }
    inline void set_padding(Box *b)             { padding.reset(b); }
    inline void set_background_color(Color *c)  { background_color.reset(c); }
    inline void set_border_color(Color *c)      { border_color.reset(c); }
    inline void set_draw_bg(bool b)             { draw_bg = b; }
    inline void set_draw_border(bool b)         { draw_border = b; }
    inline void set_border_width(double d)      { border_width = d; }
    // -- The Magic draw function!
    // Called when each widgets needs to redraw themselves.  Parents call their childrens' Draw.
    virtual void Draw(Cairo::RefPtr<Cairo::Context> cr);
};

#endif
