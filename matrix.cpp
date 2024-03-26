//
// Created by zxces on 26.03.2024.
//

#include "matrix.h"

//необходимо также сделать матрицу, внутри которой функция

Matrix::Matrix() = default;
Matrix::Matrix(size_t rows, size_t cols) : data(rows, std::vector<double>(cols, 0.0)){}

size_t Matrix::getRows() const { return data.size(); }
size_t Matrix::getCols() const { return data.empty() ? 0 : data[0].size(); }


void Matrix::setElement(size_t row, size_t col, double value) {
    if (row < getRows() && col < getCols()) {
        data[row][col] = value;
    }
    else{
        std::cout << "Неверный индекс" << '\n';
    }
}

void Matrix::printMatrix() const {
    for (const std::vector<double> & row : data) {
        for (const double & element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

double Matrix::getElement(size_t row, size_t col) const {
    if (row < getRows() && col < getCols()) {
        return data[row][col];
    }
    return 0.0; // выброс исключения в случае некорректного индекса
}

Matrix Matrix::t() const {
    Matrix transposed(getCols(), getRows()); //да, так и должно быть
    for (size_t i = 0; i < getRows(); ++i) {
        for (size_t j = 0; j < getCols(); ++j) {
            transposed.setElement(j, i, getElement(i, j));
        }
    }
    //НЕ меняет исходную матрицу
    return transposed;
}

Matrix Matrix::add(const Matrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        // ошибка если размеры матриц не совпадают
        return {};
    }

    Matrix result(getRows(), getCols());
    for (size_t i = 0; i < getRows(); ++i) {
        for (size_t j = 0; j < getCols(); ++j) {
            result.setElement(i, j, getElement(i, j) + other.getElement(i, j));
        }
    }
    return result;
}

Matrix Matrix::dot(const Matrix& other) const {
    if (getCols() != other.getRows()) {
        // ошибка если количество столбцов первой матрицы не равно количеству строк второй
        return {};
    }

    Matrix result(getRows(), other.getCols());
    for (size_t i = 0; i < getRows(); ++i) {
        for (size_t j = 0; j < other.getCols(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < getCols(); ++k) {
                sum += getElement(i, k) * other.getElement(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}

Matrix Matrix::eachMul(const Matrix& other) const{
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        // ошибка если размеры не равны
        return {};
    }

    Matrix result(getRows(), other.getCols());
    for (size_t i = 0; i < getCols(); ++i) {
        for (size_t j = 0; j < getRows(); ++j) {
            result.setElement(i, j, getElement(i, j) * other.getElement(i, j));
        }

    }
}

std::vector<double> Matrix::dotVector(const std::vector<double>& vec) const {
    if (vec.size() != getCols()) {
        // ошибка если размер вектора не соответствует количеству столбцов матрицы
        return {};
    }

    std::vector<double> result(getRows(), 0.0);
    for (size_t i = 0; i < getRows(); ++i) {
        for (size_t j = 0; j < getCols(); ++j) {
            result[i] += getElement(i, j) * vec[j];
        }
    }
    return result;
}


double Matrix::genRandom(){ //генерация от 0 до 1
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0, 1.0);
    return dis(gen);
}

std::vector<double> Matrix::sumVecs(std::vector<double> vec1, std::vector<double> vec2){
    std::vector<double> vec3(vec1.size(), 0.0);
    for (size_t i = 0; i < vec1.size(); ++i) {
        vec3[i] = vec1[i] + vec2[i];
    }
    return vec3;
}