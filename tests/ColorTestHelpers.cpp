#include <gtest/gtest.h>
#include "Color.h"

void colorsAreEqual(Color *c1, Color *c2) {
    EXPECT_FLOAT_EQ(c1->red, c2->red);
    EXPECT_FLOAT_EQ(c1->green, c2->green);
    EXPECT_FLOAT_EQ(c1->blue, c2->blue);
}