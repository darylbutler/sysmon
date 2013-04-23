#ifndef HORZ_LAYOUT_WIDGET_H
#define HORZ_LAYOUT_WIDGET_H

class HorzLayoutWidget : public LayoutWidget
{
protected:
    // Our layout Methods
    void layout_children();
    void layout_children_horz_simple();
    void layout_children_horz();
public:
    // Our constructor
    HorzLayoutWidget();
    // Option
    bool HonorChildSizes;   // Should we let widgets size themseves?
};

#endif
