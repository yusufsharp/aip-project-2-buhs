/**
 * @file main.cpp
 * @brief Основной файл программы для обучения нейронной сети и запуска приложения для рисования.
 */

#include "data_reader.h"
#include "TensorsNet.h"
#include "TrainingLoop.h"
#include <iostream>
#include "predict.h"
#include "program.h"

/**
 * @brief Основная функция программы.
 * @return int Возвращает 0 при успешном завершении программы.
 */
int main() {
    std::cout << "Let's go, motherfacker!\n";

    // Создание и запуск приложения для рисования
    PaintApp app;
    app.run();
    return 0;
}