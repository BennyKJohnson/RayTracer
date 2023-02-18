#include "Color.h"

#ifndef _CANVAS_H
#define _CANVAS_H

class Canvas
{
	public:
		Canvas(int width, int height);

		Color* getPixel(int x, int y);

		void writePixel(int x, int y, Color* color);

		~Canvas();

		int width;

		int height;

	private:
		Color*** pixels;
};

#endif