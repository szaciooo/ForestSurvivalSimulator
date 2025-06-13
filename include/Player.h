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
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;

    float health = 100.f;
    float attackStrength = 10.f;

    bool attacking = false;
    float speed = 100.f;
};
