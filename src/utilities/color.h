#ifndef COLOR_H
#define COLOR_H

using namespace std;

// Struct for Cairo's rgb color model
struct Color
{
    double red, green, blue, alpha;

    // Constructors
    Color();
    Color(double r, double g, double b);
    Color(double r, double g, double b, double a);
    Color(string hex);

    // Helper
    void set_source(Cairo::RefPtr<Cairo::Context> cr);
    // Helper
    void set_from_hex(string hex);
private:
    // -- Private Constuctor
    void setup(double r, double g, double b, double a);

    // Takes a 2 char hex string and turns it into an int
    int hex_str_to_int(string str);

    // Returns the value of a char in hex
    int hex_char_to_int(char c);
};

#endif
