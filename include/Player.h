#pragma once
#include <SFML/Graphics.hpp>

// Klasa reprezentująca gracza sterowanego przez użytkownika
class Player {
public:
    Player();

    void update(float deltaTime);         // Aktualizacja pozycji i animacji
    void render(sf::RenderWindow& window); // Renderowanie postaci

private:
    void handleInput();        // Obsługa klawiatury
    void loadTextures();       // Ładowanie grafik
    void updateAnimation();    // Animacja (jeszcze uproszczona)

    sf::Texture walkTexture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 100.f;

    enum Direction { Down, Left, Right, Up } direction = Down;
    int currentFrame = 0;
    float frameDuration = 0.15f;
    sf::Clock animationClock;

    bool moving = false;
};
