#include <gtest/gtest.h>
#include "Matrix.h"
#include "Tuple.h"
#include <iostream>

TEST(Matrix, Create2x2Matrix)
{
    float values[2][2] = {
        {-3, 5},
        {1, -2},
    };
    Matrix *matrix = new Matrix(values);

    EXPECT_FLOAT_EQ((*matrix)[0][0], -3);
    EXPECT_FLOAT_EQ((*matrix)[0][1], 5);

    EXPECT_FLOAT_EQ((*matrix)[1][0], 1);
    EXPECT_FLOAT_EQ((*matrix)[1][1], -2);

    delete matrix;
}

TEST(Matrix, Create3x3Matrix)
{
    float values[3][3] = {
        {-3, 5, 0},
        {1, -1, -7},
        {0, 1, 1},
    };
    Matrix *matrix = new Matrix(values);

    EXPECT_FLOAT_EQ((*matrix)[0][0], -3);
    EXPECT_FLOAT_EQ((*matrix)[0][1], 5);
    EXPECT_FLOAT_EQ((*matrix)[0][2], 0);

    EXPECT_FLOAT_EQ((*matrix)[1][0], 1);
    EXPECT_FLOAT_EQ((*matrix)[1][1], -1);
    EXPECT_FLOAT_EQ((*matrix)[1][2], -7);

    EXPECT_FLOAT_EQ((*matrix)[2][0], 0);
    EXPECT_FLOAT_EQ((*matrix)[2][1], 1);
    EXPECT_FLOAT_EQ((*matrix)[2][2], 1);

    delete matrix;
}

TEST(Matrix, Create2x2ZeroMatrix)
{
    Matrix *matrix = new Matrix(2, 2);

    EXPECT_FLOAT_EQ((*matrix)[0][0], 0);
    EXPECT_FLOAT_EQ((*matrix)[0][1], 0);

    EXPECT_FLOAT_EQ((*matrix)[1][0], 0);
    EXPECT_FLOAT_EQ((*matrix)[1][1], 0);

    delete matrix;
}

TEST(Matrix, Create4x4Matrix)
{
    float values[4][4] = {
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}};
    Matrix *matrix = new Matrix(values);

    EXPECT_FLOAT_EQ((*matrix)[1][0], 5.5);

    EXPECT_FLOAT_EQ((*matrix)[0][0], 1.0);
    EXPECT_FLOAT_EQ((*matrix)[0][1], 2.0);
    EXPECT_FLOAT_EQ((*matrix)[0][2], 3.0);
    EXPECT_FLOAT_EQ((*matrix)[0][3], 4.0);

    EXPECT_FLOAT_EQ((*matrix)[1][0], 5.5);
    EXPECT_FLOAT_EQ((*matrix)[1][1], 6.5);
    EXPECT_FLOAT_EQ((*matrix)[1][2], 7.5);
    EXPECT_FLOAT_EQ((*matrix)[1][3], 8.5);

    EXPECT_FLOAT_EQ((*matrix)[2][0], 9);
    EXPECT_FLOAT_EQ((*matrix)[2][1], 10);
    EXPECT_FLOAT_EQ((*matrix)[2][2], 11);
    EXPECT_FLOAT_EQ((*matrix)[2][3], 12);

    EXPECT_FLOAT_EQ((*matrix)[3][0], 13.5);
    EXPECT_FLOAT_EQ((*matrix)[3][1], 14.5);
    EXPECT_FLOAT_EQ((*matrix)[3][2], 15.5);
    EXPECT_FLOAT_EQ((*matrix)[3][3], 16.5);

    delete matrix;
}

TEST(Matrix, Get)
{
    float values[4][4] = {
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}};
    Matrix *matrix = new Matrix(values);

    EXPECT_FLOAT_EQ((*matrix)[1][0], 5.5);

    EXPECT_FLOAT_EQ(matrix->get(0, 0), 1.0);
    EXPECT_FLOAT_EQ(matrix->get(0, 1), 2.0);
    EXPECT_FLOAT_EQ(matrix->get(0, 2), 3.0);
    EXPECT_FLOAT_EQ(matrix->get(0, 3), 4.0);

    EXPECT_FLOAT_EQ(matrix->get(1, 0), 5.5);
    EXPECT_FLOAT_EQ(matrix->get(1, 1), 6.5);
    EXPECT_FLOAT_EQ(matrix->get(1, 2), 7.5);
    EXPECT_FLOAT_EQ(matrix->get(1, 3), 8.5);

    EXPECT_FLOAT_EQ(matrix->get(2, 0), 9);
    EXPECT_FLOAT_EQ(matrix->get(2, 1), 10);
    EXPECT_FLOAT_EQ(matrix->get(2, 2), 11);
    EXPECT_FLOAT_EQ(matrix->get(2, 3), 12);

    EXPECT_FLOAT_EQ(matrix->get(3, 0), 13.5);
    EXPECT_FLOAT_EQ(matrix->get(3, 1), 14.5);
    EXPECT_FLOAT_EQ(matrix->get(3, 2), 15.5);
    EXPECT_FLOAT_EQ(matrix->get(3, 3), 16.5);

    delete matrix;
}

TEST(Matrix, MatricesAreNotEqualIfDifferentSizes)
{
    float matrix2x2Values[2][2] = {
        {0, 0},
        {0, 0}};
    Matrix *matrix2x2 = new Matrix(matrix2x2Values);

    float matrix3x3Values[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    Matrix *matrix3x3 = new Matrix(matrix3x3Values);

    EXPECT_FALSE(*matrix2x2 == *matrix3x3);

    delete matrix2x2;
    delete matrix3x3;
}

TEST(Matrix, MatricesAreNotEqualIfTheyContainDifferentValues)
{
    float matrixAValues[2][2] = {
        {1.1, 2.2},
        {3.3, 4.4},
    };
    Matrix *matrixA = new Matrix(matrixAValues);

    float matrixBValues[2][2] = {
        {1.1, 2.2},
        {3.3, 4.5},
    };
    Matrix *matrixB = new Matrix(matrixBValues);

    EXPECT_FALSE(*matrixA == *matrixB);

    delete matrixA;
    delete matrixB;
}

TEST(Matrix, MatricesAreEqualIfIdentical2x2)
{
    float values[2][2] = {
        {1.1, 2.2},
        {3.3, 4.4},
    };
    Matrix *matrixA = new Matrix(values);
    Matrix *matrixB = new Matrix(values);

    EXPECT_EQ(*matrixA, *matrixB);

    delete matrixA;
    delete matrixB;
}

TEST(Matrix, MatricesAreEqualIfIdentical4x4)
{
    float values[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};
    Matrix *matrixA = new Matrix(values);
    Matrix *matrixB = new Matrix(values);

    EXPECT_EQ(*matrixA, *matrixB);

    delete matrixA;
    delete matrixB;
}

TEST(Matrix, MultipleTwoMatrices)
{
    float matrixAValues[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}};
    Matrix matrixA = Matrix(matrixAValues);

    float matrixBValues[4][4] = {
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}};
    Matrix matrixB = Matrix(matrixBValues);

    Matrix *result = matrixA.multiply(matrixB);

    float expectedResultValues[4][4] = {
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}};
    Matrix expectedResultMatrix = Matrix(expectedResultValues);

    EXPECT_EQ(*result, expectedResultMatrix);

    delete result;
}

TEST(Matrix, MultipleMatrixByATuple)
{
    float matrixAValues[4][4] = {
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}};
    Matrix matrixA = Matrix(matrixAValues);
    Tuple tupleB = Tuple(1, 2, 3, 1);

    Tuple *result = matrixA.multiply(tupleB);
    Tuple expectedResult = Tuple(18, 24, 33, 1);

    EXPECT_EQ(*result, expectedResult);
}

TEST(Matrix, CreateIdentityMatrix4x4)
{
    float expectedIdentityMatrixValues[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    Matrix *identityMatrix = Matrix::identity(4, 4);
    Matrix expectedIdentityMatrix = Matrix(expectedIdentityMatrixValues);
    EXPECT_EQ(*identityMatrix, expectedIdentityMatrix);

    delete identityMatrix;
}

TEST(Matrix, MultiplyingMatrixByIdentityMatrixReturnsIdenticalMatrix)
{
    float matrixAValues[4][4] = {
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}};

    Matrix matrixA = Matrix(matrixAValues);
    Matrix *matrixMultipliedByIdentity = matrixA.multiply(*matrixA.identity());

    EXPECT_EQ(*matrixMultipliedByIdentity, matrixA);
}

TEST(Matrix, MultiplyingIdentityMatrixByTupleEqualsTuple)
{
    Matrix *identityMatrix = Matrix::identity(4, 4);
    Tuple tuple = Tuple(1, 2, 3, 4);

    Tuple *resultTuple = identityMatrix->multiply(tuple);
    EXPECT_EQ(*resultTuple, tuple);

    delete identityMatrix;
    delete resultTuple;
}

TEST(Matrix, TransposingAMatrixTurnsRowsIntoColumns)
{
    float matrixAValues[4][4] = {
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}};
    Matrix matrixA = Matrix(matrixAValues);

    float expectedResult[4][4] = {
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}};
    Matrix expectedResultMatrix = Matrix(expectedResult);

    Matrix *transposedMatrix = matrixA.transpose();
    EXPECT_EQ(*transposedMatrix, expectedResultMatrix);

    delete transposedMatrix;
}

TEST(Matrix, TransposingAnIdentityMatrixResultsInIdentityMatrix)
{
    Matrix *identityMatrix = Matrix::identity(4, 4);
    Matrix *transposedIdentityMatrix = identityMatrix->transpose();
    Matrix *expectedResult = Matrix::identity(4, 4);

    EXPECT_EQ(*transposedIdentityMatrix, *expectedResult);

    delete identityMatrix;
    delete transposedIdentityMatrix;
    delete expectedResult;
}

TEST(Matrix, SubMatrixOf3x3Is2x2)
{
    float values[3][3] = {
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}};
    Matrix matrix = Matrix(values);

    Matrix *subMatrix = matrix.subMatrix(0, 2);

    float expectedMatrixValues[2][2] = {
        {-3, 2},
        {0, 6}};
    Matrix expectedMatrix = Matrix(expectedMatrixValues);

    EXPECT_EQ(*subMatrix, expectedMatrix);

    delete subMatrix;
}

TEST(Matrix, SubMatrixOf4x4Is3x3)
{
    float values[4][4] = {
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}};

    Matrix matrix = Matrix(values);
    Matrix *subMatrix = matrix.subMatrix(2, 1);

    float expectedMatrixValues[3][3] = {
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}};

    Matrix expectedMatrix = Matrix(expectedMatrixValues);

    EXPECT_EQ(*subMatrix, expectedMatrix);

    delete subMatrix;
}

TEST(Matrix, CalculateMinorOfA3x3Matrix)
{
    float matrixValues[3][3] = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};

    Matrix matrix = Matrix(matrixValues);

    EXPECT_EQ(matrix.minor(0, 0), -12);
    EXPECT_EQ(matrix.minor(1, 0), 25);
}

TEST(Matrix, CalculateCofactorOfA3x3Matrix)
{
    float matrixValues[3][3] = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}};

    Matrix matrix = Matrix(matrixValues);
    EXPECT_EQ(matrix.cofactor(0, 0), -12);
    EXPECT_EQ(matrix.cofactor(1, 0), -25);
}

TEST(Matrix, CalculateDeterminantOfA3x3Matrix)
{
    float matrixValues[3][3] = {
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}};
    Matrix matrix = Matrix(matrixValues);
    EXPECT_EQ(matrix.determinant(), -196);
}

TEST(Matrix, CalculateDeterminantOf4x4Matrix)
{
    float matrixValues[4][4] = {
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}};

    Matrix matrix = Matrix(matrixValues);
    EXPECT_EQ(matrix.determinant(), -4071);
}

TEST(Matrix, MatrixIsNotInvertibleIfTheDeterminantIsZero)
{
    float matrixValues[4][4] = {
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}};

    Matrix matrix = Matrix(matrixValues);
    EXPECT_FALSE(matrix.isInvertible());
}

TEST(Matrix, MatrixIsInvertibleIfTheDeterminantIsNonZero)
{
    float matrixValues[4][4] = {
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, 6}};

    Matrix matrix = Matrix(matrixValues);
    EXPECT_TRUE(matrix.isInvertible());
}

TEST(Matrix, CalculateTheInverseOfAMatrix4x4)
{
    float matrixValues[4][4] = {
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}};
    Matrix matrix = Matrix(matrixValues);

    float expectedValues[4][4] = {
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}};
    Matrix expectedMatrix = Matrix(expectedValues);

    Matrix *inverse = matrix.inverse();
    EXPECT_EQ(*inverse, expectedMatrix);

    delete inverse;
}

TEST(Matrix, CalculateTheInverseOfAMatrix4x4Number2)
{
    float matrixValues[4][4] = {
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4},
    };
    Matrix matrix = Matrix(matrixValues);

    float expectedValues[4][4] = {
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}};
    Matrix expectedMatrix = Matrix(expectedValues);

    Matrix *inverse = matrix.inverse();
    EXPECT_EQ(*inverse, expectedMatrix);

    delete inverse;
}

TEST(Matrix, CalculateTheInverseOfAMatrix4x4Number3)
{
    float matrixValues[4][4] = {
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}};

    Matrix matrix = Matrix(matrixValues);

    float expectedValues[4][4] = {
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}};
    Matrix expectedMatrix = Matrix(expectedValues);
    Matrix *inverse = matrix.inverse();
    EXPECT_EQ(*inverse, expectedMatrix);

    delete inverse;
}

TEST(Matrix, InverseIdentityMatrixEqualsIdentityMatrix)
{
    Matrix *identityMatrix = Matrix::identity(4, 4);
    Matrix *identityMatrixInverse = identityMatrix->inverse();

    EXPECT_EQ(*identityMatrixInverse, *identityMatrix);
    delete identityMatrixInverse;
    delete identityMatrix;
}
