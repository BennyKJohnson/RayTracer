#include "CanvasExporter.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string join(vector<string>* strings, string separator) {
	string str = string();
	bool first = true;
	for (auto currentString = strings->begin(); currentString != strings->end(); ++currentString)
	{
		if (!first) {
			str += separator;
		}
		first = false;
		str += *currentString;
	}

	return str;
}

string ppmComponentsFromColor(Color* color) {
	int maxColorValue = 255;
	int redComponent = min(max((int)round(color->red * maxColorValue), 0), maxColorValue);
	int greenComponent = min(max((int)round(color->green * maxColorValue), 0), maxColorValue);
	int blueComponent = min(max((int)round(color->blue * maxColorValue), 0), maxColorValue);

	return to_string(redComponent) + " " + to_string(greenComponent) + " " + to_string(blueComponent);
}

vector<string>* getPPMRowComponents(Canvas* canvas, int y) {
	vector<string> *rowComponents = new vector<string>();
	for (int x = 0; x < canvas->width; x++) {
		Color *pixelColor = canvas->getPixel(x, y);
		rowComponents->push_back(ppmComponentsFromColor(pixelColor));
	}

	return rowComponents;
}

string ppmHeaderForCanvas(Canvas *canvas)
{
	return "P3\n" + to_string(canvas->width) + " " + to_string(canvas->height) + "\n255\n";
}

string ppmBodyFromCanvas(Canvas *canvas)
{
	string body;
	for (int y = 0; y < canvas->height; y++)
	{
		vector<string> *ppmRowComponents = getPPMRowComponents(canvas, y);
		body += join(ppmRowComponents, " ") + "\n";
	
		delete ppmRowComponents;
	}

	return body;
}

string wrapPPMBodyLines(string ppmBody) {
	const int lineLimit = 70;
	const int numberOfCharsInNewLine = 1;

 	string body = ppmBody;
	int index = 0;
	while (index + lineLimit < body.length())
	{
		int nextNewLine = body.find("\n", index);
		int nextNewLineDistance = 0;
		if (nextNewLine != std::string::npos) {
			nextNewLineDistance = nextNewLine - index;
		}

		if (nextNewLineDistance > lineLimit) {
			int spaceIdxToReplace = body.rfind(" ", index + lineLimit);
			body.replace(spaceIdxToReplace, 1, "\n");
			index = spaceIdxToReplace + numberOfCharsInNewLine;
		} else {
			index = body.find("\n", index) + numberOfCharsInNewLine;
		}
	}

	return body;
}

string* ppmFromCanvas(Canvas* canvas) {
	string header = ppmHeaderForCanvas(canvas);
	string body = wrapPPMBodyLines(ppmBodyFromCanvas(canvas));

	return new string(header + body);
}

void savePPMFileFromCanvas(Canvas* canvas, std::string filename)
{
	std::ofstream file(filename);
	string *ppm = ppmFromCanvas(canvas);
	file << *ppm;
	file.close();
}