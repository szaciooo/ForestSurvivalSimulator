#include "Game.h"
#include <iostream>
#include <ctime> // dla srand

Game::Game(sf::RenderWindow& window) : window(window), player() {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udało się załadować mapy!");
    }

    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        static_cast<float>(window.getSize().x) / mapTexture.getSize().x,
        static_cast<float>(window.getSize().y) / mapTexture.getSize().y
        );

    if (!font.loadFromFile("assets/fonts/PixelFont.ttf")) {
        throw std::runtime_error("Nie udało się załadować czcionki!");
    }

    srand(static_cast<unsigned>(time(nullptr))); // inicjalizacja RNG

    spawnWave(); // Dodano: startowa fala
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    player.update(deltaTime);

    for (auto& enemy : skeletons) {
        enemy.update(deltaTime, player.getPosition());
    }
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& enemy : skeletons) {
        enemy.render(window);
    }
}

void Game::spawnWave() {
    int count = 5;
    skeletons.clear();

    for (int i = 0; i < count; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos);
    }
}
