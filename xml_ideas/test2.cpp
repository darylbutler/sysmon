#include <iostream>
#include <X11/Xlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <unistd.h>

#include "src/widgets/vert_layout_widget.cpp"


#include "src/data_sources/data_source.cpp"
#include <string>

int main()
{

    std::cout << "Hello, world!" << std::endl;

    DataSource *src = new DataSource();
    std::cout << src->GetValues()[0] << std::endl;
    return 1;




    // Open a display.
    Display *d = XOpenDisplay(0);

    if ( d )
    {
        // Create the window
        Window w = XCreateWindow(
                       d,                        // Display
                       DefaultRootWindow(d),     // Parent
                       0, 0,                     // x, y
                       200, 600,                 // width, height
                       0,                        // border width
                       CopyFromParent,           // depth
                       CopyFromParent,           // class
                       CopyFromParent,           // visual
                       0,                        // valuemask
                       0                         // attributes
                   );

        // Show the window
        XMapWindow(d, w);
        XFlush(d);

        // Test Widget
        cairo_surface_t *cs = cairo_xlib_surface_create(
                                  d,    // X11 display
                                  w,    // Drawable surface, in this case the window
                                  DefaultVisual(d, 0),
                                  200,
                                  600
                              );

        cairo_t *cr = cairo_create(cs);

        XSelectInput(d, w, ExposureMask);

        // ---------------------------------------------------------
        // Setup Widget
        VertLayoutWidget *wid = new VertLayoutWidget();
        wid->set_size(new Size(0, 0, 200, 600));
        wid->set_margin(new Box(10));
        wid->set_padding(new Box(8));
        wid->set_spacing(8);
        wid->HonorChildSizes = true; // start simple

        // Add a child
        Widget *chld = new Widget();
        chld->set_background_color(new Color(1, 0, 0, 1));
        chld->set_border_color(new Color(0, 1, 0, 1));
        chld->set_margin(new Box(0));
        chld->set_requested_size(new Size(-1, -1, -1, -1));

        // 1st Child
        wid->add_child(chld);
        // 2nd
        wid->add_child(new Widget(*chld));
        // 3rd
        wid->add_child(new Widget(*chld));


        //chld->set_requested_size(new Size(-1, -1, 500, 100));


        wid->Draw(cr);
        // ----------------------------------------------------------

        XEvent ev;
        while (1) {
            XNextEvent(d, &ev);
            std::cout << "Event!" << std::endl;
            if (ev.type == Expose) {
                wid->Draw(cr);
            }
        }

        cairo_destroy(cr);
        cairo_surface_destroy(cs);
        XCloseDisplay(d);
        return 0;
    }
}
