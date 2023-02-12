#include <stdio.h>

#ifndef _TUPLE_H
#define _TUPLE_H

bool areEqual(float a, float b);

class Tuple
{
public:
	Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	bool operator==(const Tuple &other) const;

	Tuple *add(Tuple *tupleB);

	Tuple *subtract(Tuple *tupleB);

	Tuple *negate();

	Tuple *normalize();

	float magnitude();

	float dot(Tuple *other);

	Tuple *cross(Tuple *other);

	Tuple *multiply(float scalar);

	Tuple *divide(float scalar);

	bool isPoint();

	bool isVector();

	float x;

	float y;

	float z;

	float w;
};

Tuple *createPoint(float x, float y, float z);

Tuple *createVector(float x, float y, float z);

bool tuplesAreEqual(Tuple *tupleA, Tuple *tupleB);

#endif