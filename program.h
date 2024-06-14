#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "TensorsNet.h" // Для использования нейросети
#include "predict.h"

class PaintApp {
public:
    PaintApp();
    void run();

    bool isEraser;

    void toggleTool();

    sf::Image captureCanvas();

    void clearCanvas();

    sf::Image resizeImage(const sf::Image& image, unsigned int width, unsigned int height);

    void saveImageAsText(const sf::Image& image, const std::string& filename);

    void handleMouseInput(sf::Vector2i position, bool isPressed);

    void handleButtonClick(sf::Vector2i position);

    bool isDrawing;

    void update();

    sf::RenderWindow window;

    void processEvents();

private:

    void render();

    void drawUI();

    sf::RenderTexture canvas;
    sf::Sprite canvasSprite;
    sf::RectangleShape background;
    sf::RectangleShape drawingArea;
    sf::RectangleShape saveButton;
    sf::RectangleShape clearButton;
    sf::Font font;
    sf::Text instructions;
    sf::Text saveButtonText;
    sf::Text clearButtonText;
    sf::Text resultText;
    sf::Vector2i previousMousePosition;
    sf::Texture pencilTexture;
    sf::Sprite pencilSprite;
    float lineWidth;


    TensorsNet net; // Нейронная сеть для предсказаний
};

#endif // PROGRAM_H