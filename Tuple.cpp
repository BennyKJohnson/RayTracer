#include "Tuple.h"
#include "FloatHelper.h"
#include <math.h>

bool Tuple::isPoint()
{
	return areEqual(w, 1.0);
}

bool Tuple::isVector()
{
	return areEqual(w, 0);
}

Tuple *Tuple::add(Tuple *tupleB)
{
	Tuple *newTuple = new Tuple(
		x + tupleB->x,
		y + tupleB->y,
		z + tupleB->z,
		w + tupleB->w);
	return newTuple;
}

Tuple *Tuple::subtract(Tuple *tupleB)
{
	Tuple *newTuple = new Tuple(
		x - tupleB->x,
		y - tupleB->y,
		z - tupleB->z,
		w - tupleB->w);
	return newTuple;
}

Tuple *Tuple::negate()
{
	Tuple *zeroTuple = new Tuple(0, 0, 0, 0);
	Tuple *negatedTuple = zeroTuple->subtract(this);
	delete zeroTuple;

	return negatedTuple;
}

Tuple *Tuple::normalize()
{
	float magnitudeValue = magnitude();
	return new Tuple(
		x / magnitudeValue,
		y / magnitudeValue,
		z / magnitudeValue,
		w / magnitudeValue);
}

float Tuple::magnitude()
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

float Tuple::dot(Tuple *other)
{
	return x * other->x +
		   y * other->y +
		   z * other->z +
		   w * other->w;
}

Tuple *Tuple::cross(Tuple *other)
{
	return new Tuple(
		y * other->z - z * other->y,
		z * other->x - x * other->z,
		x * other->y - y * other->x,
		0);
}

Tuple *Tuple::multiply(float scalar)
{
	return new Tuple(
		x * scalar,
		y * scalar,
		z * scalar,
		w * scalar);
}

Tuple *Tuple::divide(float scalar)
{
	return new Tuple(
		x / scalar,
		y / scalar,
		z / scalar,
		w / scalar);
}

bool Tuple::operator==(const Tuple &other) const
{
	return areEqual(x, other.x) && areEqual(y, other.y) && areEqual(z, other.z) && areEqual(w, other.w);
}

Tuple *createPoint(float x, float y, float z)
{
	Tuple *newPoint = new Tuple(x, y, z, 1.0);
	return newPoint;
}

Tuple *createVector(float x, float y, float z)
{
	Tuple *newVector = new Tuple(x, y, z, 0);

	return newVector;
}

bool tuplesAreEqual(Tuple *tupleA, Tuple *tupleB)
{
	return *tupleA == *tupleB;
}