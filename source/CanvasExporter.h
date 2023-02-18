#include "Canvas.h"
#include <string>

#ifndef _CANVAS_EXPORTER_H
#define _CANVAS_EXPORTER_H

std::string* ppmFromCanvas(Canvas* canvas);

void savePPMFileFromCanvas(Canvas* canvas, std::string filename);

#endif