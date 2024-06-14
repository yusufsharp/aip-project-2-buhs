//
// Created by zxces on 26.03.2024.
//
/**
 * @file matrix.h
 * @brief Заголовочный файл для класса Matrix.
 */
#pragma once
#ifndef AIP_PROJECT_2_BUHS_MATRIX_H
#define AIP_PROJECT_2_BUHS_MATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

/**
 * @brief Класс для работы с матрицами.
 *
 * Этот класс предоставляет методы для создания, изменения и выполнения различных операций с матрицами.
 */
class Matrix {
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    Matrix();

    /**
     * @brief Конструктор, создающий матрицу заданного размера.
     *
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     */
    Matrix(size_t rows, size_t cols);

    /**
     * @brief Устанавливает значение элемента матрицы.
     *
     * @param row Номер строки.
     * @param col Номер столбца.
     * @param value Значение.
     */
    void setElement(size_t row, size_t col, double value);

    /**
     * @brief Выводит матрицу на экран.
     */
    void printMatrix() const;

    /**
     * @brief Генерирует случайное число в диапазоне от -1.0 до 1.0.
     *
     * @return Случайное число.
     */
    [[nodiscard]] static double genRandom();

    /**
     * @brief Складывает два вектора.
     *
     * @param vec1 Первый вектор.
     * @param vec2 Второй вектор.
     * @return Результат сложения.
     */
    static std::vector<double> sumVecs(std::vector<double> vec1, std::vector<double> vec2);

    /**
     * @brief Вычитает один вектор из другого.
     *
     * @param vec1 Уменьшаемое.
     * @param vec2 Вычитаемое.
     * @return Результат вычитания.
     */
    static std::vector<double> subVecs(std::vector<double> vec1, std::vector<double> vec2);

    /**
     * @brief Поэлементно умножает два вектора.
     *
     * @param vec1 Первый вектор.
     * @param vec2 Второй вектор.
     * @return Результат поэлементного умножения.
     */
    static std::vector<double> eachmulVecs(std::vector<double> vec1, std::vector<double> vec2);

    /**
     * @brief Вычисляет скалярное произведение двух векторов.
     *
     * @param vec1 Первый вектор.
     * @param vec2 Второй вектор.
     * @return Скалярное произведение.
     */
    static double dotprodVecs(std::vector<double> vec1, std::vector<double> vec2);

    /**
     * @brief Выполняет внешнее произведение двух векторов.
     *
     * @param vec1 Первый вектор.
     * @param vec2 Второй вектор.
     * @return Матрица результата внешнего произведения.
     */
    static Matrix ij_mul(std::vector<double> vec1, std::vector<double> vec2);

    /**
     * @brief Возвращает количество строк матрицы.
     *
     * @return Количество строк.
     */
    [[nodiscard]] size_t getRows() const;

    /**
     * @brief Возвращает количество столбцов матрицы.
     *
     * @return Количество столбцов.
     */
    [[nodiscard]] size_t getCols() const;

    /**
     * @brief Возвращает транспонированную матрицу.
     *
     * @return Транспонированная матрица.
     */
    [[nodiscard]] Matrix t() const;

    /**
     * @brief Возвращает значение элемента матрицы.
     *
     * @param row Номер строки.
     * @param col Номер столбца.
     * @return Значение элемента.
     */
    [[nodiscard]] double getElement(size_t row, size_t col) const;

    /**
     * @brief Складывает текущую матрицу с другой матрицей.
     *
     * @param other Другая матрица.
     * @return Результат сложения.
     */
    [[nodiscard]] Matrix add(const Matrix &other) const;

    /**
     * @brief Умножает текущую матрицу на скаляр.
     *
     * @param coeff Скаляр.
     * @return Результат умножения.
     */
    [[nodiscard]] Matrix scalarMul(double coeff) const;

    /**
     * @brief Умножает текущую матрицу на другую матрицу.
     *
     * @param other Другая матрица.
     * @return Результат умножения.
     */
    [[nodiscard]] Matrix dot(const Matrix &other) const;

    /**
     * @brief Поэлементно умножает текущую матрицу на другую матрицу.
     *
     * @param other Другая матрица.
     * @return Результат поэлементного умножения.
     */
    void eachMul(const Matrix &other) const;

    /**
     * @brief Умножает текущую матрицу на вектор.
     *
     * @param vec Вектор.
     * @return Результат умножения.
     */
    [[nodiscard]] std::vector<double> dotVector(const std::vector<double> &vec) const;

    /**
     * @brief Умножает вектор на скаляр.
     *
     * @param vec Вектор.
     * @param coeff Скаляр.
     * @return Результат умножения.
     */
    static std::vector<double> scalarMulVec(const std::vector<double> &vec, double coeff);

    /**
     * @brief Выполняет свёртку матрицы с весами и смещением.
     *
     * @param i1 Начальный индекс строки.
     * @param i2 Конечный индекс строки.
     * @param j1 Начальный индекс столбца.
     * @param j2 Конечный индекс столбца.
     * @param weights Весовая матрица.
     * @param bias Смещение.
     * @return Результат свёртки.
     */
    [[nodiscard]] double convDot(size_t i1, size_t i2, size_t j1, size_t j2, Matrix weights, double bias) const;

    /**
     * @brief Преобразует вектор в квадратную матрицу заданного размера.
     *
     * @param vec Вектор.
     * @param size Размер стороны квадратной матрицы.
     * @return Результат преобразования.
     */
    static Matrix vecReshape(std::vector<double> vec, size_t size);

    /**
     * @brief Добавляет вектор в качестве новой строки матрицы.
     *
     * @param rowVector Вектор для добавления.
     */
    void addVec(const std::vector<double> &rowVector);

    /**
     * @brief Читает матрицу из файла.
     *
     * @param file_path Путь к файлу.
     * @return Прочитанная матрица.
     */
    static Matrix readMatrix(const std::string &file_path);

    /**
     * @brief Читает вектор из файла.
     *
     * @param file_path Путь к файлу.
     * @return Прочитанный вектор.
     */
    static std::vector<double> readVector(const std::string &file_path);

    std::vector<std::vector<double>> data; ///< Данные матрицы.
};

#endif // AIP_PROJECT_2_BUHS_MATRIX_H
