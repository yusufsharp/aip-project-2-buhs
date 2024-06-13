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
    static std::vector<double> subVecs(std::vector<double> vec1, std::vector<double> vec2);
    static std::vector<double> eachmulVecs(std::vector<double> vec1, std::vector<double> vec2);
    static double dotprodVecs(std::vector<double> vec1, std::vector<double> vec2);
    static Matrix ij_mul(std::vector<double> vec1, std::vector<double> vec2);
    [[nodiscard]] size_t getRows() const;
    [[nodiscard]] size_t getCols() const;
    [[nodiscard]] Matrix t() const;
    [[nodiscard]] double getElement(size_t row, size_t col) const;
    [[nodiscard]] Matrix add(const Matrix& other) const;
    [[nodiscard]] Matrix scalarMul(double coeff) const;
    [[nodiscard]] Matrix dot(const Matrix& other) const;
    [[nodiscard]] Matrix eachMul(const Matrix& other) const;
    [[nodiscard]] std::vector<double> dotVector(const std::vector<double>& vec) const;
    static std::vector<double> scalarMulVec(const std::vector<double> & vec, double coeff);
    [[nodiscard]] double convDot(size_t i1, size_t i2, size_t j1, size_t j2, Matrix weights, double bias) const;
    static Matrix vecReshape(std::vector<double> vec, size_t size);
    std::vector<std::vector<double>> data;
    void addVec(const std::vector<double> &rowVector);

    static Matrix readMatrix(const std::string &file_path);
    static std::vector<double> readVector(const std::string &file_path);
};


#endif //AIP_PROJECT_2_BUHS_MATRIX_H