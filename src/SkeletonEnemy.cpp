#include "SkeletonEnemy.h"
#include <cmath>

SkeletonEnemy::SkeletonEnemy(sf::Vector2f pos) : position(pos) {
    walkTexture.loadFromFile("assets/player/BODY_skeleton.png");
    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void SkeletonEnemy::update(float deltaTime, sf::Vector2f playerPos) {
    // Oblicz kierunek do gracza
    sf::Vector2f dir = playerPos - position;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        dir /= len;

    float speed = 40.f;
    position += dir * speed * deltaTime;

    sprite.setPosition(position);
    updateAnimation();
}

void SkeletonEnemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void SkeletonEnemy::updateAnimation() {
    // Prosty placeholder, bez klatek jeszcze
    // Można rozbudować później (milestone)
}
