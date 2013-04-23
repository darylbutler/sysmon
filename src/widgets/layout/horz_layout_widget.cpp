/*
 *
 *
 */

#include "layout_widget.cpp"
#include "horz_layout_widget.h"

// ---------------
// Our Constructor
// ---------------
HorzLayoutWidget::HorzLayoutWidget() : LayoutWidget()
{
    // By default, listen to child sizes
    HonorChildSizes = true;
}

// --------------------
// Our Layout Functions
// --------------------
void HorzLayoutWidget::layout_children_horz_simple()
{
    // This function is called when HonorChildSizes is false.
    // It is much simpler to size widgets this way.

    // First, we find out how much room we have available
    double avail_width  = size->width - (margin->total_horz() + padding->total_horz() + (border_width * 2));
    double avail_height = size->height - (margin->total_vert() + padding->total_vert() + (border_width * 2));
    int child_count = children.size();

    // Subtract the spacing left between each child
    avail_width -= (child_count - 1) * spacing;

    // Assign the figured widths
    double chld_width = avail_width / child_count;
    for (int loopX = 0; loopX < child_count; loopX++)
    {
        children.at(loopX)->set_size(new Size(
                    size->x + margin->left + border_width + padding->left + (loopX * (chld_width + spacing)),
                    size->y + margin->top + border_width + padding->top,
                    chld_width,
                    avail_height
                    ));
    }
}
void HorzLayoutWidget::layout_children_horz()
{
    // TODO: This is probably really slow.  Need to make it faster.

    // This function is more complicated than simple because it
    // reads its childrens' size requests and honors it.

    // We need to know the same information from above
    double avail_width = size->width - (margin->total_horz() + padding->total_horz());
    double avail_height = size->height - (margin->total_vert() + padding->total_vert());
    int child_count = children.size();
    int children_to_size = child_count; // How many children need to be resized?

    // Subtract the gap between children
    avail_width -= (child_count - 1) * spacing;

    // Array to hold widget_width vs its order (Used to calc positon)
    std::vector<double> child_widths;   // -1 means it needs to be auto sized
    for (int loopX = 0; loopX < child_count; loopX++)
        child_widths.push_back(0);

    // Loop through the children and, if any are sized, remove their width from avail_width
    for (int loopX = 0; loopX < child_count; loopX++)
    {
        if (children.at(loopX)->get_requested_size() != 0)
        {
            // Create a pointer to their requested size
            Size *chld_size = children.at(loopX)->get_requested_size();
            // Make sure they're not just requesting auto size
            if (chld_size->width > -1)
            {
                // Subtract their size from the available width
                avail_width -= chld_size->width;
                // Update the widths array
                child_widths[loopX] = chld_size->width;
                // decrement the resize count
                children_to_size--;
            }
            else
            {
                // Requesting to be autosized
                child_widths[loopX] = -1;
            }
            // dereference the pointer
            chld_size = 0;
        }
        else
        {
            // We will need to auto size this widget, so add it to the table
            child_widths[loopX] = -1;
        }
    }

    // At this point, we know how much space we have left to allocate, and we
    // know how many widgets need to fit into this space
    double widget_width = avail_width / children_to_size;

    // Now we can size them all
    double cumul_x = size->x + margin->left + padding->left;
    for (int loopX = 0; loopX < child_count; loopX++)
    {
        // Our Temperary coordinates
        double x, y, w, h;
        x = y = w = h = 0;

        // -- Assign x
        x = cumul_x;
        // update the cumulative x
        cumul_x += child_widths[loopX] > -1 ? child_widths[loopX] + spacing : widget_width + spacing;

        // -- Assign y
        y = size->y + margin->top + padding->top;

        // -- Assign Width
        w = child_widths[loopX] > -1 ? child_widths[loopX] : widget_width;

        // -- Assign height
        if (children.at(loopX)->get_requested_size() != 0)
        {
            double req_h = children.at(loopX)->get_requested_size()->height;
            h = req_h > -1 ? req_h : avail_height; // -1 is autosize
        }
        else
            h = avail_height;

        // -- Assign these to the child
        children.at(loopX)->set_size(new Size(x, y, w, h));
    }
}
// Finally, the function that is actually called from Draw()
void HorzLayoutWidget::layout_children()
{
    if (HonorChildSizes)
        layout_children_horz();
    else
        layout_children_horz_simple();
}
