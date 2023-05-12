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

private:
	float **values;
	int rows;
	int columns;
};


#endif