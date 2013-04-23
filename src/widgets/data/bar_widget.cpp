/*
 * This is a basic bar widget (Much like a progress bar).
 *
 * The Most Important Parameters / Options:
 * MaxValue:
 *      This determines how the actual value is represented.
 *      The widget will only draw a value between 0 and 1, so the value will
 *      be changed to MaxValue / value
 *
 * TODO: Introduce gradient colors! Come up with a snazy name for the parameter!
 */

#include <iostream>
#include <memory>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <string>
#include "../../data_sources/data_source.h"
#include "../widget.h"
#include "bar_widget.h"

// ----------------------------------------------------------------------------
// -- Constructor / Destructor
// ----------------------------------------------------------------------------
BarWidget::BarWidget(DataSource *src) : Widget()
{
    // We must have a data source!  It is our bread and budda!
    source = unique_ptr<DataSource>(src); // We own this DataSource now.

    // Setup defaults
    bar_color           = unique_ptr<Color>(new Color(0.8, 0.8, 0.8));
    bar_bg_color        = unique_ptr<Color>(new Color(0.4, 0.4, 0.4));
    bar_border_color    = unique_ptr<Color>(new Color(1, 1, 1));
    bar_bg_border_color = unique_ptr<Color>(new Color(0.6, 0.2, 0.2));
    bar_border_width = 1.0;
    bar_bg_border_width = 1.0;

    draw_bar_bg         = true;
    draw_bar_bg_border  = true;
    draw_bar_border     = true;

    vertical = false;

    m_maxValue  = -1;   // -1 = assume value is already percent
    m_value     = 0;    // This is 0 by default until we update it

    m_data_id = "";       // empty string, we'll take the defaul value
}
BarWidget::~BarWidget()
{
}

// ----------------------------------------------------------------------------
// -- Function    : draw_bar(cr)
// --
// -- Takes       : cr = point to a cairo reference
// --
// -- Purpose     : Assumes value is already between 1 and 0!  Draws the bar
//                  on the provided cairo reference.
void BarWidget::draw_bar(Cairo::RefPtr<Cairo::Context> cr)
{
    // Get our bar coords
    Size size = get_avail_rect();
    Size* s = &size;

    // Draw the bg first
    cr->set_line_width(bar_bg_border_width);
    cr->rectangle(s->x, s->y, s->width, s->height);

    // -- bg border
    if (draw_bar_bg_border)
    {
        bar_bg_border_color->set_source(cr);
        cr->stroke_preserve();
    }
    // -- bg
    if (draw_bar_bg)
    {
        bar_bg_color->set_source(cr);
        cr->fill_preserve();
    }

    // Clear the path
    cr->begin_new_path();

    // -- Now we're drawing the value bar
    // Modify the size by our value / percent
    // If we're horz, modify the width.
    // If we're vert, modify the height.
    if (vertical)
        s->height = s->height * m_value;
    else
        s->width = s->width * m_value;

    // New path, draw!
    cr->set_line_width(bar_border_width);
    cr->rectangle(s->x, s->y, s->width, s->height);

    // -- bar border
    if (draw_bar_border)
    {
        bar_border_color->set_source(cr);
        cr->stroke_preserve();
    }

    // -- Draw the bar
    bar_color->set_source(cr);
    cr->fill();

    // clean up
    cr->begin_new_path();
    s = nullptr;
}

// ----------------------------------------------------------------------------
// -- Function    : update_value()
// --
// -- Takes       : Nothing
// --
// -- Purpose     : We are about to redraw ourselves, so query our data source
//                  for our update value and ensure it is between 1 and 0.
void BarWidget::update_value()
{
    // grab the value from the datasource.  We display a percent, which is a
    // number, so we call the right function.
    double val = source->GetValueAsNumber(m_data_id);

    if (m_maxValue == -1) // assume this number is good
    {
        m_value = val;
        return;
    }

    // Now, we divide the MaxValue by this value to obtain our %
    val = m_maxValue / val;

    // If, for some reason, it is larger than 1, just update to 1
    m_value = val > 1 ? 1 : val;
}

// ----------------------------------------------------------------------------
// -- Public Functions
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -- Function    : public Draw(cr)
// --
// -- Takes       : cr = a cairo context
// --
// -- Purpose     : This is called by our parent, and it signals that we need to
//                  update our value and redraw ourselves.
void BarWidget::Draw(Cairo::RefPtr<Cairo::Context> cr)
{
    // First, update our internal value
    update_value();
    // Then draw our bg and border (Parent method)
    draw_bg_and_border(cr);
    // Then draw our bar
    draw_bar(cr);
}
