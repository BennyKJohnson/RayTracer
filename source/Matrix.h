#include "Tuple.h"
#include <iostream>

#ifndef _MATRIX_H
#define _MATRIX_H

class Matrix
{
public:
	Matrix(float data[2][2]);

	Matrix(float data[3][3]);

	Matrix(float data[4][4]);

	Matrix(int numberOfRows, int numberOfColumns);

	float get(int x, int y) const;

	float *operator[](int rowIndex) const;

	bool operator==(const Matrix &other) const;

	~Matrix();

	Matrix *multiply(Matrix &matrixB) const;

	Tuple *multiply(Tuple &tuple) const;

	static Matrix *identity(int rows, int columns);

	Matrix *identity();

	Matrix *transpose();

	Matrix *subMatrix(int row, int col);

	float determinant();

	float minor(int row, int col);

	float cofactor(int row, int col);

	bool isInvertible();

	Matrix *inverse();

	friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix);

	Matrix* rotateX(float radians);

	Matrix* rotateY(float radians);

	Matrix* rotateZ(float radians);

	Matrix* translate(float x, float y, float z);

	Matrix* scale(float x, float y, float z);

	Matrix* shear(float xy, float xx, float yx, float yz, float zx, float zy);

	static Matrix* createTranslation(float x, float y, float z);

	static Matrix* createScaling(float x, float y, float z);

	static Matrix* createRotationX(float radians);

	static Matrix* createRotationY(float radians);

	static Matrix* createRotationZ(float radians);

	static Matrix* createShearing(float xy, float xx, float yx, float yz, float zx, float zy);

private:
	float **values;
	int rows;
	int columns;
};


#endif