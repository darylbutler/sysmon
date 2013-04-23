// This was a sample file from google test sources.  I modified it to work for
// my project.

#include <limits.h>
#include <string>
#include <vector>
#include <iostream>
#include "../src/utilities/color.h"
#include "gtest/gtest.h"

// Can it turn a valid hex string into a valid cairo color?
TEST(Color, StringToHexBlack)
{
    Color *c = new Color("#000000");
    Color *f = new Color(0, 0, 0, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexRed)
{
    Color *c = new Color("#Ff0000");
    Color *f = new Color(1, 0, 0, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexGreen)
{
    Color *c = new Color("#00fF00");
    Color *f = new Color(0, 1, 0, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexBlue)
{
    Color *c = new Color("#0000Ff");
    Color *f = new Color(0, 0, 1, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexYellow)
{
    Color *c = new Color("#ffff00");
    Color *f = new Color(1, 1, 0, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexAqua)
{
    Color *c = new Color("#00ffff");
    Color *f = new Color(0, 1, 1, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexMagenta)
{
    Color *c = new Color("#ff00ff");
    Color *f = new Color(1, 0, 1, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexGray)
{
    Color *c = new Color("#C0c0C0");
    double d = 192.0 / 255.0;

    EXPECT_DOUBLE_EQ(d, c->red);
    EXPECT_DOUBLE_EQ(d, c->green);
    EXPECT_DOUBLE_EQ(d, c->blue);

    delete c;
}
TEST(Color, StringToHexWhite)
{
    Color *c = new Color("#fFffFF");
    Color *f = new Color(1, 1, 1, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}
TEST(Color, StringToHexNoHashWhite)
{
    Color *c = new Color("FFFFFF");
    Color *f = new Color(1, 1, 1, 1);

    EXPECT_DOUBLE_EQ(f->red, c->red);
    EXPECT_DOUBLE_EQ(f->green, c->green);
    EXPECT_DOUBLE_EQ(f->blue, c->blue);

    delete c;
    delete f;
}


