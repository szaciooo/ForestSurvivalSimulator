#pragma once
#include <SFML/Graphics.hpp>

class SkeletonEnemy {
public:
    SkeletonEnemy(sf::Vector2f pos);

    void update(float deltaTime, sf::Vector2f playerPos);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    float getHealth() const;

    void takeDamage(float amount);

private:
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;

    float health = 100.f;
};
