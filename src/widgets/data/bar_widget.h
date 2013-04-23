#ifndef BAR_WIDGET_H
#define BAR_WIDGET_H

class BarWidget : public Widget
{
private:
    // Private Members
    double m_maxValue;                  // The largest number we will show
    unique_ptr<DataSource> source;      // Where we pull our data from
    double m_value;                     // This is the value that we draw from
    string m_data_id;                   // id to give to the datasource so we get the right
                                        // value (Passed to datasource->getvalue(id);)
    // Visual ---
    unique_ptr<Color>   bar_color, 
                        bar_border_color,       // Colors of the filled bar
                        bar_bg_color, 
                        bar_bg_border_color;    // Colors of the unfilled bar
    double bar_border_width, bar_bg_border_width;
    bool draw_bar_bg, draw_bar_bg_border,   // Drawing
         draw_bar_border;                   // options
    bool vertical;          // Determines whether the bar is vertical or horizontal

    // Private Methods
    virtual void draw_bar(Cairo::RefPtr<Cairo::Context> cr); // Our part of the draw function
    virtual void update_value();        // Use our datasource to update our value
public:
    // -- Constructor and Destructor
    BarWidget(DataSource *src);
    ~BarWidget();

    // -- Accessors
    // get
    inline double get_max_value()           { return m_maxValue; }
    inline double get_value()               { return m_value; }
    inline string get_data_id()             { return m_data_id; }
    inline Color* get_bar_color()           { return bar_color.get(); }
    inline Color* get_bar_border_color()    { return bar_border_color.get(); }
    inline Color* get_bar_bg_color()        { return bar_bg_color.get(); }
    inline Color* get_bar_bg_border_color() { return bar_bg_border_color.get(); }
    inline double get_bar_border_width()    { return bar_border_width; }
    inline double get_bar_bg_border_width() { return bar_bg_border_width; }
    inline bool   get_draw_bar_bg()         { return draw_bar_bg; }
    inline bool   get_draw_bar_bg_border()  { return draw_bar_bg_border; }
    inline bool   get_draw_bar_border()     { return draw_bar_border; }
    inline bool   get_is_vertical()         { return vertical; }
    // set
    inline void set_max_value(double d) { m_maxValue = d; }
    inline void set_value(double d) { m_value = d; }
    inline void set_data_id(string s) { m_data_id = s; }
    inline void set_bar_color(Color *c) { bar_color.reset(c); }
    inline void set_bar_border_color(Color *c) { bar_border_color.reset(c); }
    inline void set_bar_bg_color(Color *c) { bar_bg_color.reset(c); }
    inline void set_bar_bg_border_color(Color *c) { bar_bg_border_color.reset(c); }
    inline void set_bar_border_width(double d) { bar_border_width = d; }
    inline void set_bar_bg_border_width(double d) { bar_bg_border_width = d; }
    inline void set_draw_bar_bg(bool b) { draw_bar_bg = b; }
    inline void set_draw_bar_bg_border(bool b) { draw_bar_bg_border = b; }
    inline void set_draw_bar_border(bool b) { draw_bar_border = b; }
    inline void set_is_vertical(bool b) { vertical = b; }

    // Public Methods
    void Draw(Cairo::RefPtr<Cairo::Context> cr); // Our implementation of the draw function

};

#endif
