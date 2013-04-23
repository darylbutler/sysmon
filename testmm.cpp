#include <iostream>
#include <X11/Xlib.h>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include <cairomm/xlib_surface.h>
#include <unistd.h>

#include "src/widgets/layout/vert_layout_widget.cpp"
#include "src/data_sources/cpu_source.cpp"
#include "src/widgets/data/bar_widget.cpp"
#include <string>

int main()
{
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
        Cairo::RefPtr<Cairo::XlibSurface> surface = Cairo::XlibSurface::create(
                                                        d,                      // The Display
                                                        w,                      // The Drawable
                                                        DefaultVisual(d, 0),    // Visual
                                                        200,                    // Width
                                                        600                     // Height
                                                        );

        Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);

        XSelectInput(d, w, ExposureMask);

        // ---------------------------------------------------------
        // Setup Widget
        VertLayoutWidget *wid = new VertLayoutWidget();
        wid->set_size(new Size(0, 0, 200, 600));
        wid->set_margin(new Box(10));
        wid->set_padding(new Box(8));
        wid->set_spacing(8);
        wid->HonorChildSizes = true;

        // Add a child
        Widget *chld = new Widget();
        chld->set_background_color(new Color(1, 0, 0, 1));
        chld->set_border_color(new Color(0, 1, 0, 1));
        chld->set_margin(new Box(0));
        chld->set_requested_size(new Size(-1, -1, -1, -1));

        // Create the bar_widget
        CpuSource *cpuSrc = new CpuSource();
        BarWidget *bar = new BarWidget(cpuSrc);
        bar->set_requested_size(new Size(-1, -1, -1, 10));

        cpuSrc->DoWork();
        sleep(2);
        cpuSrc->DoWork();

        // 1st Child
        wid->add_child(bar);
        // 2nd
        //wid->add_child(new Widget(*chld));
        // 3rd
        //wid->add_child(new Widget(*chld));


        //chld->set_requested_size(new Size(-1, -1, 500, 100));


        wid->Draw(cr);
        // ----------------------------------------------------------

        XEvent ev;
        while (1)
        {
            // wait 2 seconds between updates
            sleep(2);

            // Check if we have a new XEvent
            if (XCheckWindowEvent(d, w, ExposureMask, &ev))
            {
                std::cout << "Event!" << std::endl;
                if (ev.type == Expose)
                {
                    wid->Draw(cr);
                }
            }

            // Update the data source and redraw
            cpuSrc->DoWork();
            wid->Draw(cr);
        }

        XCloseDisplay(d);
        return 0;
    }
}
