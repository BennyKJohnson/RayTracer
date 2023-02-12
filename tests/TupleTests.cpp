#include <gtest/gtest.h>
#include "Tuple.h"

TEST(Tuple, CreatePoint)
{
    Tuple *point = createPoint(4.3, -4.2, 3.1);

    EXPECT_FLOAT_EQ(point->x, 4.3);
    EXPECT_FLOAT_EQ(point->y, -4.2);
    EXPECT_FLOAT_EQ(point->z, 3.1);
    EXPECT_FLOAT_EQ(point->w, 1.0);

    delete point;
}

TEST(Tuple, ATupleWithWEqualToOneIsAPoint)
{
    Tuple *point = createPoint(4.3, -4.2, 3.1);
    EXPECT_TRUE(point->isPoint());

    delete point;
}

TEST(Tuple, ATupleWithWEqualToOneIsNotAVector)
{
    Tuple *point = createPoint(4.3, -4.2, 3.1);
    EXPECT_FALSE(point->isVector());

    delete point;
}

TEST(Tuple, CreateVector)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    EXPECT_FLOAT_EQ(vector->x, 4.3);
    EXPECT_FLOAT_EQ(vector->y, -4.2);
    EXPECT_FLOAT_EQ(vector->z, 3.1);
    EXPECT_FLOAT_EQ(vector->w, 0.0);

    delete vector;
}

TEST(Tuple, ATupleWithWEqualToZeroIsNotAPoint)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    EXPECT_FALSE(vector->isPoint());

    delete vector;
}

TEST(Tuple, ATupleWithWEqualToZeroIsAVector)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    EXPECT_TRUE(vector->isVector());

    delete vector;
}

TEST(Tuple, VectorsWithDifferentXValuesAreNotEqual)
{
    Tuple *vectorA = createVector(4.3, -4.2, 3.0);
    Tuple *vectorB = createVector(4.4, -4.2, 3.0);

    EXPECT_FALSE(tuplesAreEqual(vectorA, vectorB));

    delete vectorA;
    delete vectorB;
}

TEST(Tuple, VectorsWithDifferentYValuesAreNotEqual)
{
    Tuple *vectorA = createVector(4.4, -4.1, 3.0);
    Tuple *vectorB = createVector(4.4, -4.2, 3.0);

    EXPECT_FALSE(tuplesAreEqual(vectorA, vectorB));

    delete vectorA;
    delete vectorB;
}

TEST(Tuple, VectorsWithDifferentZValuesAreNotEqual)
{
    Tuple *vectorA = createVector(4.3, -4.2, 3.1);
    Tuple *vectorB = createVector(4.3, -4.2, 3.0);

    EXPECT_FALSE(tuplesAreEqual(vectorA, vectorB));

    delete vectorA;
    delete vectorB;
}

TEST(Tuple, VectorsWithEqualComponentsAreEqual)
{
    Tuple *vectorA = createVector(4.3, -4.2, 3.1);
    Tuple *vectorB = createVector(4.3, -4.2, 3.1);

    EXPECT_TRUE(*vectorA == *vectorB);

    delete vectorA;
    delete vectorB;
}

TEST(Tuple, VectorAndPointWithSameXYZAreNotEqual)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    Tuple *point = createPoint(4.3, -4.2, 3.1);

    EXPECT_FALSE(tuplesAreEqual(vector, point));

    delete vector;
    delete point;
}

TEST(Tuple, AddVectorAndVector)
{
    Tuple *vectorA = createVector(3, -2, 5);
    Tuple *vectorB = createVector(-2, 3, 1);

    Tuple *expectedResult = createVector(1, 1, 6);
    Tuple *result = vectorA->add(vectorB);

    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete vectorA;
    delete vectorB;
    delete expectedResult;
    delete result;
}

TEST(Tuple, AddVectorAndPoint)
{
    Tuple *point = createPoint(3, -2, 5);
    Tuple *vector = createVector(-2, 3, 1);

    Tuple *expectedResult = createPoint(1, 1, 6);
    Tuple *result = point->add(vector);

    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete point;
    delete vector;
    delete expectedResult;
    delete result;
}

TEST(Tuple, AddTwoPoints)
{
    Tuple *pointA = createPoint(3, -2, 5);
    Tuple *pointB = createPoint(-2, 3, 1);

    Tuple *expectedResult = (Tuple*)malloc(sizeof(Tuple));
    expectedResult->x = 1;
    expectedResult->y = 1;
    expectedResult->z = 6;
    expectedResult->w = 2;
    Tuple *result = pointA->add(pointB);

    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete pointA;
    delete pointB;
    delete expectedResult;
    delete result;
}

TEST(Tuple, SubtractTwoPoints)
{
    Tuple *pointA = createPoint(3, 2, 1);
    Tuple *pointB = createPoint(5, 6, 7);
    Tuple *result = pointA->subtract(pointB);

    Tuple *expectedResult = createVector(-2, -4, -6);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete pointA;
    delete pointB;
    delete result;
    delete expectedResult;
}

TEST(Tuple, SubtractVectorFromAPoint)
{
    Tuple *point = createPoint(3, 2 , 1);
    Tuple *vector = createVector(5, 6, 7);
    Tuple *result = point->subtract(vector);

    Tuple *expectedResult = createPoint(-2, -4, -6);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete point;
    delete vector;
    delete result;
    delete expectedResult;
}

TEST(Tuple, SubtractTwoVectors)
{
    Tuple *vectorA = createVector(3, 2, 1);
    Tuple *vectorB = createVector(5, 6, 7);
    
    Tuple *result = vectorA->subtract(vectorB);

    Tuple *expectedResult = createVector(-2, -4, -6);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete vectorA;
    delete vectorB;
    delete result;
    delete expectedResult;
}

TEST(Tuple, SubtractVectorFromAZeroVector)
{
    Tuple *zero = createVector(0, 0, 0);
    Tuple *vector = createVector(1, -2, 3);

    Tuple *result = zero->subtract(vector);

    Tuple *expectedResult = createVector(-1, 2, -3);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete zero;
    delete vector;
    delete result;
    delete expectedResult;
}

TEST(Tuple, NegateTuple)
{
    Tuple *tuple = new Tuple(1, -2, 3, -4);
    Tuple *negatedTuple = tuple->negate();

    Tuple *expected = new Tuple(-1, 2, -3, 4);
    EXPECT_TRUE(tuplesAreEqual(negatedTuple, expected));

    delete tuple;
    delete negatedTuple;
    delete expected;
}

TEST(Tuple, MultiplyTuple)
{
    Tuple *tuple = new Tuple(1, -2, 3, -4);
    Tuple *result = tuple->multiply(3.5);

    Tuple *expected = new Tuple(3.5, -7, 10.5, -14);
    EXPECT_TRUE(tuplesAreEqual(result, expected));

    delete tuple;
    delete result;
    delete expected;
}

TEST(Tuple, DivisionTuple)
{
    Tuple *tuple = new Tuple(1, -2, 3, -4);
    Tuple *result = tuple->divide(2);

    Tuple *expected = new Tuple(0.5, -1, 1.5, -2);
    EXPECT_TRUE(tuplesAreEqual(result, expected));

    delete tuple;
    delete result;
    delete expected;
}

TEST(Tuple, MagnitudeOfVectorWithNonZeroXComponent)
{
    Tuple *vector = createVector(1, 0, 0);
    float magnitude = vector->magnitude();
    EXPECT_FLOAT_EQ(magnitude, 1);

    delete vector;
}

TEST(Tuple, MagnitudeOfVectorWithNonZeroYComponent)
{
    Tuple *vector = createVector(0, 2, 0);
    float magnitude = vector->magnitude();
    EXPECT_FLOAT_EQ(magnitude, 2);
    
    delete vector;
}

TEST(Tuple, MagnitudeOfVectorWithNonZeroZComponent)
{
    Tuple *vector = createVector(0, 0, 1);
    float magnitude = vector->magnitude();
    EXPECT_FLOAT_EQ(magnitude, 1);

    delete vector;
}

TEST(Tuple, MagnitudeOfVectorWithNonZeroXYZComponents)
{
    Tuple *vector = createVector(-1, -2, -3);
    float magnitude = vector->magnitude();
    EXPECT_FLOAT_EQ(magnitude, sqrtf(14));

    delete vector;
}

TEST(Tuple, NormalizeNonZeroXComponent)
{
    Tuple *vector = createVector(4, 0, 0);
    Tuple *result = vector->normalize();

    Tuple *expectedResult = createVector(1, 0, 0);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete vector;
    delete result;
    delete expectedResult;
}

TEST(Tuple, NormalizeANonZeroMagnitudeVectorIntoUnitVector)
{
    Tuple *vector = createVector(1, 2, 3);
    Tuple *result = vector->normalize();

    Tuple *expectedResult = createVector(1/sqrtf(14), 2/sqrtf(14), 3/sqrtf(14));
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete vector;
    delete result;
    delete expectedResult;
}

TEST(Tuple, DotProductOfTwoVectors)
{
    Tuple *a = createVector(1, 2, 3);
    Tuple *b = createVector(2, 3 ,4);

   EXPECT_FLOAT_EQ(a->dot(b), 20);

   delete a;
   delete b;
}

TEST(Tuple, DotProductOfTwoVectors2)
{
    Tuple *a = createVector(2, 2, 3);
    Tuple *b = createVector(2, 3 ,4);

   EXPECT_FLOAT_EQ(a->dot(b), 22);

   delete a;
   delete b;
}

TEST(Tuple, TwoVectorCrossProductACrossB)
{
    Tuple *a = createVector(1, 2, 3);
    Tuple *b = createVector(2, 3, 4);
    Tuple *result = a->cross(b);

    Tuple *expectedResult = createVector(-1, 2, -1);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete a;
    delete b;
    delete result;
    delete expectedResult;
}

TEST(Tuple, TwoVectorCrossProductBCrossA)
{
    Tuple *a = createVector(1, 2, 3);
    Tuple *b = createVector(2, 3, 4);
    Tuple *result = b->cross(a);

    Tuple *expectedResult = createVector(1, -2, 1);
    EXPECT_TRUE(tuplesAreEqual(result, expectedResult));

    delete a;
    delete b;
    delete result;
    delete expectedResult;
}
