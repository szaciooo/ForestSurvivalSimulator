#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 100.f;

    void handleInput();
};
