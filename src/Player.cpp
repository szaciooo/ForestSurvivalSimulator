#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Player::Player() {
    position = sf::Vector2f(700.f, 500.f);

    texture.loadFromFile("assets/player/BODY_male_walk.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void Player::update(float deltaTime) {
    sf::Vector2f velocity(0.f, 0.f);
    attacking = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        attacking = true;
    }

    position += velocity * deltaTime;

    // Zapobiegamy wyjściu poza ekran
    position.x = std::clamp(position.x, 0.f, 1536.f - 64.f);
    position.y = std::clamp(position.y, 0.f, 1024.f - 64.f);

    sprite.setPosition(position);
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::FloatRect Player::getAttackBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.width += 10;
    bounds.height += 10;
    bounds.left -= 5;
    bounds.top -= 5;
    return bounds;
}

sf::Vector2f Player::getPosition() const {
    return position;
}

bool Player::isAttacking() const {
    return attacking;
}

float Player::getHealth() const {
    return health;
}

float Player::getAttackStrength() const {
    return attackStrength;
}

void Player::takeDamage(float dmg) {
    health -= dmg;
    if (health < 0.f) health = 0.f;
}

void Player::heal(float amount) {
    health = std::min(health + amount, 100.f);
}
