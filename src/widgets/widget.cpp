/*
 * Widget.cpp
 *
 * This is the base widget of sysmon.
 * It doesn't layout widgets or display any information,
 * it just draws it's background and border.
 *
 * All widgets should inherit this class and the draw functions will be
 * passed on.  Just my starting point.
 *
 */
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <memory>
#include "../utilities/color.cpp"
#include "widget.h"

// -- Constructor --
// Default -- Just set everything to some nice defaults
void Widget::setup_base()
{
    requested_size = unique_ptr<Size>(nullptr); // Null the pointer
    size           = unique_ptr<Size>(new Size());
    margin         = unique_ptr<Box>(new Box());
    padding        = unique_ptr<Box>(new Box());

    // Default Colors
    background_color = unique_ptr<Color>(new Color(0, 0, 0));  // Black background
    border_color     = unique_ptr<Color>(new Color());             // White Border

    // Draw borders and background by default
    draw_bg     = true;
    draw_border = true;
    border_width = 1;
}
Widget::Widget()
{
    setup_base();
}
// Destructor
Widget::~Widget()
{
}

// ----------------------------------------------------------------------------
// -- Function    : private get_avail_rect()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : Returns a size of the room left over for content.  It is the
//                  size minus all the margin / padding / borders.
//                  This gives us the space that draw_bg_and_borders didn't use!
//
Size Widget::get_avail_rect()
{
    Size s;

    s.x = size->x + margin->left + border_width + padding->left;
    s.y = size->y + margin->top +  border_width + padding->top;
    s.width  = size->width  - (margin->total_horz() + (border_width * 2) + padding->total_horz());
    s.height = size->height - (margin->total_vert() + (border_width * 2) + padding->total_vert());

    return s;
}


// This function draws the background and border on the provided cairo context
// Note, This particular function does not use the padding member because
// the border goes between the margin and the padding.  In descendant widgets,
// honor padding.
void Widget::draw_bg_and_border(Cairo::RefPtr<Cairo::Context> cr)
{
    // Start by drawing background
    //  We do not include the margin
    background_color->set_source(cr);
    cr->set_line_width(border_width);
    cr->rectangle(
            size->x + margin->left,
            size->y + margin->top,
            size->width - (margin->left + margin->right),
            size->height - (margin->top + margin->bottom)
        );

    if (draw_bg)
        cr->fill_preserve();
    if (draw_border)
    {
        border_color->set_source(cr);
        cr->stroke_preserve();
    }
    // Any other options

    // Clear the path when done
    cr->begin_new_path();
}

// ---- Public ----
// Draw: The methods tells the widget to draw itself onto the provided cairo context.
//       Remember that child widgets are apart of your widget, so you should call
//       their draw methods here, or they'll never get called.
// this is my simple example, so it only calls our private draw function (Which is virtual,
// so you can share my brilliance).
void Widget::Draw(Cairo::RefPtr<Cairo::Context> cr)
{
    // Easy!
    draw_bg_and_border(cr);

    // Call any children!
    // MyChildNode->Draw(cr);
}
