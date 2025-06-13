#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "SkeletonEnemy.h"

class Game {
public:
    Game(sf::RenderWindow& window);

    void handleEvents();
    void update();
    void render();

private:
    sf::RenderWindow& window;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    sf::Clock clock;
    sf::Font font;

    Player player;
    std::vector<SkeletonEnemy> skeletons; // Dodano: lista szkieletów

    void spawnWave(); // Dodano: tworzenie fali wrogów
};
