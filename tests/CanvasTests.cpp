#include <gtest/gtest.h>
#include "Canvas.h"
#include "ColorTestHelpers.h"

TEST(Canvas, CreateCanvas)
{
	Canvas *canvas = new Canvas(10, 20);

	Color *blackColor = new Color(0, 0, 0);

	EXPECT_EQ(canvas->width, 10);
	EXPECT_EQ(canvas->height, 20);

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 20; y++) {
			Color *pixel = canvas->getPixel(x, y);
			colorsAreEqual(pixel, blackColor);
		}
	}

	delete canvas;
	delete blackColor;
}

TEST(Canvas, WritePixelToCanvas)
{
	Canvas *canvas = new Canvas(10, 20);
	Color *redColor = new Color(1, 0, 0);
	Color *whiteColor = new Color(1, 1, 1);

	canvas->writePixel(0, 0, whiteColor);
	canvas->writePixel(2, 3, redColor);

	Color *whitePixelColor = canvas->getPixel(0, 0);
	colorsAreEqual(whitePixelColor, whiteColor);

	Color *redPixelColor = canvas->getPixel(2, 3);
	colorsAreEqual(redPixelColor, redColor);

	delete canvas;
}