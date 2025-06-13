#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::FloatRect getAttackBounds() const;
    sf::Vector2f getPosition() const;

    bool isAttacking() const;
    float getHealth() const;
    float getAttackStrength() const;

    void takeDamage(float dmg);
    void heal(float amount);

private:
    void handleInput();
    void loadTextures();
    void updateAnimation();

    sf::Texture walkTexture, bodyWeaponTexture, weaponTexture;
    sf::Sprite sprite, weaponSprite;

    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed = 100.f;

    enum Direction { Down, Left, Right, Up } direction = Down;
    int currentFrame = 0;
    float frameDuration = 0.15f;
    sf::Clock animationClock;

    bool moving = false;
    bool attacking = false;

    float currentHealth = 100.f;
    float attackPower = 10.f;
};
