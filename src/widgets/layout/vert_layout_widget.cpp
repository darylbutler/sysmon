/*
 *
 *
 */

#include "layout_widget.cpp"
#include "vert_layout_widget.h"

// ---------------
// Our Constructor
// ---------------
VertLayoutWidget::VertLayoutWidget() : LayoutWidget()
{
    // By default, listen to child sizes
    HonorChildSizes = true;
}

// --------------------
// Our Layout Functions
// --------------------
void VertLayoutWidget::layout_children_vert_simple()
{
    // This function is called when HonorChildSizes is false.
    // It is much simpler to size widgets this way.

    // First, we find out how much room we have available
    double avail_width  = size->width - (margin->total_horz() + padding->total_horz());
    double avail_height = size->height - (margin->total_vert() + padding->total_vert());
    int child_count = children.size();

    // Subtract the spacing left between each child
    avail_height -= (child_count - 1) * spacing;

    // Assign the figured heights
    double widget_height = avail_height / child_count;
    for (int loopX = 0; loopX < child_count; loopX++)
    {
        children.at(loopX)->set_size(new Size(
                    size->x + margin->left + padding->left,
                    size->y + margin->top + padding->top + (loopX * (widget_height + spacing)),
                    avail_width,
                    widget_height
                    ));
    }
}
void VertLayoutWidget::layout_children_vert()
{   
    // TODO: This is probably really slow.  Need to make it faster.
    // TODO: Also, merge both Vert and Horz Layout into one class with a type switch

    // This function is more complicated than simple because it
    // reads its childrens' size requests and honors it.

    // We need to know the same information from above
    double avail_width = size->width - (margin->total_horz() + padding->total_horz());
    double avail_height = size->height - (margin->total_vert() + padding->total_vert());
    int child_count = children.size();
    int children_to_size = child_count; // How many children need to be resized?

    // Subtract the gap between children
    avail_height -= (child_count - 1) * spacing;

    // Array to hold widget_height vs its order (Used to calc positon)
    std::vector<double> child_heights;   // -1 means it needs to be auto sized
    for (int loopX = 0; loopX < child_count; loopX++)
        child_heights.push_back(0);

    // Loop through the children and, if any are sized, remove their width from avail_height
    for (int loopX = 0; loopX < child_count; loopX++)
    {
        if (children.at(loopX)->get_requested_size() != 0)
        {
            // Create a pointer to their requested size
            Size *chld_size = children.at(loopX)->get_requested_size();
            // Make sure they're not just requesting auto size
            if (chld_size->height > -1)
            {
                // Subtract their size from the available height
                avail_height -= chld_size->height;
                // Update the widths array
                child_heights[loopX] = chld_size->height;
                // decrement the resize count
                children_to_size--;
            }
            else
            {
                // Requesting to be autosized
                child_heights[loopX] = -1;
            }
            // dereference the pointer
            chld_size = 0;
        }
        else
        {
            // We will need to auto size this widget, so add it to the table
            child_heights[loopX] = -1;
        }
    }

    // At this point, we know how much space we have left to allocate, and we
    // know how many widgets need to fit into this space
    double widget_height = avail_height / children_to_size;

    // Now we can size them all
    double cumul_y = size->y + margin->top + padding->top; 
    for (int loopX = 0; loopX < child_count; loopX++)
    {
        // Our Temperary coordinates
        double x, y, w, h;
        x = y = w = h = 0;

        // -- Assign x
        x = size->x + margin->left + padding->left;

        // -- Assign y
        y = cumul_y;
        // update the cumulative y
        cumul_y += child_heights[loopX] > -1 ? child_heights[loopX] + spacing : widget_height + spacing;

        // -- Assign width
        if (children.at(loopX)->get_requested_size() != 0)
        {
            double req_w = children.at(loopX)->get_requested_size()->width;
            w = req_w > -1 ? req_w : avail_width; // -1 is autosize
        }
        else
            w = avail_width;

        // -- Assign Height
        h = child_heights[loopX] > -1 ? child_heights[loopX] : widget_height;
        
        // -- Assign these to the child
        children.at(loopX)->set_size(new Size(x, y, w, h));
    }
}

// -------
// Draw()!
//
// -- Finally, the function that is actually called from Draw()
// -------
void VertLayoutWidget::layout_children()
{
    if (HonorChildSizes)
        layout_children_vert();
    else
        layout_children_vert_simple();
}
