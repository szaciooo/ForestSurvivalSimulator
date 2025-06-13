#pragma once
#include <SFML/Graphics.hpp>

// Klasa zarządzająca statystykami gracza i ich wyświetlaniem
class PlayerStats {
public:
    PlayerStats();

    void update(float deltaTime);          // Regen HP
    void render(sf::RenderWindow& window); // Rysowanie panelu statystyk
    void nextWave();                       // Ulepszanie statystyk po fali
    void heal(float amount);               // Leczenie
    void takeDamage(float amount);         // Obrażenia
    void toggle();                         // Przełączanie widoczności

    float getAttackStrength() const;       // Getter siły
    float getSpeed() const;                // Getter prędkości
    bool isDead() const;                   // Czy gracz martwy?
    bool isVisible() const;                // Czy panel widoczny?

private:
    float health;
    float maxHealth;
    float strength;
    float speed;
    int wave;

    float regenRate;

    sf::Font font;
    sf::Text statsText;
    sf::RectangleShape background;
    bool showStats;

    void updateText(); // Odświeżenie tekstu
};
