#include <stdio.h>

#ifndef _TUPLE_H
#define _TUPLE_H

typedef struct Tuple {
    float x;
    float y;
    float z;
    float w;
} Tuple;

Tuple* createPoint(float x, float y, float z)
{
    Tuple *newPoint = (Tuple*)malloc(sizeof(Tuple));
    newPoint->x = x;
    newPoint->y = y;
    newPoint->z = z;
    newPoint->w = 1.0;

    return newPoint;
}

Tuple* createVector(float x, float y, float z)
{
    Tuple *newVector = (Tuple*)malloc(sizeof(Tuple));
    newVector->x = x;
    newVector->y = y;
    newVector->z = z;
    newVector->w = 0;

    return newVector;
}

bool areEqual(float a, float b) {
    return fabs(a -b) < 0.0001;
}

bool isPoint(Tuple* tuple)
{
    return areEqual(tuple->w, 1.0);
}

bool isVector(Tuple *tuple)
{
    return areEqual(tuple->w, 0.0);
}

#endif