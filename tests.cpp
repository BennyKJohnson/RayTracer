#include <gtest/gtest.h>
#include "Tuple.h"

TEST(Tuple, CreatePoint)
{
    Tuple *point = createPoint(4.3, -4.2, 3.1);

    EXPECT_FLOAT_EQ(point->x, 4.3);
    EXPECT_FLOAT_EQ(point->y, -4.2);
    EXPECT_FLOAT_EQ(point->z, 3.1);
    EXPECT_FLOAT_EQ(point->w, 1.0);

    free(point);
}

TEST(Tuple, ATupleWithWEqualToOneIsAPoint)
{
    Tuple *point = createPoint(4.3, -4.2, 3.1);
    EXPECT_TRUE(isPoint(point));
}

TEST(Tuple, ATupleWithWEqualToOneIsNotAVector)
{
    Tuple *point = createPoint(4.3, -4.2, 3.1);
    EXPECT_FALSE(isVector(point));
}

TEST(Tuple, CreateVector)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    EXPECT_FLOAT_EQ(vector->x, 4.3);
    EXPECT_FLOAT_EQ(vector->y, -4.2);
    EXPECT_FLOAT_EQ(vector->z, 3.1);
    EXPECT_FLOAT_EQ(vector->w, 0.0);

    free(vector);
}

TEST(Tuple, ATupleWithWEqualToZeroIsNotAPoint)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    EXPECT_FALSE(isPoint(vector));
}

TEST(Tuple, ATupleWithWEqualToZeroIsAVector)
{
    Tuple *vector = createVector(4.3, -4.2, 3.1);
    EXPECT_TRUE(isVector(vector));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}