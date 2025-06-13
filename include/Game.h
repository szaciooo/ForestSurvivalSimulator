#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "SkeletonEnemy.h"

class Game {
public:
    Game(sf::RenderWindow& window);
    void handleEvents(bool& backToMenu);
    void update();
    void render();

private:
    sf::RenderWindow& window;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::Font font;

    Player player;
    std::vector<SkeletonEnemy> skeletons;
    int wave = 1;
    sf::Clock clock;
    sf::Clock lastRegenTime;

    enum class GameState { Playing, Won, Lost };
    GameState state = GameState::Playing;

    sf::Text endText;
    sf::Text xText;
    sf::RectangleShape xHitbox;

    void spawnWave();
    void drawUI();
    void drawHealthBar(sf::Vector2f pos, float hp, float maxHp);
};
