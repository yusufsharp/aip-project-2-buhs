//
// Created by pc on 12.06.2024.
//
/**
 * @file predict.h
 * @brief Заголовочный файл для функций, которые обеспечивают предсказание модели.
 */

#ifndef AIP_PROJECT_2_BUHS_PREDICT_H
#define AIP_PROJECT_2_BUHS_PREDICT_H

#include <iostream>
#include <vector>
#include "TensorsNet.h"

/**
 * @brief Считывает матрицу из файла.
 *
 * Эта функция открывает файл и считывает данные в матрицу размером rows x cols.
 *
 * @param filename Путь к файлу.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Считанная матрица.
 */
std::vector<std::vector<double>> readMatrixFromFile(const std::string& filename, int rows, int cols);

/**
 * @brief Преобразует матрицу в одномерный вектор.
 *
 * Эта функция преобразует двумерную матрицу в одномерный вектор, объединяя все строки.
 *
 * @param matrix Исходная матрица.
 * @return Одномерный вектор.
 */
std::vector<double> flattenMatrix(const std::vector<std::vector<double>>& matrix);

/**
 * @brief Предсказывает цифру на изображении.
 *
 * Эта функция считывает изображение из файла, преобразует его в одномерный вектор и передает
 * его в нейронную сеть для предсказания цифры.
 *
 * @param net Объект нейронной сети TensorsNet.
 * @param filename Путь к файлу изображения.
 * @return Предсказанная цифра.
 */
int predictDigit(TensorsNet& net, const std::string& filename);

#endif // AIP_PROJECT_2_BUHS_PREDICT_H
