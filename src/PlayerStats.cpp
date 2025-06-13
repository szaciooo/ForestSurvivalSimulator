#include "PlayerStats.h"
#include <sstream>

// Konstruktor – ustawienia początkowe
PlayerStats::PlayerStats() {
    maxHealth = 100.f;
    health = maxHealth;
    strength = 10.f;
    speed = 100.f;
    regenRate = 2.f;
    wave = 1;
    showStats = false;

    font.loadFromFile("assets/fonts/PixelFont.ttf");
    statsText.setFont(font);
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::White);

    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setSize(sf::Vector2f(300, 100));
    background.setPosition(1236, 20);

    updateText();
}

// Automatyczne leczenie co klatkę
void PlayerStats::update(float deltaTime) {
    if (health < maxHealth)
        health += regenRate * deltaTime;
    if (health > maxHealth)
        health = maxHealth;

    updateText();
}

// Rysowanie panelu z tekstem
void PlayerStats::render(sf::RenderWindow& window) {
    if (showStats) {
        window.draw(background);
        window.draw(statsText);
    }
}

// Odświeżenie tekstu
void PlayerStats::updateText() {
    std::stringstream ss;
    ss << "Zdrowie: " << static_cast<int>(health)
       << "\nSila: " << static_cast<int>(strength)
       << "\nSzybkosc: " << static_cast<int>(speed);
    statsText.setString(ss.str());
    statsText.setPosition(background.getPosition().x + 10, background.getPosition().y + 10);
}

// Ulepszanie po każdej fali
void PlayerStats::nextWave() {
    wave++;
    strength += 2.f;
    speed += 5.f;
}

// Leczenie i obrażenia
void PlayerStats::heal(float amount) {
    health += amount;
    if (health > maxHealth)
        health = maxHealth;
}

void PlayerStats::takeDamage(float amount) {
    health -= amount;
    if (health < 0.f)
        health = 0.f;
}

// GETTERY

float PlayerStats::getAttackStrength() const {
    return strength;
}

float PlayerStats::getSpeed() const {
    return speed;
}

bool PlayerStats::isDead() const {
    return health <= 0.f;
}

bool PlayerStats::isVisible() const {
    return showStats;
}

// Przełączanie widoczności statystyk
void PlayerStats::toggle() {
    showStats = !showStats;
}
