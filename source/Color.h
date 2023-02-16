#ifndef _COLOR_H
#define _COLOR_H

class Color
{
	public:
		Color(float red, float green, float blue): red(red), green(green), blue(blue) {}

		Color* add(Color* color);

		Color* subtract(Color *color);

		Color* multiply(float scalar);

		Color* product(Color *color);

		bool operator==(const Color &other) const;

		float red;

		float green;

		float blue;
};

#endif
