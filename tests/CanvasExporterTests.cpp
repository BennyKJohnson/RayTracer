#include <gtest/gtest.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include <stdio.h>
#include "Canvas.h"
#include "CanvasExporter.h"

using namespace std;

TEST(CanvasExporter, EmptyCanvasToPPM)
{
	Canvas *canvas = new Canvas(0, 0);
	string *ppm = ppmFromCanvas(canvas);

	string *expectedString = new string("P3\n0 0\n255\n");
	EXPECT_STREQ(ppm->c_str(), expectedString->c_str());
	
	delete ppm;
	delete expectedString;
	delete canvas;
}
 
TEST(CanvasExporter, CanvasToPPM)
{
	Canvas *canvas = new Canvas(5, 3);
	Color *c1 = new Color(1.5, 0, 0);
	Color *c2 = new Color(0, 0.5, 0);
	Color *c3 = new Color(-0.5, 0, 1);

	canvas->writePixel(0, 0, c1);
	canvas->writePixel(2, 1, c2);
	canvas->writePixel(4, 2, c3);

	string *ppm = ppmFromCanvas(canvas);

	string expectedString = string("P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n");
	EXPECT_STREQ(ppm->c_str(), expectedString.c_str());

	delete canvas;
	delete c1;
	delete c2;
	delete c3;
	delete ppm;
}

TEST(CanvasExporter, WrapsLinesGreaterThan70Characters)
{
	Canvas *canvas = new Canvas(10, 2);
	Color *color = new Color(1, 0.8, 0.6);

	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 10; x++) {
			canvas->writePixel(x, y, color);
		}
	}

	string *ppm = ppmFromCanvas(canvas);
	string expectedString = string("P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n");

	EXPECT_STREQ(ppm->c_str(), expectedString.c_str());

	delete canvas;
	delete color;
	delete ppm;
}

TEST(CanvasExporter, WriteToFile)
{
	Canvas *canvas = new Canvas(1, 1);
	Color *whiteColor = new Color(1, 1, 1);
	canvas->writePixel(0,0, whiteColor);

	char filename[] = "/tmp/canvasXXXXXX";
	int fileDescriptor = mkstemp(filename);

	savePPMFileFromCanvas(canvas, string(filename));

	std::ifstream fileStream(filename);
	std::stringstream ppmBuffer;
	ppmBuffer << fileStream.rdbuf();

	string expectedString = string("P3\n1 1\n255\n255 255 255\n");
	EXPECT_STREQ(ppmBuffer.str().c_str(), expectedString.c_str());

	unlink(filename);
	delete canvas;
}
