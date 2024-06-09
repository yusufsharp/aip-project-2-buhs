#include "data_reader.h"
#include <algorithm>

void NormalizeData(std::vector<std::vector<double>>& images)
{
    double minPixel = std::numeric_limits<double>::max();
    double maxPixel = std::numeric_limits<double>::min();

    // Находим минимальное и максимальное значения пикселей
    for (const auto& image : images)
    {
        for (double pixel : image) {
            minPixel = std::min(minPixel, pixel);
            maxPixel = std::max(maxPixel, pixel);
        }
    }

    // Вычисляем диапазон значений пикселей
    double range = maxPixel - minPixel;

    // Нормализуем значения пикселей к диапазону от 0 до 1
    for (auto& image : images) {
        for (double& pixel : image){
            pixel = (pixel - minPixel) / range;
        }
    }
}

std::vector<unsigned char> readLabelFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

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

std::vector<std::vector<double>> readImageFile(const std::string &filename) {
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

    std::vector<std::vector<double>> images(numImages, std::vector<double>(numRows * numCols));

    for (int i = 0; i < numImages; ++i) {
        std::vector<unsigned char> tempImage(numRows * numCols);
        file.read(reinterpret_cast<char *>(tempImage.data()), numRows * numCols);
        for (int j = 0; j < numRows * numCols; ++j) {
            images[i][j] = static_cast<double>(tempImage[j]);
        }
    }

    NormalizeData(images);

    file.close();

    return images;
}

void printImage(const std::vector<double>& image, int numRows, int numCols) {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            double pixel = image[i * numCols + j];
            char displayChar = pixel > 0.5 ? '#' : '.';
            std::cout << displayChar;
        }
        std::cout << std::endl;
    }
}