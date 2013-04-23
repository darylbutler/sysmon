#ifndef VERT_LAYOUT_WIDGET_H
#define VERT_LAYOUT_WIDGET_H

class VertLayoutWidget : public LayoutWidget
{
protected:
    // Our layout Methods
    void layout_children();
    void layout_children_vert_simple();
    void layout_children_vert();
public:
    // Our constructor
    VertLayoutWidget();
    // Option
    bool HonorChildSizes;   // Should we let widgets size themseves?
};

#endif
