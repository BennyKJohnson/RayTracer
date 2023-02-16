#include <gtest/gtest.h>
#include "Color.h"

void colorsAreEqual(Color *c1, Color *c2) {
    EXPECT_FLOAT_EQ(c1->red, c2->red);
    EXPECT_FLOAT_EQ(c1->green, c2->green);
    EXPECT_FLOAT_EQ(c1->blue, c2->blue);
}

TEST(Color, CreateColor)
{
    Color *color = new Color(-0.5, 0.4, 1.7);
    EXPECT_FLOAT_EQ(color->red, -0.5);
    EXPECT_FLOAT_EQ(color->green, 0.4);
    EXPECT_FLOAT_EQ(color->blue, 1.7);

    delete color;
}

TEST(Color, ColorsAreEqualIfRGBComponentsAreEqual)
{
    Color *c1 = new Color(0.9, 0.6, 0.75);
    Color *c2 = new Color(0.9, 0.6, 0.75);
    EXPECT_TRUE(*c1 == *c2);

    delete c1;
    delete c2;
}

TEST(Color, ColorsAreNotEqualIfRGBComponentsAreNotEqual)
{
    Color *c1 = new Color(0.9, 0.6, 0.75);
    Color *c2 = new Color(0.1, 0.6, 0.75);
    EXPECT_FALSE(*c1 == *c2);

    delete c1;
    delete c2;
}

TEST(Color, AddColors)
{
    Color *c1 = new Color(0.9, 0.6, 0.75);
    Color *c2 = new Color(0.7, 0.1, 0.25);

    Color *combinedColor = c1->add(c2);

    Color *expectedColor = new Color(1.6, 0.7, 1.0);
    colorsAreEqual(combinedColor, expectedColor);

    delete c1;
    delete c2;
    delete combinedColor;
    delete expectedColor;
}

TEST(Color, SubtractColors)
{
    Color *c1 = new Color(0.9, 0.6, 0.75);
    Color *c2 = new Color(0.7, 0.1, 0.25);

    Color *result = c1->subtract(c2);
    Color *expectedColor = new Color(0.2, 0.5, 0.5);
    colorsAreEqual(result, expectedColor);

    delete c1;
    delete c2;
    delete result;
    delete expectedColor;
}

TEST(Color, MultiplyColorByScalar)
{
    Color *color = new Color(0.2, 0.3, 0.4);
    Color *result = color->multiply(2);
    
    Color *expectedColor = new Color(0.4, 0.6, 0.8);
    colorsAreEqual(result, expectedColor);

    delete color;
    delete result;
    delete expectedColor;
}

TEST(Color, ColorProduct)
{
    Color *c1 = new Color(1.0, 0.2, 0.4);
    Color *c2 = new Color(0.9, 1.0, 0.1);

    Color *result = c1->product(c2);
    Color *expectedColor = new Color(0.9, 0.2, 0.04);
    colorsAreEqual(result, expectedColor);
}
