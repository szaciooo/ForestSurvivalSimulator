#include "SkeletonEnemy.h"
#include <cmath>

SkeletonEnemy::SkeletonEnemy(sf::Vector2f pos) : position(pos) {
    texture.loadFromFile("assets/player/BODY_skeleton.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void SkeletonEnemy::update(float deltaTime, sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length;

    float speed = 40.f;
    position += direction * speed * deltaTime;
    sprite.setPosition(position);
}

void SkeletonEnemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect SkeletonEnemy::getBounds() const {
    return sprite.getGlobalBounds();
}
