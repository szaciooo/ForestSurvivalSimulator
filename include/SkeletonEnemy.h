#pragma once
#include <SFML/Graphics.hpp>

class SkeletonEnemy {
public:
    SkeletonEnemy(sf::Vector2f pos);

    void update(float deltaTime, sf::Vector2f playerPos);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

private:
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
};
