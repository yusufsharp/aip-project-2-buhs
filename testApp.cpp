#include "program.h"
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

// Тесты для метода toggleTool
TEST(PaintAppTest, ToggleTool) {
    PaintApp app;
    bool initialToolState = app.isEraser;
    app.toggleTool();
    EXPECT_NE(initialToolState, app.isEraser);
    app.toggleTool();
    EXPECT_EQ(initialToolState, app.isEraser);
}

// Тесты для метода clearCanvas
TEST(PaintAppTest, ClearCanvas) {
    PaintApp app;
    sf::Image beforeClear = app.captureCanvas();
    app.clearCanvas();
    sf::Image afterClear = app.captureCanvas();

    for (unsigned int y = 0; y < beforeClear.getSize().y; ++y) {
        for (unsigned int x = 0; x < beforeClear.getSize().x; ++x) {
            EXPECT_EQ(afterClear.getPixel(x, y), sf::Color::Black);
        }
    }
}

// Тесты для метода resizeImage
TEST(PaintAppTest, ResizeImage) {
    PaintApp app;
    sf::Image image;
    image.create(56, 56, sf::Color::White);

    sf::Image resizedImage = app.resizeImage(image, 28, 28);

    EXPECT_EQ(resizedImage.getSize().x, 28);
    EXPECT_EQ(resizedImage.getSize().y, 28);

    for (unsigned int y = 0; y < resizedImage.getSize().y; ++y) {
        for (unsigned int x = 0; x < resizedImage.getSize().x; ++x) {
            EXPECT_EQ(resizedImage.getPixel(x, y), sf::Color::White);
        }
    }
}

// Тесты для метода saveImageAsText
TEST(PaintAppTest, SaveImageAsText) {
    PaintApp app;
    sf::Image image;
    image.create(28, 28, sf::Color::White);

    app.saveImageAsText(image, "test_drawing.txt");

    std::ifstream file("test_drawing.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double value;
        while (iss >> value) {
            EXPECT_EQ(value, 1.0);
        }
    }

    file.close();
    std::remove("test_drawing.txt");
}

// Тесты для метода captureCanvas
TEST(PaintAppTest, CaptureCanvas) {
    PaintApp app;
    sf::Image capturedImage = app.captureCanvas();

    EXPECT_EQ(capturedImage.getSize().x, 512);
    EXPECT_EQ(capturedImage.getSize().y, 512);

    for (unsigned int y = 0; y < capturedImage.getSize().y; ++y) {
        for (unsigned int x = 0; x < capturedImage.getSize().x; ++x) {
            EXPECT_EQ(capturedImage.getPixel(x, y), sf::Color::Black);
        }
    }
}

// Тесты для метода handleMouseInput
TEST(PaintAppTest, HandleMouseInput) {
    PaintApp app;
    sf::Vector2i position(100, 100);
    app.handleMouseInput(position, true);
    EXPECT_TRUE(app.isDrawing);
    app.handleMouseInput(position, false);
    EXPECT_FALSE(app.isDrawing);
}

// Тесты для метода handleButtonClick - нажатие кнопки сохранения
TEST(PaintAppTest, HandleSaveButtonClick) {
    PaintApp app;
    sf::Vector2i saveButtonPos(522, 130); // Позиция кнопки Save
    app.handleButtonClick(saveButtonPos);

    std::ifstream file("drawing.txt");
    ASSERT_TRUE(file.is_open());
    file.close();
    std::remove("drawing.txt");
}

// Тесты для метода handleButtonClick - нажатие кнопки очистки
TEST(PaintAppTest, HandleClearButtonClick) {
    PaintApp app;
    sf::Vector2i clearButtonPos(632, 130); // Позиция кнопки Clear
    app.handleButtonClick(clearButtonPos);

    sf::Image image = app.captureCanvas();
    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            EXPECT_EQ(image.getPixel(x, y), sf::Color::Black);
        }
    }
}

// Тесты для метода update
TEST(PaintAppTest, Update) {
    PaintApp app;
    app.isDrawing = true;
    sf::Vector2i currentMousePosition(100, 100);
    sf::Mouse::setPosition(currentMousePosition, app.window);
    app.update();

    sf::Image image = app.captureCanvas();
    EXPECT_EQ(image.getPixel(100, 100), sf::Color::White);
}

