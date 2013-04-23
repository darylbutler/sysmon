 /*
  * This is the base class for the other layout widgets.
  * It introduces the common traits these widgets will have,
  * mainly having children.
  *
  * This widget works, but it only allows 1 child, and
  * it takes all of the available space.  It uses the box
  * model inherited from Widget, but still, this is a
  * useless widget, but a great starting point for others.
  */
#include <memory>
#include <vector>
#include "../widget.cpp"
#include "layout_widget.h"

// -----------
// Constructor
// -----------
LayoutWidget::LayoutWidget() : Widget()
{
    // Initialize child array
    children.clear();
    // Initialize our padding to cool defaults
    padding = unique_ptr<Box>(new Box(4));
    spacing = 4;
}
// ----------
// Destructor
// ----------
LayoutWidget::~LayoutWidget()
{
}

// ----------
// Add Widget
// ----------
void LayoutWidget::add_child(Widget *wdgt)
{
    // Add the child to the children array

    // Do not add null widgets
    if (!wdgt) return;

    children.push_back(unique_ptr<Widget>(wdgt));
}

// -------------
// Remove Widget
// -------------
void LayoutWidget::remove_child(Widget *wdgt)
{
    // Remove the child from the children array
    if (!wdgt) return;

    // TODO: stub
}

// --------------------
// Layout the children!
// this method is meant to be overridden in child classes
// this method must assign all children their positon and size
// before returning
//
// As this one is implemented, it displays only 1 child
// --------------------
void LayoutWidget::layout_children()
{
    if (children.size() <= 0)
        return;

    Widget *child = children.at(0).get();
    child->set_size(new Size(
                size->x + padding->left + margin->left,
                size->y + padding->top + margin->top,
                size->width - (padding->total_horz() + margin->total_horz()),
                size->height - (padding->total_vert() + margin->total_vert())
            ));
    child = nullptr;
}

// ----
// Draw
//
// Here we override the Widget's basic draw method.  This method should not have to be
// overridden further for any layout widgets.  This draw method will draw the layout
// widget, layout it's children, and then call each child's draw method.
// ----
void LayoutWidget::Draw(Cairo::RefPtr<Cairo::Context> cr)
{
    // First thing's first, layout the widgets
    layout_children();
    // Then, draw ourselves
    draw_bg_and_border(cr);
    // Then tell each of our children to Draw themselves
    for (int loopX = 0; loopX != (int) children.size(); loopX++)
        children[loopX]->Draw(cr);

    // Man, that was too easy.
}

