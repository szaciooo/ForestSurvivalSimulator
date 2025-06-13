#include "Player.h"
#include <iostream>
#include <algorithm>

// Konstruktor – inicjalizacja pozycji, ładowanie tekstur, ustawienie sprite'ów
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

// Wczytywanie wszystkich potrzebnych grafik
void Player::loadTextures() {
    if (!walkTexture.loadFromFile("assets/player/BODY_male_walk.png")) {
        std::cerr << "Failed to load walk texture!" << std::endl;
    }
    if (!hurtTexture.loadFromFile("assets/player/BODY_male_hurt.png")) {
        std::cerr << "Failed to load hurt texture!" << std::endl;
    }
    if (!bodyWeaponTexture.loadFromFile("assets/player/BODY_human.png")) {
        std::cerr << "Failed to load body weapon texture!" << std::endl;
    }
    if (!weaponTexture.loadFromFile("assets/player/WEAPON_dagger.png")) {
        std::cerr << "Failed to load weapon texture!" << std::endl;
    }
}

// Obsługa klawiszy: WASD + spacja (atak)
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
        direction = Up;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= speed;
        direction = Down;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += speed;
        direction = Right;
        moving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        attacking = true;
    }
}

// Główna aktualizacja – logika ruchu, kolizji i animacji
void Player::update(float deltaTime) {
    handleInput();

    position += velocity * deltaTime;

    // Ograniczenie poruszania się do rozmiaru okna gry
    position.x = std::clamp(position.x, 0.f, 1536.f - 64.f);
    position.y = std::clamp(position.y, 0.f, 1024.f - 64.f);

    sprite.setPosition(position);
    weaponSprite.setPosition(position);

    updateAnimation();
}

// Zmiana animacji na podstawie stanu (ruch / atak / spoczynek)
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

// Rysowanie gracza (i broni jeśli atakuje)
void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
    if (attacking)
        window.draw(weaponSprite);
}

// Zasięg kolizji gracza
sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

// Zasięg ataku – większy od zwykłego kolizyjnego
sf::FloatRect Player::getAttackBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.width += 10;
    bounds.height += 10;
    bounds.left -= 5;
    bounds.top -= 5;
    return bounds;
}

// GETTERY – używane przez inne klasy

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

// Zadawanie obrażeń
void Player::takeDamage(float dmg) {
    currentHealth -= dmg;
    if (currentHealth < 0.f)
        currentHealth = 0.f;
}

// Leczenie
void Player::heal(float h) {
    currentHealth = std::min(currentHealth + h, 100.f);
}
