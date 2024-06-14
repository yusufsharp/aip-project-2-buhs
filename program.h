/**
 * @file program.h
 * @brief Заголовочный файл для класса PaintApp, который реализует приложение для рисования и распознавания цифр.
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "TensorsNet.h" // Для использования нейросети
#include "predict.h"

/**
 * @class PaintApp
 * @brief Класс, реализующий приложение для рисования и распознавания цифр.
 */
class PaintApp {
public:
    /**
     * @brief Конструктор класса PaintApp.
     * Инициализирует все необходимые компоненты приложения.
     */
    PaintApp();

    /**
     * @brief Запускает основной цикл приложения.
     */
    void run();

    /**
     * @brief Флаг, проверяющий включение ластика.
     */
    bool isEraser;

    /**
     * @brief Переключает инструмент между карандашом и ластиком.
     */
    void toggleTool();

    /**
     * @brief Захватывает текущее состояние холста в виде изображения.
     * @return sf::Image - изображение текущего состояния холста.
     */
    sf::Image captureCanvas();

    /**
     * @brief Очищает холст, устанавливая все пиксели в черный цвет.
     */
    void clearCanvas();

    /**
     * @brief Изменяет размер изображения до указанных размеров.
     * @param image Исходное изображение.
     * @param width Новый ширина изображения.
     * @param height Новый высота изображения.
     * @return sf::Image - изображение с измененными размерами.
     */
    sf::Image resizeImage(const sf::Image &image, unsigned int width, unsigned int height);

    /**
     * @brief Сохраняет изображение в текстовый файл.
     * @param image Изображение для сохранения.
     * @param filename Имя файла, в который будет сохранено изображение.
     */
    void saveImageAsText(const sf::Image &image, const std::string &filename);

    /**
     * @brief Обрабатывает ввод от мыши.
     * @param position Позиция курсора мыши.
     * @param isPressed Флаг, указывающий, нажата ли кнопка мыши.
     */
    void handleMouseInput(sf::Vector2i position, bool isPressed);

    /**
     * @brief Обрабатывает клики по кнопкам.
     * @param position Позиция курсора мыши.
     */
    void handleButtonClick(sf::Vector2i position);

    /**
     * @brief Флаг, указывающий, находится ли приложение в режиме рисования.
     */
    bool isDrawing;

    /**
     * @brief Обновляет состояние приложения.
     */
    void update();

    /**
     * @brief Окно приложения.
     */
    sf::RenderWindow window;

    /**
     * @brief Обрабатывает события окна.
     */
    void processEvents();

private:
    /**
     * @brief Отрисовывает все элементы приложения.
     */
    void render();

    /**
     * @brief Отрисовывает пользовательский интерфейс.
     */
    void drawUI();

    /**
     * @brief Текстура холста для рисования.
     */
    sf::RenderTexture canvas;

    /**
     * @brief Спрайт для отображения текстуры холста.
     */
    sf::Sprite canvasSprite;

    /**
     * @brief Фон для области с текстом.
     */
    sf::RectangleShape background;

    /**
     * @brief Область для рисования.
     */
    sf::RectangleShape drawingArea;

    /**
     * @brief Кнопка сохранения изображения.
     */
    sf::RectangleShape saveButton;

    /**
     * @brief Кнопка очистки холста.
     */
    sf::RectangleShape clearButton;

    /**
     * @brief Шрифт для текста.
     */
    sf::Font font;

    /**
     * @brief Текст инструкций.
     */
    sf::Text instructions;

    /**
     * @brief Текст на кнопке сохранения.
     */
    sf::Text saveButtonText;

    /**
     * @brief Текст на кнопке очистки.
     */
    sf::Text clearButtonText;

    /**
     * @brief Текст для вывода результата распознавания.
     */
    sf::Text resultText;

    /**
     * @brief Предыдущая позиция курсора мыши.
     */
    sf::Vector2i previousMousePosition;

    /**
     * @brief Текстура для спрайта карандаша.
     */
    sf::Texture pencilTexture;

    /**
     * @brief Спрайт карандаша.
     */
    sf::Sprite pencilSprite;

    /**
     * @brief Ширина линии для рисования.
     */
    float lineWidth;

    /**
     * @brief Нейронная сеть для предсказаний.
     */
    TensorsNet net;
};

#endif // PROGRAM_H