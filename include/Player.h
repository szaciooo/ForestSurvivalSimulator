#pragma once
#include <SFML/Graphics.hpp>

// Klasa reprezentująca gracza – postać sterowana przez użytkownika
class Player {
public:
    Player(); // Konstruktor

    void update(float deltaTime);           // Aktualizacja logiki ruchu i animacji
    void render(sf::RenderWindow& window);  // Rysowanie gracza i broni

    // Metody pomocnicze do kolizji
    sf::FloatRect getBounds() const;         // Zasięg kolizji gracza
    sf::FloatRect getAttackBounds() const;   // Zasięg ataku (trochę większy)

    sf::Vector2f getPosition() const;        // Pozycja gracza
    bool isAttacking() const;                // Czy aktualnie atakuje
    float getHealth() const;                 // Aktualne HP
    float getAttackStrength() const;         // Siła ataku

    void takeDamage(float dmg);              // Odejmowanie życia
    void heal(float amount);                 // Leczenie

private:
    void handleInput();       // Obsługa klawiatury
    void loadTextures();      // Wczytywanie grafik
    void updateAnimation();   // Zmiana animacji w zależności od stanu

    // Tekstury: ruch, obrażenia, atak, broń
    sf::Texture walkTexture;
    sf::Texture hurtTexture;
    sf::Texture bodyWeaponTexture;
    sf::Texture weaponTexture;

    // Sprite gracza i broni
    sf::Sprite sprite;
    sf::Sprite weaponSprite;

    // Pozycja i ruch
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 100.f;

    // Kierunki animacji
    enum Direction { Down, Left, Right, Up } direction = Down;
    int currentFrame = 0;
    float frameDuration = 0.15f;
    sf::Clock animationClock;

    bool moving = false;
    bool attacking = false;

    float currentHealth = 100.f;
    float attackPower = 10.f;
};
