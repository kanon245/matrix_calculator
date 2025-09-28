#include <gtest/gtest.h>
#include "matrix.h"
#include <cmath>

TEST(MatrixTest, CreateAndFree) {
    Matrix m = create_matrix(2, 2);
    EXPECT_EQ(m.rows, 2);
    EXPECT_EQ(m.cols, 2);
    EXPECT_NE(m.data, nullptr);
    free_matrix(m);
}

TEST(MatrixTest, InvalidSize) {
    EXPECT_THROW(create_matrix(-1, 2), std::invalid_argument);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_add(A, B);
    EXPECT_EQ(C.data[0][0], 6);
    EXPECT_EQ(C.data[0][1], 8);
    EXPECT_EQ(C.data[1][0], 10);
    EXPECT_EQ(C.data[1][1], 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, MatrixMultiplication) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_multiply(A, B);
    EXPECT_EQ(C.data[0][0], 19);
    EXPECT_EQ(C.data[0][1], 22);
    EXPECT_EQ(C.data[1][0], 43);
    EXPECT_EQ(C.data[1][1], 50);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

TEST(MatrixTest, MatrixNormalization) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    Matrix B = matrix_normalize(A);

    // Проверяем, что значения в диапазоне [0, 1]
    EXPECT_GE(B.data[0][0], 0);
    EXPECT_LE(B.data[0][0], 1);
    EXPECT_GE(B.data[1][1], 0);
    EXPECT_LE(B.data[1][1], 1);

    // Проверяем конкретные значения (1->0, 2->0.333, 3->0.667, 4->1)
    EXPECT_NEAR(B.data[0][0], 0.0, 1e-6);
    EXPECT_NEAR(B.data[0][1], 1.0/3.0, 1e-6);
    EXPECT_NEAR(B.data[1][0], 2.0/3.0, 1e-6);
    EXPECT_NEAR(B.data[1][1], 1.0, 1e-6);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, MatrixNormalizationSameValues) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = 5; A.data[0][1] = 5;
    A.data[1][0] = 5; A.data[1][1] = 5;

    Matrix B = matrix_normalize(A);

    // Все значения должны быть 0.5
    EXPECT_NEAR(B.data[0][0], 0.5, 1e-6);
    EXPECT_NEAR(B.data[0][1], 0.5, 1e-6);
    EXPECT_NEAR(B.data[1][0], 0.5, 1e-6);
    EXPECT_NEAR(B.data[1][1], 0.5, 1e-6);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, MatrixNormalizationNegativeValues) {
    Matrix A = create_matrix(2, 2);
    A.data[0][0] = -2; A.data[0][1] = -1;
    A.data[1][0] = 0; A.data[1][1] = 1;

    Matrix B = matrix_normalize(A);

    // Проверяем диапазон [0, 1]
    EXPECT_GE(B.data[0][0], 0);
    EXPECT_LE(B.data[0][0], 1);
    EXPECT_GE(B.data[1][1], 0);
    EXPECT_LE(B.data[1][1], 1);

    // Проверяем конкретные значения (-2->0, -1->0.333, 0->0.667, 1->1)
    EXPECT_NEAR(B.data[0][0], 0.0, 1e-6);
    EXPECT_NEAR(B.data[0][1], 1.0/3.0, 1e-6);
    EXPECT_NEAR(B.data[1][0], 2.0/3.0, 1e-6);
    EXPECT_NEAR(B.data[1][1], 1.0, 1e-6);

    free_matrix(A);
    free_matrix(B);
}

TEST(MatrixTest, MatrixNormalizationEmptyMatrix) {
    Matrix A;
    A.data = nullptr;
    A.rows = 0;
    A.cols = 0;
    EXPECT_THROW(matrix_normalize(A), std::invalid_argument);
    // Не вызываем free_matrix(A) потому что data = nullptr
}
