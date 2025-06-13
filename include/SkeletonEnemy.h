#pragma once
#include <SFML/Graphics.hpp>

// Prosta klasa reprezentująca szkieleta jako wroga
class SkeletonEnemy {
public:
    SkeletonEnemy(sf::Vector2f pos); // Konstruktor z pozycją startową

    void update(float deltaTime, sf::Vector2f playerPos); // Ruch w stronę gracza
    void render(sf::RenderWindow& window); // Rysowanie przeciwnika

private:
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture walkTexture;

    void updateAnimation(); // Póki co tylko placeholder
};
