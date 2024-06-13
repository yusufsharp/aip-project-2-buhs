#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "TensorsNet.h"
#include <algorithm>

std::vector<std::vector<double>> readMatrixFromFile(const std::string& filename, int rows, int cols) {
    std::ifstream file(filename);
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return matrix;
    }

    std::string line;
    for (int i = 0; i < rows && std::getline(file, line); ++i) {
        std::istringstream iss(line);
        for (int j = 0; j < cols; ++j) {
            iss >> matrix[i][j];
        }
    }

    file.close();
    return matrix;
}

std::vector<double> flattenMatrix(const std::vector<std::vector<double>>& matrix) {
    std::vector<double> flat_matrix;
    for (const auto& row : matrix) {
        flat_matrix.insert(flat_matrix.end(), row.begin(), row.end());
    }
    return flat_matrix;
}

void predictDigit(TensorsNet& net, const std::string& filename) {
    // Step 1: Read the matrix from the file
    std::vector<std::vector<double>> matrix = readMatrixFromFile(filename, 28, 28);

    // Step 2: Flatten the matrix
    std::vector<double> flat_matrix = flattenMatrix(matrix);

    // Step 3: Use the neural network for prediction
    net.forwardPass(flat_matrix);
    std::vector<double> output = net.graph.back().back().output_values;

    // Step 4: Determine the predicted digit
    int predicted_digit = std::distance(output.begin(), std::max_element(output.begin(), output.end()));

    // Print the predicted digit
    std::cout << "Predicted Digit: " << predicted_digit << std::endl;
}