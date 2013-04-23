#ifndef LAYOUT_WIDGET_H
#define LAYOUT_WIDGET_H

using namespace std;

class LayoutWidget : public Widget
{
protected:
    // -- Members
    // The Widgets we layout
    std::vector<unique_ptr<Widget>> children;   // Pointers to the widgets we manage.
    // Only layouts have padding
    unique_ptr<Box> padding;
    // spacing is the padding between children
    double spacing;

    // -- Methods
    // Assigns positions and sizes to children
    virtual void layout_children();
public:
    // -- Constructor & Destructor
    LayoutWidget();
    ~LayoutWidget();
    // -- Accessors
    // get
    inline Box* get_padding()        { return padding.get(); }
    inline double get_spacing()     { return spacing; }
    // set
    inline void set_padding(Box *b)     { padding.reset(b); }
    inline void set_spacing(double d)   { spacing = d; }
    // Child care
    virtual void add_child(Widget *wdgt);    // Hey, look! A new widget to manage!
    virtual void remove_child(Widget *wdgt);

    // Override Widget's Draw
    void Draw(Cairo::RefPtr<Cairo::Context> cr);
};

#endif
