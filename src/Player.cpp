#include "Player.h"
#include <algorithm>

Player::Player() {
    position = sf::Vector2f(700.f, 500.f);
    loadTextures();

    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(position);

    weaponSprite.setTexture(weaponTexture);
    weaponSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    weaponSprite.setPosition(position);
}

void Player::loadTextures() {
    walkTexture.loadFromFile("assets/player/BODY_male_walk.png");
    bodyWeaponTexture.loadFromFile("assets/player/BODY_human.png");
    weaponTexture.loadFromFile("assets/player/WEAPON_dagger.png");
}

void Player::handleInput() {
    velocity = {0.f, 0.f};
    moving = false;
    attacking = false;

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        attacking = true;
    }
}

void Player::update(float deltaTime) {
    handleInput();

    position += velocity * deltaTime;
    position.x = std::clamp(position.x, 0.f, 1536.f - 64.f);
    position.y = std::clamp(position.y, 0.f, 1024.f - 64.f);

    sprite.setPosition(position);
    weaponSprite.setPosition(position);
    updateAnimation();
}

void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % 6;
        animationClock.restart();
    }

    int row = static_cast<int>(direction);
    if (attacking) {
        sprite.setTexture(bodyWeaponTexture);
        sprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
        weaponSprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
    } else if (moving) {
        sprite.setTexture(walkTexture);
        sprite.setTextureRect(sf::IntRect(currentFrame * 64, row * 64, 64, 64));
    } else {
        sprite.setTexture(walkTexture);
        sprite.setTextureRect(sf::IntRect(0, row * 64, 64, 64));
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
    if (attacking)
        window.draw(weaponSprite);
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
    return currentHealth;
}

float Player::getAttackStrength() const {
    return attackPower;
}

void Player::takeDamage(float dmg) {
    currentHealth -= dmg;
    currentHealth = std::max(currentHealth, 0.f);
}

void Player::heal(float amount) {
    currentHealth = std::min(currentHealth + amount, 100.f);
}
