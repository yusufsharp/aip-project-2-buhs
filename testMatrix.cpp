#include <gtest/gtest.h>
#include "matrix.h"
#include "TensorsNet.h"

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
// Тест для конструктора TensorsNet
TEST(TensorsNetTest, Constructor) {
    std::vector<size_t> layers = {2, 3, 1};
    TensorsNet net(layers);

    // Проверяем, что граф создан корректно
    ASSERT_EQ(net.graph.size(), 2);
    ASSERT_EQ(net.graph[0].size(), 1);
    ASSERT_EQ(net.graph[1].size(), 1);

    // Проверяем размеры матриц весов
    ASSERT_EQ(net.graph[0][0].weights.getRows(), 3);
    ASSERT_EQ(net.graph[0][0].weights.getCols(), 2);
    ASSERT_EQ(net.graph[1][0].weights.getRows(), 1);
    ASSERT_EQ(net.graph[1][0].weights.getCols(), 3);
}

// Тест для метода addLayer
TEST(TensorsNetTest, AddLayer) {
    TensorsNet net({2, 3});

    // Проверяем, что слой добавлен корректно
    ASSERT_EQ(net.graph.size(), 1);
    ASSERT_EQ(net.graph[0].size(), 1);
    ASSERT_EQ(net.graph[0][0].weights.getRows(), 3);
    ASSERT_EQ(net.graph[0][0].weights.getCols(), 2);
    ASSERT_EQ(net.graph[0][0].biases.size(), 3);
    ASSERT_EQ(net.graph[0][0].d_biases.size(), 3);
    ASSERT_EQ(net.graph[0][0].output_values.size(), 3);
    ASSERT_EQ(net.graph[0][0].layer_type, 0);
}

// Тест для метода forwardPass
TEST(TensorsNetTest, ForwardPass) {
    std::vector<size_t> layers = {2, 3, 1};
    TensorsNet net(layers);

    std::vector<double> inputs = {1.0, 2.0};
    net.forwardPass(inputs);

    // Проверяем, что выходные значения первого слоя корректны
    ASSERT_EQ(net.graph[0][0].output_values.size(), 3);

    // Проверяем, что выходные значения второго слоя корректны
    ASSERT_EQ(net.graph[1][0].output_values.size(), 1);
}

// Тест для метода relu_function
TEST(TensorsNetTest, ReluFunction) {
    std::vector<double> values = {-1.0, 0.0, 1.0, 2.0};
    TensorsNet::relu_function(values);

    // Проверяем, что значения после применения ReLU корректны
    ASSERT_EQ(values[0], 0.0);
    ASSERT_EQ(values[1], 0.0);
    ASSERT_EQ(values[2], 1.0);
    ASSERT_EQ(values[3], 2.0);
}

// Тест для метода relu_function_derived
TEST(TensorsNetTest, ReluFunctionDerived) {
    std::vector<double> values = {-1.0, 0.0, 1.0, 2.0};
    std::vector<double> derived = TensorsNet::relu_function_derived(values);

    // Проверяем, что значения после применения производной ReLU корректны
    ASSERT_EQ(derived[0], 0.0);
    ASSERT_EQ(derived[1], 0.0);
    ASSERT_EQ(derived[2], 1.0);
    ASSERT_EQ(derived[3], 1.0);
}

TEST(TensorsNetTest, AddLayerNegative) {
    TensorsNet net({2, 3});

    // Попытка добавить слой с неправильным размером
    net.addLayer(0, 0, 0);

    // Проверяем, что слой не добавлен
    ASSERT_EQ(net.graph.size(), 1);
}

TEST(MatrixTest, AddNegative) {
    Matrix mat1(2, 2);
    mat1.setElement(0, 0, 1.0);
    mat1.setElement(0, 1, 2.0);
    mat1.setElement(1, 0, 3.0);
    mat1.setElement(1, 1, 4.0);

    // Попытка добавить матрицу с неправильными размерами
    Matrix mat3(3, 3);
    Matrix result = mat1.add(mat3);
    EXPECT_EQ(result.getRows(), 0);
    EXPECT_EQ(result.getCols(), 0);

    // Попытка добавить матрицу с отрицательными размерами
    try {
        Matrix mat4(-1, -1);
        Matrix result2 = mat1.add(mat4);
        FAIL() << "Expected std::length_error";
    } catch (const std::length_error &e) {
        EXPECT_STREQ("cannot create std::vector larger than max_size()", e.what());
    } catch (const std::exception &e) {
        FAIL() << "Expected std::length_error, but got: " << e.what();
    }
}