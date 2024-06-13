#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <string>

class PaintApp {
public:
    PaintApp();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleMouseInput(sf::Vector2i position, bool isPressed);
    void handleButtonClick(sf::Vector2i position);
    void toggleTool();
    void clearCanvas();
    sf::Image captureCanvas();
    sf::Image resizeImage(const sf::Image& image, unsigned int width, unsigned int height);
    void saveImageAsText(const sf::Image& image, const std::string& filename); // Прототип новой функции
    void drawUI();

    sf::RenderWindow window;
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
    bool isDrawing;
    bool isEraser;
    sf::Vector2i previousMousePosition;
    sf::Texture pencilTexture;
    sf::Sprite pencilSprite;
    float lineWidth;
};

#endif // PROGRAM_H
