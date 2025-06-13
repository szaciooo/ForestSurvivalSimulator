#include "SkeletonEnemy.h"
#include <cmath>

SkeletonEnemy::SkeletonEnemy(sf::Vector2f pos) : position(pos) {
    texture.loadFromFile("assets/player/BODY_skeleton.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void SkeletonEnemy::update(float deltaTime, sf::Vector2f playerPos) {
    sf::Vector2f dir = playerPos - position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0) dir /= len;

    float speed = 40.f;
    position += dir * speed * deltaTime;
    sprite.setPosition(position);
}

void SkeletonEnemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect SkeletonEnemy::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f SkeletonEnemy::getPosition() const {
    return position;
}

float SkeletonEnemy::getHealth() const {
    return health;
}

void SkeletonEnemy::takeDamage(float amount) {
    health -= amount;
}
