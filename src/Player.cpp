#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player() {
    position = sf::Vector2f(700.f, 500.f);
    loadTextures();

    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void Player::loadTextures() {
    if (!walkTexture.loadFromFile("assets/player/BODY_male_walk.png")) {
        std::cerr << "Failed to load walk texture!" << std::endl;
    }
}

void Player::handleInput() {
    velocity = {0.f, 0.f};
    moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= speed;
        direction = Left;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += speed;
        direction = Right;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= speed;
        direction = Up;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += speed;
        direction = Down;
        moving = true;
    }
}

void Player::update(float deltaTime) {
    handleInput();

    position += velocity * deltaTime;

    position.x = std::clamp(position.x, 0.f, 1536.f - 64.f);
    position.y = std::clamp(position.y, 0.f, 1024.f - 64.f);

    sprite.setPosition(position);

    updateAnimation();
}

void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % 6;
        animationClock.restart();
    }

    int row = 0;
    switch (direction) {
    case Down:  row = 0; break;
    case Left:  row = 1; break;
    case Right: row = 2; break;
    case Up:    row = 3; break;
    }

    if (moving) {
        sprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
    } else {
        sprite.setTextureRect(sf::IntRect(0, row * 64, 64, 64));
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return position;
}
