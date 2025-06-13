#include "Player.h"
#include <algorithm>

Player::Player() {
    position = {700.f, 500.f};

    if (!texture.loadFromFile("assets/player/BODY_male_walk.png")) {
        // W razie problemu załaduj awaryjny kolor lub sprite
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);
}

void Player::handleInput() {
    velocity = {0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x += speed;
}

void Player::update(float deltaTime) {
    handleInput();
    position += velocity * deltaTime;
    position.x = std::clamp(position.x, 0.f, 1536.f - 64.f);
    position.y = std::clamp(position.y, 0.f, 1024.f - 64.f);
    sprite.setPosition(position);
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
