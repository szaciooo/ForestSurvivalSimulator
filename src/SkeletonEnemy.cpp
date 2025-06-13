#include "SkeletonEnemy.h"
#include <cmath>

SkeletonEnemy::SkeletonEnemy(sf::Vector2f pos, float atk) : position(pos), attackStrength(atk) {
    walkTexture.loadFromFile("assets/player/BODY_skeleton.png");
    attackTexture.loadFromFile("assets/player/BODY_skeleton_attack.png");
    deathTexture.loadFromFile("assets/player/BODY_skeleton_hurt.png");
    weaponTexture.loadFromFile("assets/player/WEAPON_dagger.png");

    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void SkeletonEnemy::update(float deltaTime, sf::Vector2f playerPos) {
    direction = playerPos - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length;

    float speed = 70.f;
    position += direction * speed * deltaTime;
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

void SkeletonEnemy::takeDamage(float amount) {
    health -= amount;
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
    if (animationClock.getElapsedTime().asSeconds() > 0.2f) {
        currentFrame = (currentFrame + 1) % 4;
        animationClock.restart();
    }

    int row = 0;
    if (std::abs(direction.y) > std::abs(direction.x)) {
        row = (direction.y > 0) ? 2 : 0; // Down : Up
    } else {
        row = (direction.x > 0) ? 3 : 1; // Right : Left
    }

    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
}
