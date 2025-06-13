#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MenuState {
public:
    MenuState(sf::RenderWindow& window);

    void handleEvents();
    void update();
    void render();

    bool shouldStartGame() const;
    bool shouldShowInstructions() const;
    void resetState();

private:
    sf::RenderWindow& window;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    std::vector<sf::Texture> buttonTexturesIdle;
    std::vector<sf::Texture> buttonTexturesHover;
    std::vector<sf::RectangleShape> buttonShapes;

    int hoveredButton = -1;
    bool startGame = false;
    bool showInstructions = false;

    void updateButtonStates();
};
