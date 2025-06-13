#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

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

    Player player;
};
