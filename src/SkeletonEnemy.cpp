#include "SkeletonEnemy.h"
#include <cmath>

SkeletonEnemy::SkeletonEnemy(sf::Vector2f pos, float atk) : position(pos), attackStrength(atk) {
    walkTexture.loadFromFile("assets/player/BODY_skeleton.png");

    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void SkeletonEnemy::update(float deltaTime, sf::Vector2f playerPos) {
    sf::Vector2f dir = playerPos - position;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;

    float speed = 40.f;
    position += dir * speed * deltaTime;
    sprite.setPosition(position);

    updateAnimation();
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

void SkeletonEnemy::takeDamage(float dmg) {
    health -= dmg;
}

bool SkeletonEnemy::canAttack() const {
    return attackClock.getElapsedTime().asSeconds() > 1.5f;
}

float SkeletonEnemy::getAttackStrength() const {
    return attackStrength;
}

void SkeletonEnemy::resetAttackCooldown() {
    attackClock.restart();
}

void SkeletonEnemy::updateAnimation() {
    // Można rozwinąć animację
}
