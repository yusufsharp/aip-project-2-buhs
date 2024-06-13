//
// Created by pc on 12.06.2024.
//

#ifndef AIP_PROJECT_2_BUHS_PREDICT_H
#define AIP_PROJECT_2_BUHS_PREDICT_H

#include <iostream>
#include <vector>
#include "TensorsNet.h"

std::vector<std::vector<double>> readMatrixFromFile(const std::string& filename, int rows, int cols);

std::vector<double> flattenMatrix(const std::vector<std::vector<double>>& matrix);

int predictDigit(TensorsNet& net, const std::string& filename);

#endif //AIP_PROJECT_2_BUHS_PREDICT_H
