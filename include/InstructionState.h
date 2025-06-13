#pragma once
#include <SFML/Graphics.hpp>

class InstructionState {
public:
    InstructionState(sf::RenderWindow& window);
    void handleEvents(bool& backToMenu);
    void render();

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font font;
    sf::Text instructions;
    sf::Text xText;

    sf::RectangleShape xHitbox;
    bool hovered = false;

    void updateHover();
};
