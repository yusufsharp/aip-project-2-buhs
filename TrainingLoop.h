#ifndef TRAINING_LOOP_H
#define TRAINING_LOOP_H

#include <vector>
#include "TensorsNet.h"

/**
 * @brief Функция для обучения нейронной сети.
 *
 * @param net Обучаемая нейронная сеть.
 * @param train_images Набор тренировочных изображений, представленных в виде двумерных массивов.
 * @param train_labels Набор меток классов для тренировочных изображений.
 * @param epochs Количество эпох обучения.
 * @param learning_rate Скорость обучения.
 * @param momentum Момент для градиентного спуска.
 *
 * @details Эта функция выполняет обучение нейронной сети, используя предоставленные тренировочные данные.
 * Она выполняет прямой и обратный проходы для каждого изображения и обновляет веса и смещения сети.
 */
void trainNetwork(TensorsNet& net, const std::vector<std::vector<double>>& train_images, const std::vector<unsigned char>& train_labels, int epochs, double learning_rate, double momentum);

/**
 * @brief Функция для сохранения весов и смещений нейронной сети в файлы.
 *
 * @param net Нейронная сеть, чьи веса и смещения необходимо сохранить.
 * @param filename1 Имя файла для сохранения весов.
 * @param filename2 Имя файла для сохранения смещений.
 *
 * @details Эта функция сохраняет текущие веса и смещения всех слоев нейронной сети в указанные файлы.
 */
void saveWeightsAndBiases(const TensorsNet& net, const std::string& filename1, const std::string& filename2);

/**
 * @brief Функция для предсказания числа на основе входного изображения.
 *
 * @param net Нейронная сеть, используемая для предсказания.
 * @param image Изображение, представленное в виде двумерного массива (28x28).
 *
 * @details Эта функция выполняет предсказание на основе входного изображения, выполняя прямой проход через сеть.
 * Она выводит предсказанное число и значения выходного слоя.
 */
void predictDigit(TensorsNet& net, const std::vector<std::vector<double>>& image);

#endif // TRAINING_LOOP_H
