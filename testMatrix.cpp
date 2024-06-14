#include <gtest/gtest.h>
#include "matrix.h"

// Тесты для конструктора Matrix
TEST(MatrixTest, Constructor) {
    Matrix mat1;
    EXPECT_EQ(mat1.getRows(), 0);
    EXPECT_EQ(mat1.getCols(), 0);

    Matrix mat2(3, 4);
    EXPECT_EQ(mat2.getRows(), 3);
    EXPECT_EQ(mat2.getCols(), 4);
}

// Тесты для функции setElement
TEST(MatrixTest, SetElement) {
    Matrix mat(3, 3);

    mat.setElement(1, 1, 5.0);
    EXPECT_DOUBLE_EQ(mat.getElement(1, 1), 5.0);

    // Проверка на неверный индекс
    testing::internal::CaptureStdout();
    mat.setElement(3, 3, 10.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Неверный индекс\n");
}

// Тесты для функции getElement
TEST(MatrixTest, GetElement) {
    Matrix mat(3, 3);
    mat.setElement(1, 1, 5.0);

    EXPECT_DOUBLE_EQ(mat.getElement(1, 1), 5.0);

    // Проверка на неверный индекс
    EXPECT_DOUBLE_EQ(mat.getElement(3, 3), 0.0);
}

// Тесты для функции t (транспонирование)
TEST(MatrixTest, Transpose) {
    Matrix mat(2, 3);
    mat.setElement(0, 0, 1.0);
    mat.setElement(0, 1, 2.0);
    mat.setElement(0, 2, 3.0);
    mat.setElement(1, 0, 4.0);
    mat.setElement(1, 1, 5.0);
    mat.setElement(1, 2, 6.0);

    Matrix transposed = mat.t();
    EXPECT_EQ(transposed.getRows(), 3);
    EXPECT_EQ(transposed.getCols(), 2);
    EXPECT_DOUBLE_EQ(transposed.getElement(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(transposed.getElement(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(transposed.getElement(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(transposed.getElement(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(transposed.getElement(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(transposed.getElement(2, 1), 6.0);
}

// Тесты для функции add (сложение матриц)
TEST(MatrixTest, Add) {
    Matrix mat1(2, 2);
    mat1.setElement(0, 0, 1.0);
    mat1.setElement(0, 1, 2.0);
    mat1.setElement(1, 0, 3.0);
    mat1.setElement(1, 1, 4.0);

    Matrix mat2(2, 2);
    mat2.setElement(0, 0, 5.0);
    mat2.setElement(0, 1, 6.0);
    mat2.setElement(1, 0, 7.0);
    mat2.setElement(1, 1, 8.0);

    Matrix result = mat1.add(mat2);
    EXPECT_DOUBLE_EQ(result.getElement(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(result.getElement(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(result.getElement(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(result.getElement(1, 1), 12.0);

    // Проверка на несовпадение размеров
    Matrix mat3(2, 3);
    Matrix result2 = mat1.add(mat3);
    EXPECT_EQ(result2.getRows(), 0);
    EXPECT_EQ(result2.getCols(), 0);
}

// Тесты для функции dot (умножение матриц)
TEST(MatrixTest, Dot) {
    Matrix mat1(2, 3);
    mat1.setElement(0, 0, 1.0);
    mat1.setElement(0, 1, 2.0);
    mat1.setElement(0, 2, 3.0);
    mat1.setElement(1, 0, 4.0);
    mat1.setElement(1, 1, 5.0);
    mat1.setElement(1, 2, 6.0);

    Matrix mat2(3, 2);
    mat2.setElement(0, 0, 7.0);
    mat2.setElement(0, 1, 8.0);
    mat2.setElement(1, 0, 9.0);
    mat2.setElement(1, 1, 10.0);
    mat2.setElement(2, 0, 11.0);
    mat2.setElement(2, 1, 12.0);

    Matrix result = mat1.dot(mat2);
    EXPECT_EQ(result.getRows(), 2);
    EXPECT_EQ(result.getCols(), 2);
    EXPECT_DOUBLE_EQ(result.getElement(0, 0), 58.0);
    EXPECT_DOUBLE_EQ(result.getElement(0, 1), 64.0);
    EXPECT_DOUBLE_EQ(result.getElement(1, 0), 139.0);
    EXPECT_DOUBLE_EQ(result.getElement(1, 1), 154.0);

    // Проверка на несовпадение размеров
    Matrix mat3(4, 2);
    Matrix result2 = mat1.dot(mat3);
    EXPECT_EQ(result2.getRows(), 0);
    EXPECT_EQ(result2.getCols(), 0);
}
