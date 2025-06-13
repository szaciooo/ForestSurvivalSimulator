#include "Game.h"
#include <sstream>
#include <iostream>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    mapTexture.loadFromFile("assets/maps/forest_map.png");
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        static_cast<float>(window.getSize().x) / mapTexture.getSize().x,
        static_cast<float>(window.getSize().y) / mapTexture.getSize().y
        );

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    spawnWave();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    player.update(0.016f);  // przykładowa delta time

    for (auto& skeleton : skeletons) {
        skeleton.update(0.016f, player.getPosition());
    }
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& skeleton : skeletons)
        skeleton.render(window);

    drawUI();
}

void Game::spawnWave() {
    skeletons.clear();
    for (int i = 0; i < 3 + wave; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos, 4.0f);
    }
}

void Game::drawUI() {
    sf::Text text;
    text.setFont(font);
    text.setString("Fala: " + std::to_string(wave));
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);
    window.draw(text);
}
