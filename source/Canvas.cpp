#include "Canvas.h"

Canvas::Canvas(int width, int height): width(width), height(height)
{
	pixels = new Color**[height];
	Color *blackColor = new Color(0, 0, 0);
	for (int y = 0; y < height; y++) {
		pixels[y] = new Color*[width];
		for (int x = 0; x < width; x++) {
			pixels[y][x] = 0;
			writePixel(x, y, blackColor);
		}
	}

	delete blackColor;
}

Color* Canvas::getPixel(int x, int y) {
	return pixels[y][x];
}

void Canvas::writePixel(int x, int y, Color* color) {
	Color *existingColor = pixels[y][x];
	if (existingColor != 0) {
		delete existingColor;
	}

	pixels[y][x] = new Color(color->red, color->green, color->blue);
}

Canvas::~Canvas() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			delete pixels[y][x];
		}
		delete pixels[y];
	}
}