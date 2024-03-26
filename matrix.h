//
// Created by zxces on 26.03.2024.
//
#pragma once
#ifndef AIP_PROJECT_2_BUHS_MATRIX_H
#define AIP_PROJECT_2_BUHS_MATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>


class Matrix{
public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    void setElement(size_t row, size_t col, double value);
    void printMatrix() const;
    [[nodiscard]] static double genRandom();
    static std::vector<double> sumVecs(std::vector<double> vec1, std::vector<double> vec2);
    [[nodiscard]] size_t getRows() const;
    [[nodiscard]] size_t getCols() const;
    [[nodiscard]] Matrix t() const;
    [[nodiscard]] double getElement(size_t row, size_t col) const;
    [[nodiscard]] Matrix add(const Matrix& other) const;
    [[nodiscard]] Matrix dot(const Matrix& other) const;
    [[nodiscard]] Matrix eachMul(const Matrix& other) const;
    [[nodiscard]] std::vector<double> dotVector(const std::vector<double>& vec) const;
private:
    std::vector<std::vector<double>> data;
};


#endif //AIP_PROJECT_2_BUHS_MATRIX_H
