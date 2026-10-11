#include <iostream>
#include <gtest/gtest.h>
#include <stdexcept>

#include "../include/Group-7-project-ridge-lib/matrix.hpp"

using namespace ridge;

TEST(Matrix, ConstructionAndAccess) {
    Matrix matrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(matrix.rows(), 2u);
    EXPECT_EQ(matrix.cols(), 3u);
    EXPECT_DOUBLE_EQ(matrix(1, 2), 6.0);
    matrix(0, 0) = 9.0;
    EXPECT_DOUBLE_EQ(matrix(0, 0), 9.0);

    EXPECT_THROW(Matrix(2, 2, {1, 2, 3}), std::invalid_argument);
    EXPECT_THROW(matrix(2, 0), std::out_of_range);
    EXPECT_THROW(matrix(0, 3), std::out_of_range);
}

TEST(Matrix, IdentityAndTranspose) {
    Matrix identity = Matrix::identity(3);
    EXPECT_DOUBLE_EQ(identity(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(identity(0, 1), 0.0);

    Matrix transposed = Matrix(2, 3, {1, 2, 3, 4, 5, 6}).transpose();
    EXPECT_EQ(transposed.rows(), 3u);
    EXPECT_EQ(transposed.cols(), 2u);
    EXPECT_DOUBLE_EQ(transposed(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(transposed(0, 1), 4.0);
}

TEST(Matrix, AdditionSubtractionAndScaling) {
    Matrix a(1, 2, {1, 2}), b(1, 2, {3, 5});
    EXPECT_DOUBLE_EQ((a + b)(0, 1), 7.0);
    EXPECT_DOUBLE_EQ((b - a)(0, 0), 2.0);
    EXPECT_DOUBLE_EQ((a * 3.0)(0, 1), 6.0);
    EXPECT_THROW(a + Matrix(2, 1), std::invalid_argument);
    EXPECT_THROW(a - Matrix(2, 1), std::invalid_argument);
}

TEST(Matrix, Multiplication) {
    Matrix a(2, 2, {1, 2, 3, 4}), b(2, 2, {5, 6, 7, 8});
    Matrix product = a * b;
    EXPECT_DOUBLE_EQ(product(0, 0), 19.0);
    EXPECT_DOUBLE_EQ(product(0, 1), 22.0);
    EXPECT_DOUBLE_EQ(product(1, 0), 43.0);
    EXPECT_DOUBLE_EQ(product(1, 1), 50.0);

    Matrix rectangular(2, 3, {1, 2, 3, 4, 5, 6});
    Matrix result = rectangular * Matrix(3, 1, {1, 1, 1});
    EXPECT_DOUBLE_EQ(result(1, 0), 15.0);
    EXPECT_THROW(rectangular * rectangular, std::invalid_argument);
}

TEST(Matrix, VectorOperations) {
    Matrix matrix(2, 2, {1, 2, 3, 4});
    Vector result = matrix.multiply({1, 1}); 
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 7.0);
    EXPECT_THROW(matrix.multiply({1, 2, 3}), std::invalid_argument);
    EXPECT_DOUBLE_EQ(dot({1, 2, 3}, {4, 5, 6}), 32.0);
    EXPECT_THROW(dot({1}, {1, 2}), std::invalid_argument);
}

TEST(Matrix, RowAndColumn) {
    Matrix matrix(2, 2, {1, 2, 3, 4});
    EXPECT_EQ(matrix.row(1), (Vector{3, 4}));
    EXPECT_EQ(matrix.column(0), (Vector{1, 3}));
    EXPECT_THROW(matrix.row(2), std::out_of_range);
    EXPECT_THROW(matrix.column(2), std::out_of_range);
}
