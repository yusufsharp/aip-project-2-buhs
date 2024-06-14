#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TensorsNet.h"
#include "matrix.h"
#include "predict.h"
#include "data_reader.h"

// Mock class for TensorsNet
class MockTensorsNet : public TensorsNet {
public:
    MockTensorsNet(const std::vector<size_t>& all_layers) : TensorsNet(all_layers) {}
    MOCK_METHOD(void, forwardPass, (const std::vector<double>& input), (override));


    void loadWeightsAndBiases() {
        Matrix M1 = Matrix::readMatrix("../learned/weights1.txt");
        Matrix M2 = Matrix::readMatrix("../learned/weights2.txt");
        std::vector<double> V1 = Matrix::readVector("../learned/bias1.txt");
        std::vector<double> V2 = Matrix::readVector("../learned/bias2.txt");

        this->graph[0][0].weights = M1;
        this->graph[0][0].biases = V1;
        this->graph[1][0].weights = M2;
        this->graph[1][0].biases = V2;
    }
};

TEST(PredictDigitTest, ValidPredictionWithWeights) {
    std::vector<size_t> layers = {784, 128, 10};
    MockTensorsNet net(layers);
    net.loadWeightsAndBiases();
    EXPECT_CALL(net, forwardPass(testing::_)).Times(1);

    int predicted_digit = predictDigit(net, "../drawing_28x28.txt");
    EXPECT_EQ(predicted_digit, 0);
}


TEST(FlattenMatrixTest, ValidMatrix) {
    std::vector<std::vector<double>> matrix = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
    };
    std::vector<double> flat_matrix = flattenMatrix(matrix);
    std::vector<double> expected = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    EXPECT_EQ(flat_matrix, expected);
}

TEST(ReadMatrixFromFileTest, ValidFile) {
    std::vector<std::vector<double>> matrix = readMatrixFromFile("../drawing_28x28.txt", 28, 28);
    EXPECT_EQ(matrix.size(), 28);
    for (const auto& row : matrix) {
        EXPECT_EQ(row.size(), 28);
    }
}
TEST(DataNormalizationTest, NormalizeData) {
    std::vector<std::vector<double>> images = {{0.0, 50.0, 100.0}, {150.0, 200.0, 255.0}};
    NormalizeData(images);

    // Проверяем, что данные нормализованы в диапазоне от 0 до 1
    for (const auto& image : images) {
        for (double pixel : image) {
            EXPECT_GE(pixel, 0.0);
            EXPECT_LE(pixel, 1.0);
        }
    }
}

// Тест для функции readLabelFile
TEST(ReadLabelFileTest, ReadLabelFile) {
    // Создаем тестовый файл меток
    std::string filename = "test_labels.dat";
    std::ofstream file(filename, std::ios::binary);
    char magicNumber[4] = {0, 0, 0, 1};
    char numLabelsBytes[4] = {0, 0, 0, 3};
    unsigned char labels[3] = {1, 2, 3};
    file.write(magicNumber, 4);
    file.write(numLabelsBytes, 4);
    file.write(reinterpret_cast<char*>(labels), 3);
    file.close();

    std::vector<unsigned char> readLabels = readLabelFile(filename);

    // Проверяем, что метки считаны корректно
    EXPECT_EQ(readLabels.size(), 3);
    EXPECT_EQ(readLabels[0], 1);
    EXPECT_EQ(readLabels[1], 2);
    EXPECT_EQ(readLabels[2], 3);

    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

// Тест для функции readImageFile
TEST(ReadImageFileTest, ReadImageFile) {
    // Создаем тестовый файл изображений
    std::string filename = "test_images.dat";
    std::ofstream file(filename, std::ios::binary);
    char magicNumber[4] = {0, 0, 0, 1};
    char numImagesBytes[4] = {0, 0, 0, 2};
    char numRowsBytes[4] = {0, 0, 0, 2};
    char numColsBytes[4] = {0, 0, 0, 2};
    unsigned char images[8] = {0, 50, 100, 150, 200, 100, 50, 0};
    file.write(magicNumber, 4);
    file.write(numImagesBytes, 4);
    file.write(numRowsBytes, 4);
    file.write(numColsBytes, 4);
    file.write(reinterpret_cast<char*>(images), 8);
    file.close();

    std::vector<std::vector<double>> readImages = readImageFile(filename);

    // Проверяем, что изображения считаны и нормализованы корректно
    ASSERT_EQ(readImages.size(), 2);
    for (const auto& image : readImages) {
        for (double pixel : image) {
            EXPECT_GE(pixel, 0.0);
            EXPECT_LE(pixel, 1.0);
        }
    }

    // Удаляем тестовый файл
    std::remove(filename.c_str());
}

