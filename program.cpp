#include "program.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <fstream>
#include <iomanip>

// Конструктор класса PaintApp
PaintApp::PaintApp()
        : window(sf::VideoMode(768, 512), "Paint"),
          isDrawing(false), isEraser(false), lineWidth(30.0f) {
    window.setFramerateLimit(60);

    // Определяем размеры холста для рисования
    unsigned int drawingAreaWidth = 512;
    unsigned int drawingAreaHeight = 512;

    // Создаем холст для рисования
    canvas.create(drawingAreaWidth, drawingAreaHeight);
    canvas.clear(sf::Color::Black);
    canvasSprite.setTexture(canvas.getTexture());
    canvasSprite.setPosition(0, 0);

    // Создаем белый фон для области с текстом
    background.setSize(sf::Vector2f(768, 512));
    background.setFillColor(sf::Color::White);

    // Определяем размеры области для рисования
    drawingArea.setSize(sf::Vector2f(drawingAreaWidth, drawingAreaHeight));
    drawingArea.setFillColor(sf::Color::Black);
    drawingArea.setPosition(0, 0);

    // Загрузка шрифта для текста
    if (!font.loadFromFile("../DejaVu.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
    } else {
        std::cout << "Шрифт загружен успешно" << std::endl;
    }

    // Установка текста инструкций
    instructions.setFont(font);
    instructions.setString("Hello! Draw any number from 0 to 9\n"
                           " on a black canvas and our program\n"
                           " will guess what this number is\n"
                           " (what miracles!?!?!?!).");
    instructions.setCharacterSize(14);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition(drawingAreaWidth + 10, 20);

    // Установка текста кнопки сохранения
    saveButton.setSize(sf::Vector2f(100, 40));
    saveButton.setFillColor(sf::Color::Transparent);
    saveButton.setOutlineColor(sf::Color::Black);
    saveButton.setOutlineThickness(2);
    saveButton.setPosition(drawingAreaWidth + 10, 120);

    saveButtonText.setFont(font);
    saveButtonText.setString("Save");
    saveButtonText.setCharacterSize(14);
    saveButtonText.setFillColor(sf::Color::Black);
    saveButtonText.setPosition(drawingAreaWidth + 20, 130);

    // Установка текста кнопки очистки
    clearButton.setSize(sf::Vector2f(100, 40));
    clearButton.setFillColor(sf::Color::Transparent);
    clearButton.setOutlineColor(sf::Color::Black);
    clearButton.setOutlineThickness(2);
    clearButton.setPosition(drawingAreaWidth + 120, 120);

    clearButtonText.setFont(font);
    clearButtonText.setString("Clear");
    clearButtonText.setCharacterSize(14);
    clearButtonText.setFillColor(sf::Color::Black);
    clearButtonText.setPosition(drawingAreaWidth + 130, 130);

    // Установка текста для вывода результата
    resultText.setFont(font);
    resultText.setString("Result: ");
    resultText.setCharacterSize(14);
    resultText.setFillColor(sf::Color::Black);
    resultText.setPosition(drawingAreaWidth + 10, 180);

    // Загрузка текстуры и установка спрайта карандаша
    if (!pencilTexture.loadFromFile("pencil.png")) {
        std::cerr << "Ошибка загрузки текстуры карандаша" << std::endl;
    } else {
        std::cout << "Текстура карандаша загружена успешно" << std::endl;
    }
    pencilSprite.setTexture(pencilTexture);
    pencilSprite.setOrigin(pencilTexture.getSize().x / 2, pencilTexture.getSize().y / 2);
}

// Основной метод для запуска приложения
void PaintApp::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

// Обработка событий
void PaintApp::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::T) {
                toggleTool();
            }
            if (event.key.code == sf::Keyboard::S) {
                sf::Image image = captureCanvas();
                image.saveToFile("drawing_original.png"); // Сохранение оригинального изображения
                sf::Image resizedImage = resizeImage(image, 28, 28);
                resizedImage.saveToFile("drawing_28x28.png");
                saveImageAsText(resizedImage, "drawing_28x28.txt");
                resultText.setString("Result: ...");
            }
            if (event.key.code == sf::Keyboard::C) {
                clearCanvas();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
            bool isPressed = (event.type == sf::Event::MouseButtonPressed);
            handleMouseInput(sf::Mouse::getPosition(window), isPressed);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            handleButtonClick(sf::Mouse::getPosition(window));
        }
    }
}

// Обновление логики программы
void PaintApp::update() {
    if (isDrawing) {
        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
        // Ограничиваем рисование только областью холста
        if (drawingArea.getGlobalBounds().contains(static_cast<sf::Vector2f>(currentMousePosition))) {
            sf::RectangleShape line;
            line.setSize(sf::Vector2f(lineWidth, lineWidth));
            line.setFillColor(isEraser ? sf::Color::Black : sf::Color::White);
            line.setPosition(static_cast<sf::Vector2f>(currentMousePosition));
            canvas.draw(line);

            previousMousePosition = currentMousePosition;
        }
    }
    pencilSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

// Отрисовка графики
void PaintApp::render() {
    window.clear();
    window.draw(background);  // Отрисовка белого фона
    window.draw(drawingArea); // Отрисовка области для рисования
    canvas.display();
    window.draw(canvasSprite);
    drawUI();
    window.draw(pencilSprite);
    window.display();
}

// Обработка ввода мыши
void PaintApp::handleMouseInput(sf::Vector2i position, bool isPressed) {
    if (isPressed) {
        isDrawing = true;
        previousMousePosition = position;
    } else {
        isDrawing = false;
    }
}

// Обработка нажатия кнопок
void PaintApp::handleButtonClick(sf::Vector2i position) {
    if (saveButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(position))) {
        sf::Image image = captureCanvas();
        image.saveToFile("../drawing_original.png"); // Сохранение оригинального изображения
        sf::Image resizedImage = resizeImage(image, 28, 28);
        resizedImage.saveToFile("../drawing_28x28.png");
        saveImageAsText(resizedImage, "../drawing.txt");
        resultText.setString("Result: ...");
    }
    if (clearButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(position))) {
        clearCanvas();
    }
}

// Переключение между карандашом и ластиком
void PaintApp::toggleTool() {
    isEraser = !isEraser;
    pencilSprite.setColor(isEraser ? sf::Color::Red : sf::Color::White);
}

// Очистка холста
void PaintApp::clearCanvas() {
    canvas.clear(sf::Color::Black);
}

// Захват изображения с холста
sf::Image PaintApp::captureCanvas() {
    canvas.display();
    return canvas.getTexture().copyToImage();
}

// Изменение размера изображения
sf::Image PaintApp::resizeImage(const sf::Image& image, unsigned int width, unsigned int height) {
    sf::Image resizedImage;
    resizedImage.create(width, height, sf::Color::Black);

    sf::Vector2u imageSize = image.getSize();
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            unsigned int srcX = x * imageSize.x / width;
            unsigned int srcY = y * imageSize.y / height;
            resizedImage.setPixel(x, y, image.getPixel(srcX, srcY));
        }
    }

    return resizedImage;
}

// Сохранение изображения в текстовом формате
void PaintApp::saveImageAsText(const sf::Image& image, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        sf::Vector2u size = image.getSize();
        for (unsigned int y = 0; y < size.y; ++y) {
            for (unsigned int x = 0; x < size.x; ++x) {
                sf::Color color = image.getPixel(x, y);
                double value = (color.r + color.g + color.b) / (3.0 * 255.0); // Преобразование в градации серого
                file << std::fixed << std::setprecision(6) << value << " ";
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
    }
}

// Отрисовка пользовательского интерфейса
void PaintApp::drawUI() {
    window.draw(instructions);
    window.draw(saveButton);
    window.draw(saveButtonText);
    window.draw(clearButton);
    window.draw(clearButtonText);
    window.draw(resultText);
}

// Точка входа в программу
int main() {
    PaintApp app;
    app.run();
    return 0;
}