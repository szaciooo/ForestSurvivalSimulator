#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udało się załadować mapy!");
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        static_cast<float>(window.getSize().x) / mapTexture.getSize().x,
        static_cast<float>(window.getSize().y) / mapTexture.getSize().y
        );

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    spawnEnemies();
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

    // Atak gracza
    if (player.isAttacking()) {
        for (auto& enemy : skeletons) {
            if (player.getAttackBounds().intersects(enemy.getBounds())) {
                enemy.takeDamage(player.getAttackStrength());
            }
        }
    }

    // Usuwanie martwych przeciwników i leczenie
    skeletons.erase(std::remove_if(skeletons.begin(), skeletons.end(),
                                   [&](const SkeletonEnemy& e) {
                                       if (e.getHealth() <= 0) {
                                           player.heal(5.f);
                                           return true;
                                       }
                                       return false;
                                   }),
                    skeletons.end());
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& enemy : skeletons) {
        enemy.render(window);
        drawHealthBar(enemy.getPosition(), enemy.getHealth(), 100.f);
    }

    drawHealthBar(player.getPosition(), player.getHealth(), 100.f);
}

void Game::spawnEnemies() {
    skeletons.clear();
    skeletons.emplace_back(sf::Vector2f(400.f, 300.f));
    skeletons.emplace_back(sf::Vector2f(500.f, 500.f));
}

void Game::drawHealthBar(sf::Vector2f pos, float hp, float maxHp) {
    sf::RectangleShape bg(sf::Vector2f(40, 5));
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setPosition(pos.x + 12, pos.y - 10);

    sf::RectangleShape hpBar(sf::Vector2f(40 * (hp / maxHp), 5));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setPosition(pos.x + 12, pos.y - 10);

    window.draw(bg);
    window.draw(hpBar);
}
