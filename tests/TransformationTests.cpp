#include <gtest/gtest.h>
#include "Tuple.h"
#include "Matrix.h"
#include <math.h>

const float HALF_QUARTER = M_PI / 4;
const float FULL_QUARTER = M_PI / 2;

TEST(TransformationTest, CreateTranslationMatrix)
{
	Matrix *translation = Matrix::createTranslation(2, 3, 4);
	float expectedMatrixValues[4][4] = {
        {1, 0, 0, 2},
        {0, 1, 0, 3},
        {0, 0, 1, 4},
        {0, 0, 0, 1}};
	Matrix *expectedTranslationMatrix = new Matrix(expectedMatrixValues);
	EXPECT_EQ(*translation, *expectedTranslationMatrix);

	delete translation;
	delete expectedTranslationMatrix;
}

TEST(TransformationTest, TranslateMatrix)
{
	Matrix *identity = Matrix::identity(4, 4);
	Matrix *translation = identity->translate(2, 3, 4);
	float expectedMatrixValues[4][4] = {
        {1, 0, 0, 2},
        {0, 1, 0, 3},
        {0, 0, 1, 4},
        {0, 0, 0, 1}};
	Matrix *expectedTranslationMatrix = new Matrix(expectedMatrixValues);
	EXPECT_EQ(*translation, *expectedTranslationMatrix);

	delete identity;
	delete translation;
	delete expectedTranslationMatrix;
}

TEST(TransformationTest, MultiplyingByATranslationMatrix)
{
	Matrix *transform = Matrix::createTranslation(5, -3, 2);
	Tuple *point = createPoint(-3, 4, 5);
	Tuple *result = transform->multiply(*point);
	Tuple *expectedResult = createPoint(2, 1, 7);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete transform;
	delete point;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, MultiplyingByTheInverseOfATranslation)
{
	Matrix *transform = Matrix::createTranslation(5, -3, 2);
	Matrix *inverse = transform->inverse();
	Tuple *point = createPoint(-3, 4, 5);
	Tuple *result = inverse->multiply(*point);
	Tuple *expectedResult = createPoint(-8, 7, 3);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete transform;
	delete inverse;
	delete point;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, MultiplyingTranslationMatrixByAVectorShouldNotChangeVector)
{
	Matrix *transform = Matrix::createTranslation(5, -3, 2);
	Tuple *vector = createVector(-3, 4, 5);
	Tuple *resultVector = transform->multiply(*vector);

	EXPECT_TRUE(tuplesAreEqual(resultVector, vector));

	delete transform;
	delete vector;
	delete resultVector;
}

TEST(TransformationTest, CreateScalingMatrix)
{
	Matrix *scalingMatrix = Matrix::createScaling(2, 3 ,4);
	float expectedMatrixValues[4][4] = {
        {2, 0, 0, 0},
        {0, 3, 0, 0},
        {0, 0, 4, 0},
        {0, 0, 0, 1}};
	Matrix *expectedMatrix = new Matrix(expectedMatrixValues);
	EXPECT_EQ(*scalingMatrix, *expectedMatrix);

	delete scalingMatrix;
	delete expectedMatrix;
}

TEST(TransformationTest, ScaleMatrix)
{
	Matrix *identity = Matrix::identity(4, 4);
	Matrix *scalingMatrix = identity->scale(2, 3 ,4);
	float expectedMatrixValues[4][4] = {
        {2, 0, 0, 0},
        {0, 3, 0, 0},
        {0, 0, 4, 0},
        {0, 0, 0, 1}};
	Matrix *expectedMatrix = new Matrix(expectedMatrixValues);
	EXPECT_EQ(*scalingMatrix, *expectedMatrix);

	delete identity;
	delete scalingMatrix;
	delete expectedMatrix;
}

TEST(TransformationTest, ScalingAppliedToPoint)
{
	Matrix *scalingMatrix = Matrix::createScaling(2, 3, 4);
	Tuple *point = createPoint(-4, 6, 8);
	Tuple *result = scalingMatrix->multiply(*point);
	Tuple *expectedResult = createPoint(-8, 18, 32);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete scalingMatrix;
	delete point;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, ScalingMatrixMultipliedByAVector)
{
	Matrix *scalingMatrix = Matrix::createScaling(2, 3, 4);
	Tuple *vector = createVector(-4, 6, 8);

	Tuple *result = scalingMatrix->multiply(*vector);
	Tuple *expectedResult = createVector(-8, 18, 32);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete scalingMatrix;
	delete vector;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, MultiplyingVectorByTheInverseOfAScalingMatrixShrinksTheVector)
{
	Matrix *scalingMatrix = Matrix::createScaling(2, 3, 4);
	Matrix *inverse = scalingMatrix->inverse();

	Tuple *vector = createVector(-4, 6, 8);
	Tuple *result = inverse->multiply(*vector);

	Tuple *expectedResult = createVector(-2, 2, 2);
	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete scalingMatrix;
	delete inverse;
	delete vector;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, ReflectionMatrixMultipliedByAPoint)
{
	Matrix *reflectionMatrix = Matrix::createScaling(-1, 1, 1);
	Tuple *point = createPoint(2, 3 , 4);
	Tuple *result = reflectionMatrix->multiply(*point);
	Tuple *expectedResult = createPoint(-2, 3, 4);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete reflectionMatrix;
	delete point;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheXAxisHalfQuarter)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *halfQuarter = Matrix::createRotationX(M_PI / 4);
	Tuple *result = halfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(0, sqrtf(2) / 2, sqrtf(2) / 2);
	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete halfQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheXAxisFullQuarter)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *fullQuarter = Matrix::createRotationX(M_PI / 2);
	Tuple *result = fullQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(0, 0, 1);
	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete fullQuarter;
	delete result;
	delete expectedResult;
}


TEST(TransformationTest, RotateAPointAroundTheXAxisHalfQuarterFluent)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *identity = Matrix::identity(4, 4);
	Matrix *halfQuarter = identity->rotateX(M_PI / 4);
	Tuple *result = halfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(0, sqrtf(2) / 2, sqrtf(2) / 2);
	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete identity;
	delete halfQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, InverseOfAnXRotationRotatesInTheOppositeDirection)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *halfQuarter = Matrix::createRotationX(M_PI / 4);
	Matrix *inverseHalfQuarter = halfQuarter->inverse();
	Tuple *result = inverseHalfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(0, sqrt(2) / 2, -sqrt(2) / 2);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete halfQuarter;
	delete inverseHalfQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheYAxisHalfQuarter)
{
	Tuple *point = createPoint(0, 0, 1);
	Matrix *halfQuarter = Matrix::createRotationY(HALF_QUARTER);
	Tuple *result = halfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(sqrt(2)/2, 0, sqrt(2) / 2);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete halfQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheYAxisFullQuarter)
{
	Tuple *point = createPoint(0, 0, 1);
	Matrix *fullQuarter = Matrix::createRotationY(FULL_QUARTER);
	Tuple *result = fullQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(1, 0, 0);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete fullQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheYAxisHalfQuarterFluent)
{
	Tuple *point = createPoint(0, 0, 1);
	Matrix *identity = Matrix::identity(4, 4);
	Matrix *halfQuarter = identity->rotateY(HALF_QUARTER);
	Tuple *result = halfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(sqrt(2)/2, 0, sqrt(2) / 2);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete identity;
	delete halfQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheZAxisHalfQuarter)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *halfQuarter = Matrix::createRotationZ(HALF_QUARTER);
	Tuple *result = halfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(-sqrt(2)/2, sqrt(2)/2, 0);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete halfQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, RotateAPointAroundTheZAxisHalfQuarterFluent)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *identity = Matrix::identity(4, 4);
	Matrix *halfQuarter = identity->rotateZ(HALF_QUARTER);
	Tuple *result = halfQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(-sqrt(2)/2, sqrt(2)/2, 0);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete halfQuarter;
	delete result;
	delete expectedResult;
}


TEST(TransformationTest, RotateAPointAroundTheZAxisFullQuarter)
{
	Tuple *point = createPoint(0, 1, 0);
	Matrix *fullQuarter = Matrix::createRotationZ(FULL_QUARTER);
	Tuple *result = fullQuarter->multiply(*point);
	Tuple *expectedResult = createPoint(-1, 0, 0);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete fullQuarter;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, ShearingTransformationMovesXInProportionToY)
{
	Tuple *point = createPoint(2, 3, 4);
	Matrix *shearing = Matrix::createShearing(1, 0, 0, 0, 0, 0);

	Tuple *result = shearing->multiply(*point);
	Tuple *expectedResult = createPoint(5, 3, 4);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete shearing;
	delete result;
	delete expectedResult;
}

void assertShearingTransform(Matrix *shearing, Tuple* expectedResult) {
	Tuple *point = createPoint(2, 3, 4);

	Tuple *result = shearing->multiply(*point);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete result;
}

TEST(TransformationTest, ShearingTransformationMovesXInProportionToZ)
{
	Matrix *shearing = Matrix::createShearing(0, 1, 0, 0, 0, 0);
	Tuple *expectedResult = createPoint(6, 3, 4);
	assertShearingTransform(shearing, expectedResult);

	delete shearing;
	delete expectedResult;
}

TEST(TransformationTest, ShearingTransformationMovesYInProportionToX)
{
	Matrix *shearing = Matrix::createShearing(0, 0, 1, 0, 0, 0);
	Tuple *expectedResult = createPoint(2, 5, 4);
	assertShearingTransform(shearing, expectedResult);

	delete shearing;
	delete expectedResult;
}

TEST(TransformationTest, ShearingTransformationMovesYInProportionToZ)
{
	Matrix *shearing = Matrix::createShearing(0, 0, 0, 1, 0, 0);
	Tuple *expectedResult = createPoint(2, 7, 4);
	assertShearingTransform(shearing, expectedResult);

	delete shearing;
	delete expectedResult;
}

TEST(TransformationTest, ShearingTransformationMovesZInProportionToX)
{
	Matrix *shearing = Matrix::createShearing(0, 0, 0, 0, 1, 0);
	Tuple *expectedResult = createPoint(2, 3, 6);
	assertShearingTransform(shearing, expectedResult);

	delete shearing;
	delete expectedResult;
}

TEST(TransformationTest, ShearingTransformationMovesZInProportionToY)
{
	Matrix *shearing = Matrix::createShearing(0, 0, 0, 0, 0, 1);
	Tuple *expectedResult = createPoint(2, 3, 7);
	assertShearingTransform(shearing, expectedResult);

	delete shearing;
	delete expectedResult;
}

TEST(TransformationTest, ShearMatrixTransformation)
{
	Matrix *identity = Matrix::identity(4, 4);
	Matrix *shearing = identity->shear(0, 0, 1, 0, 0, 0);
	Tuple *expectedResult = createPoint(2, 5, 4);
	assertShearingTransform(shearing, expectedResult);

	delete identity;
	delete shearing;
	delete expectedResult;
}

TEST(TransformationTest, IndividualTransformationsAreAppliedInSequence)
{
	Tuple *point = createPoint(1, 0 , 1);
	Matrix *a = Matrix::createRotationX(M_PI / 2);
	Matrix *b = Matrix::createScaling(5, 5, 5);
	Matrix *c = Matrix::createTranslation(10, 5, 7);

	Tuple *point2 = a->multiply(*point);
	Tuple *expectedPoint2Result = createPoint(1, -1, 0);
	EXPECT_TRUE(tuplesAreEqual(point2, expectedPoint2Result));

	Tuple *point3 = b->multiply(*point2);
	Tuple *expectedPoint3Result = createPoint(5, -5, 0);
	EXPECT_TRUE(tuplesAreEqual(point3, expectedPoint3Result));

	Tuple *point4 = c->multiply(*point3);
	Tuple *expectedPoint4Result = createPoint(15, 0, 7);
	EXPECT_TRUE(tuplesAreEqual(point4, expectedPoint4Result));

	delete point;
	delete a;
	delete b;
	delete c;
	delete point2;
	delete expectedPoint2Result;
	delete point3;
	delete expectedPoint3Result;
	delete point4;
	delete expectedPoint4Result;
}

TEST(TransformationTest, ChainedTransformationsMustBeAppliedInReverseOrder)
{
	Tuple *point = createPoint(1, 0, 1);
	Matrix *a = Matrix::createRotationX(FULL_QUARTER);
	Matrix *b = Matrix::createScaling(5, 5, 5);
	Matrix *c = Matrix::createTranslation(10, 5, 7);

	Matrix *transform = c->multiply(*b->multiply(*a));
	Tuple *result = transform->multiply(*point);
	Tuple *expectedResult = createPoint(15, 0, 7);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete a;
	delete b;
	delete c;
	delete transform;
	delete result;
	delete expectedResult;
}

TEST(TransformationTest, ChainedTransformationsMustBeAppliedInReverseOrderFluentInterface)
{
	Tuple *point = createPoint(1, 0, 1);
	Matrix *identity = Matrix::identity(4,4);
	Matrix *transform = identity->rotateX(FULL_QUARTER)->scale(5, 5, 5)->translate(10, 5, 7);

	Tuple *result = transform->multiply(*point);
	Tuple *expectedResult = createPoint(15, 0, 7);

	EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

	delete point;
	delete identity;
	delete transform;
	delete result;
	delete expectedResult;
}