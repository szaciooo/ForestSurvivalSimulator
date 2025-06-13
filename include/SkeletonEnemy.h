#pragma once
#include <SFML/Graphics.hpp>

class SkeletonEnemy {
public:
    SkeletonEnemy(sf::Vector2f pos, float attackStrength);

    void update(float deltaTime, sf::Vector2f playerPos);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    float getHealth() const;
    void takeDamage(float amount);

    bool canAttack() const;
    float getAttackStrength() const;
    void resetAttackCooldown();

private:
    sf::Vector2f position;
    sf::Sprite sprite;

    sf::Texture walkTexture;
    float health = 100.f;
    float attackStrength = 5.f;
    sf::Clock attackClock;

    void updateAnimation();
};
