
#include "Matrix.h"
#include "FloatHelper.h"
#include <math.h>
#include <stdexcept>
#include <iostream>

float* Matrix::operator[](int rowIndex) const
{
	return values[rowIndex];
}

Matrix::Matrix(float data[2][2])
{
	rows = 2;
	columns = 2;
	values = new float*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new float[columns];
		values[i][0] = data[i][0];
		values[i][1] = data[i][1];
	}
}

Matrix::Matrix(float data[3][3])
{
	rows = 3;
	columns = 3;
	values = new float*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new float[columns];
		values[i][0] = data[i][0];
		values[i][1] = data[i][1];
		values[i][2] = data[i][2];
	}
}

Matrix::Matrix(float data[4][4])
{
	rows = 4;
	columns = 4;
	values = new float*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new float[columns];
		values[i][0] = data[i][0];
		values[i][1] = data[i][1];
		values[i][2] = data[i][2];
		values[i][3] = data[i][3];
	}
}

Matrix* Matrix::identity(int rows, int columns)
{
	Matrix *identityMatrix = new Matrix(rows, columns);
	for (int i = 0; i < rows; i++)
		(*identityMatrix)[i][i] = 1;

	return identityMatrix;
}


float Matrix::get(int x, int y) const
{
	return values[x][y];
}

Matrix::Matrix(int numberOfRows, int numberOfColumns)
{
	rows = numberOfRows;
	columns = numberOfColumns;
	values = new float*[rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new float[columns];
		for (int j = 0; j < columns; j++) {
			values[i][j] = 0;
		}
	}
}

Matrix* Matrix::multiply(Matrix& matrixB) const
{
	if (matrixB.columns != columns || matrixB.rows != columns) {
		return 0;
	}

	Matrix *resultMatrix = new Matrix(rows, columns);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < matrixB.columns; col++) {
			(*resultMatrix)[row][col] =
				(*this)[row][0] * matrixB[0][col] +
				(*this)[row][1] * matrixB[1][col] +
				(*this)[row][2] * matrixB[2][col] +
				(*this)[row][3] * matrixB[3][col];
		}
	}

	return resultMatrix;
}

Tuple* Matrix::multiply(Tuple& tuple) const
{
	float values[4];
	for (int r = 0; r < rows; r++) {
		values[r] = (*this)[r][0] * tuple.x +
					(*this)[r][1] * tuple.y +
					(*this)[r][2] * tuple.z +
					(*this)[r][3] * tuple.w;
	}

	return new Tuple(values[0], values[1], values[2], values[3]);
}

bool Matrix::operator==(const Matrix& other) const {
	if (other.columns != columns || other.rows != columns) {
		return false;
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (!areEqual(values[r][c], other[r][c]))
				return false;
		}
	}

	return true;
}

Matrix* Matrix::identity() {
	return Matrix::identity(rows, columns);
}

Matrix* Matrix::transpose() {
	Matrix *transposed = new Matrix(rows, columns);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			(*transposed)[r][c] = (*this)[c][r];
		}
	}

	return transposed;
}

float Matrix::determinant() {
	if (rows == 2 && columns == 2)
		return values[0][0] * values[1][1] - values[0][1] * values[1][0];
	else {
		float sum = 0;
		for (int c = 0; c < columns; c++) {
			float result = values[0][c] * this->cofactor(0, c);
			sum += result;
		}

		return sum;
	}

	return 0;
}

Matrix* Matrix::subMatrix(int row, int column) {
	Matrix *subMatrix = new Matrix(rows - 1, columns - 1);

	int rowIndex = 0;
	for (int r = 0; r < rows; r++) {
		int columnIndex = 0;
		if (r != row) {
			for (int c = 0; c < columns; c++) {
				if (c != column) {
					(*subMatrix)[rowIndex][columnIndex] = values[r][c];
					columnIndex++;
				}
			}

			rowIndex++;
		}
	}
	return subMatrix;
}

float Matrix::minor(int row, int col) {
	Matrix *subMatrix = this->subMatrix(row, col);
	float minor = subMatrix->determinant();
	delete subMatrix;

	return minor;
}

float Matrix::cofactor(int row, int col) {
	float minor = this->minor(row, col);
	if ((row + col) % 2 == 0) {
		return minor;
	}

	return minor * -1;
}

bool Matrix::isInvertible() {
	return !areEqual(this->determinant(), 0);
}

Matrix* Matrix::inverse() {
	float determinant = this->determinant();
	if (areEqual(determinant, 0)) {
		throw std::invalid_argument("Matrix is not invertible because the determinant is zero");
	}

	Matrix *inverseMatrix = new Matrix(rows, columns);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			float cofactor = this->cofactor(row, col);
			(*inverseMatrix)[col][row] = cofactor / determinant;
		}
	}

	return inverseMatrix;
}

Matrix::~Matrix() {
	for (int r = 0; r < rows; r++) {
		delete values[r];
	}
}

std::ostream& operator<< (std::ostream& stream, const Matrix& matrix) {
	stream << "Matrix(" << matrix.rows << ", " << matrix.columns << ")" << std::endl;
	for (int r = 0; r < matrix.rows; r++) {
		stream << "[";
		for (int c = 0; c < matrix.columns; c++) {
			stream << matrix.values[r][c];
			if (c < matrix.columns - 1) {
				stream << ", ";
			}
		}
		stream << "]" << std::endl;
	}

	return stream;
}

Matrix* Matrix::createTranslation(float x, float y, float z) {
	float matrixValues[4][4] = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1}};

	return new Matrix(matrixValues);
}

Matrix* Matrix::createScaling(float x, float y, float z) {
	float matrixValues[4][4] = {
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1}
	};

	return new Matrix(matrixValues);
}

Matrix* Matrix::createRotationX(float radians) {
	float matrixValues[4][4] = {
		{1, 0, 0, 0},
		{0, cosf(radians), -sinf(radians), 0},
		{0, sinf(radians), cosf(radians), 0},
		{0, 0, 0 ,1}
	};

	return new Matrix(matrixValues);
}

Matrix* Matrix::createRotationY(float radians) {
	float matrixValues[4][4] = {
		{cos(radians), 0, sin(radians), 0},
		{0, 1, 0, 0},
		{-sin(radians), 0, cos(radians), 0},
		{0, 0, 0, 1}
	};

	return new Matrix(matrixValues);
}

Matrix* Matrix::createRotationZ(float radians) {
	float matrixValues[4][4] = {
		{cos(radians), -sin(radians), 0, 0},
		{sin(radians), cos(radians), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	return new Matrix(matrixValues);
}

Matrix* Matrix::createShearing(float xy, float xx, float yx, float yz, float zx, float zy) {
	float matrixValues[4][4] = {
		{1, xy, xx, 0},
		{yx, 1, yz, 0},
		{zx, zy, 1, 0},
		{0, 0, 0, 1}
	};

	return new Matrix(matrixValues);
}

Matrix* Matrix::translate(float x, float y, float z) {
	Matrix *translation = createTranslation(x, y, z);
	Matrix *result = translation->multiply(*this);
	delete translation;
	return result;
}

Matrix* Matrix::scale(float x, float y, float z) {
	Matrix *scaleMatrix = createScaling(x, y, z);
	Matrix *result = scaleMatrix->multiply(*this);
	delete scaleMatrix;
	return result;
}

Matrix* Matrix::rotateX(float radians) {
	Matrix *rotation = createRotationX(radians);
	Matrix *result = rotation->multiply(*this);
	delete rotation;
	return result;
}

Matrix* Matrix::rotateY(float radians) {
	Matrix *rotation = createRotationY(radians);
	Matrix *result = rotation->multiply(*this);
	delete rotation;
	return result;
}

Matrix* Matrix::rotateZ(float radians) {
	Matrix *rotation = createRotationZ(radians);
	Matrix *result = rotation->multiply(*this);
	delete rotation;
	return result;
}

Matrix *Matrix::shear(float xy, float xx, float yx, float yz, float zx, float zy) {
	Matrix *shear = createShearing(xy, xx, yx, yz, zx, zy);
	Matrix *result = shear->multiply(*this);
	delete shear;
	return result;
}
