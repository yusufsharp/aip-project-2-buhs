//
// Created by pc on 27.03.2024.
//
#include "data_reader.h"

void NormalizeData(std::vector<std::vector<unsigned char>>& images)
{
    unsigned char minPixel = std::numeric_limits<unsigned char>::max();
    unsigned char maxPixel = std::numeric_limits<unsigned char>::min();

    // Находим минимальное и максимальное значения пикселей
    for (const auto& image : images)
    {
        for (unsigned char pixel : image) {
            minPixel = std::min(minPixel, pixel);
            maxPixel = std::max(maxPixel, pixel);
        }
    }

    // Вычисляем диапазон значений пикселей
    double range = maxPixel - minPixel;

    // Нормализуем значения пикселей к диапазону от 0 до 1
    for (auto& image : images) {
        for (unsigned char& pixel : image){
            pixel = static_cast<unsigned char>((pixel - minPixel) / range * 255); // Нормализация к диапазону от 0 до 255
        }
    }
}

std::vector<unsigned char> readLabelFile(const std::string &filename) {
    std::ifstream file(filename,
                       std::ios::binary);

//  std::ios::binary указывает, что файл открывается в двоичном режиме, что означает,
//  что данные будут считываться
//  как бинарные данные, а не текстовые.

    if (!file) {
        std::cerr << "Failed to open the file.\n" << std::endl;
        return {};
    }
    char magicNumber[4];
    char numLabelsBytes[4];


    file.read(magicNumber, 4);
    file.read(numLabelsBytes, 4);

    int numLabels = (static_cast<unsigned char>(numLabelsBytes[0]) << 24) |
                    (static_cast<unsigned char>(numLabelsBytes[1]) << 16) |
                    (static_cast<unsigned char>(numLabelsBytes[2]) << 8) |
                    static_cast<unsigned char>(numLabelsBytes[3]);
    std::vector<unsigned char> labels(numLabels);
    file.read(reinterpret_cast<char *>(labels.data()), numLabels);

    file.close();

    return labels;

}

std::vector<std::vector<unsigned char>> readImageFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open the file. \n" << std::endl;
        return {};
    }
    char magicNumber[4];
    char numImagesBytes[4];
    char numRowsBytes[4];
    char numColsBytes[4];

    file.read(magicNumber, 4);
    file.read(numImagesBytes, 4);
    file.read(numRowsBytes, 4);
    file.read(numColsBytes, 4);

    int numImages = (static_cast<unsigned char>(numImagesBytes[0]) << 24) |
                    (static_cast<unsigned char>(numImagesBytes[1]) << 16) |
                    (static_cast<unsigned char>(numImagesBytes[2]) << 8) |
                    static_cast<unsigned char>(numImagesBytes[3]);
    int numRows = (static_cast<unsigned char>(numRowsBytes[0]) << 24) |
                  (static_cast<unsigned char>(numRowsBytes[1]) << 16) |
                  (static_cast<unsigned char>(numRowsBytes[2]) << 8) |
                  static_cast<unsigned char>(numRowsBytes[3]);
    int numCols = (static_cast<unsigned char>(numColsBytes[0]) << 24) |
                  (static_cast<unsigned char>(numColsBytes[1]) << 16) |
                  (static_cast<unsigned char>(numColsBytes[2]) << 8) |
                  static_cast<unsigned char>(numColsBytes[3]);

    std::vector<std::vector<unsigned char>> images(numImages, std::vector<unsigned char>(numRows * numCols));

    NormalizeData(images);

    for (int i = 0; i < numImages; ++i) {
        file.read(reinterpret_cast<char *>(images[i].data()), numRows * numCols);
    }

    file.close();

    return images;
}

void printImage(const std::vector<unsigned char> &image, int sideLength) {
    int imageSize = image.size();
    int numRows = imageSize / sideLength;
    int numCols = sideLength;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            // Выводим значение пикселя в консоль (можно в виде числа или символа)
            std::cout << static_cast<int>(image[i * numCols + j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

