#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const; // <- dodane

private:
    void handleInput();
    void loadTextures();
    void updateAnimation();

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
