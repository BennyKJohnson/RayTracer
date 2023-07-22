#include <gtest/gtest.h>
#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
#include "CanvasExporter.h"
#include "Matrix.h"
#include "Tuple.h"

using namespace std;

TEST(Clock, ExportClockDrawing)
{
	float clockRadius = 200;
	int height = 500;
	int width = 500;
	Canvas *canvas = new Canvas(width, height);
	Color *whiteColor = new Color(1, 1, 1);

	Tuple *point = createPoint(0, 0 , 1);
	for (int i = 1; i <= 12; i ++) {
		Matrix *matrix = Matrix::createRotationY(i * (M_PI / 6))->scale(clockRadius, 0, clockRadius)->translate(width/2, 0, height/2);
		Tuple *position = matrix->multiply(*point);
		canvas->writePixel(position->x, position->z, whiteColor);

		delete matrix;
		delete position;
	}

	savePPMFileFromCanvas(canvas, "clock.ppm");

	delete whiteColor;
	delete canvas;
}