/*
 * This is a simple struct to help work with cairo's colors and hex colors.
 *
 * Cairo uses the rgb model, but each value is between 0 and 1, while the hex
 * value are between 0 and 255.
 */

#include <iostream>
#include <string>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include "color.h"

using namespace std;

// ----------------------------------------------------------------------------
// -- Constructors
// ----------------------------------------------------------------------------
void Color::setup(double r, double g, double b, double a)
{
    this->red   = r;
    this->green = g;
    this->blue  = b;
    this->alpha = a;
}
Color::Color()
{
    setup(1, 1, 1, 1);
}
Color::Color(double r, double g, double b)
{
    setup(r, g, b, 1);
}
Color::Color(double r, double g, double b, double a)
{
    setup(r, g, b, a);
}
Color::Color(string hex)
{
    set_from_hex(hex);
}

// ----------------------------------------------------------------------------
// -- Public
// ----------------------------------------------------------------------------
void Color::set_source(Cairo::RefPtr<Cairo::Context> cr)
{
    cr->set_source_rgba(this->red, this->green, this->blue, this->alpha);
}

void Color::set_from_hex(string hex)
{
    // Converts a string of a hex color into the current Color struct

    // Ensure a valid string
    if (int(hex.size()) == 7 && hex[0] == '#')
        hex = hex.substr(1, 6); // Remove the hash
    if (int(hex.size()) != 6)
    {
        // Log Error because the string hex does not match a good hex string
        cerr << "Color->SetFromHex failed, string not valid. Got: " << hex << endl;
    }

    // Split the string into three colors
    string sR = hex.substr(0, 2);
    string sG = hex.substr(2, 2);
    string sB = hex.substr(4, 2);

    int r = hex_str_to_int(sR);
    int g = hex_str_to_int(sG);
    int b = hex_str_to_int(sB);

    // Now, finally, set the local values to the percent of 255
    this->red    = r / 255.0;
    this->green  = g / 255.0;
    this->blue   = b / 255.0;
    this->alpha  = 1.0;
}

// ----------------------------------------------------------------------------
// -- Private
// ----------------------------------------------------------------------------
int Color::hex_str_to_int(string str)
{
    // 15 == f, 16 == 10
    int left_val = hex_char_to_int(str[0]);
    int right_val = hex_char_to_int(str[1]);

    return (left_val * 16) + right_val;
}

// Probably reinventing the wheel and then killing it.  Awesomely.  But I don't
// care, it's late and I am tired.

int Color::hex_char_to_int(char c)
{
    switch (c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            return -1;  // Oh shit, bro!
    }
}

