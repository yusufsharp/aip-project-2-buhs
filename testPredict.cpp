#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TensorsNet.h"
#include "matrix.h"
#include "predict.h"

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