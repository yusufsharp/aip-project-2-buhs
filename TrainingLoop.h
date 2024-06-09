#ifndef TRAINING_LOOP_H
#define TRAINING_LOOP_H

#include <vector>
#include "TensorsNet.h"

// Функция для обучения сети
void trainNetwork(TensorsNet &net, const std::vector<std::vector<double>> &train_images,
                  const std::vector<unsigned char> &train_labels, int epochs, double learning_rate, double momentum);

// Функция для сохранения весов и смещений
void saveWeightsAndBiases(const TensorsNet &net, const std::string &filename);

void loadWeightsAndBiases(TensorsNet &net, const std::string &filename);

std::vector<double> predict(TensorsNet& net, const std::vector<double>& input_image);

#endif // TRAINING_LOOP_H
