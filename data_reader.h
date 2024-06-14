#ifndef AIP_PROJECT_2_BUHS_DATA_READER_H
#define AIP_PROJECT_2_BUHS_DATA_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

/**
 * @brief Нормализует значения пикселей в изображениях.
 *
 * Эта функция принимает вектор изображений, где каждое изображение представлено вектором значений пикселей.
 * Она находит минимальное и максимальное значения пикселей во всех изображениях и нормализует каждый пиксель
 * к диапазону от 0 до 1.
 *
 * @param images Вектор изображений, где каждое изображение представлено вектором значений пикселей.
 */
void NormalizeData(std::vector<std::vector<double>> &images);

/**
 * @brief Читает файл меток и возвращает вектор меток.
 *
 * Эта функция открывает файл меток в бинарном режиме, читает магическое число и количество меток,
 * а затем считывает все метки в вектор.
 *
 * @param filename Путь к файлу меток.
 * @return Вектор меток.
 */
std::vector<unsigned char> readLabelFile(const std::string &filename);

/**
 * @brief Читает файл изображений и возвращает вектор изображений.
 *
 * Эта функция открывает файл изображений в бинарном режиме, читает магическое число, количество изображений,
 * количество строк и столбцов для каждого изображения. Затем она считывает все изображения в вектор,
 * где каждое изображение представлено вектором значений пикселей. После считывания изображений она нормализует
 * значения пикселей.
 *
 * @param filename Путь к файлу изображений.
 * @return Вектор изображений, где каждое изображение представлено вектором значений пикселей.
 */
std::vector<std::vector<double>> readImageFile(const std::string &filename);

/**
 * @brief Выводит изображение в консоль.
 *
 * Эта функция принимает вектор значений пикселей и длину стороны изображения (предполагается, что изображение квадратное).
 * Она преобразует значения пикселей в символы и выводит их в консоль.
 *
 * @param image Вектор значений пикселей изображения.
 * @param sideLength Длина стороны изображения.
 */
void printImage(const std::vector<double> &image, int sideLength);

#endif //AIP_PROJECT_2_BUHS_DATA_READER_H