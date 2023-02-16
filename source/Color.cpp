#include "Color.h"
#include "FloatHelper.h"

Color* Color::add(Color* color) {
	return new Color(
		red + color->red,
		green + color->green,
		blue + color->blue);
}

Color* Color::subtract(Color *color) {
	return new Color(
		red - color->red,
		green - color->green,
		blue - color->blue
	);
}

Color* Color::multiply(float scalar) {
	return new Color(
		red * scalar,
		green * scalar,
		blue * scalar
	);
}

Color* Color::product(Color *color) {
	return new Color(
		red * color->red,
		green * color->green,
		blue * color->blue
	);
}

bool Color::operator==(const Color &other) const {
	return areEqual(red, other.red) && areEqual(green, other.green) && areEqual(blue, other.blue);
}