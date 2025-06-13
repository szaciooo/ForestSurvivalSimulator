#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udało się załadować mapy.");
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        (float)window.getSize().x / mapTexture.getSize().x,
        (float)window.getSize().y / mapTexture.getSize().y
        );

    if (!font.loadFromFile("assets/fonts/PixelFont.ttf")) {
        throw std::runtime_error("Nie udało się załadować czcionki.");
    }

    spawnWave();
    lastRegenTime.restart();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
            showStats = !showStats;
        }
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

    // Atak wroga
    for (auto& enemy : skeletons) {
        if (enemy.getBounds().intersects(player.getBounds()) && enemy.canAttack()) {
            player.takeDamage(enemy.getAttackStrength());
            enemy.resetAttackCooldown();
        }
    }

    // Usuwanie martwych przeciwników
    skeletons.erase(
        std::remove_if(skeletons.begin(), skeletons.end(), [&](SkeletonEnemy& e) {
            if (e.getHealth() <= 0.f) {
                player.heal(3.f);  // nagroda za zabicie
                return true;
            }
            return false;
        }),
        skeletons.end()
        );

    // Regeneracja zdrowia co 3s
    if (lastRegenTime.getElapsedTime().asSeconds() > 3.f) {
        player.heal(1.f);
        lastRegenTime.restart();
    }

    if (skeletons.empty() && wave < 10) {
        ++wave;
        spawnWave();
    }
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    drawHealthBar(player.getPosition(), player.getHealth(), 100.f, true);

    for (auto& enemy : skeletons) {
        enemy.render(window);
        drawHealthBar(enemy.getPosition(), enemy.getHealth(), 100.f, false);
    }

    drawUI();
}

void Game::spawnWave() {
    skeletons.clear();
    int count = 3 + wave;
    for (int i = 0; i < count; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos, wave * 0.7f + 2.f);
    }
}

void Game::drawUI() {
    sf::Text topLeft;
    topLeft.setFont(font);
    topLeft.setCharacterSize(28);
    topLeft.setFillColor(sf::Color::White);
    std::stringstream ss;
    ss << "Fala: " << wave << "/10 | Wrogowie: " << skeletons.size();
    topLeft.setString(ss.str());
    topLeft.setPosition(10, 10);
    window.draw(topLeft);

    if (showStats) {
        sf::Text stats;
        stats.setFont(font);
        stats.setCharacterSize(26);
        stats.setFillColor(sf::Color::White);
        std::stringstream ss2;
        ss2 << "Zdrowie: " << (int)player.getHealth() << "\n";
        ss2 << "Sila: " << (int)player.getAttackStrength() << "\n";
        ss2 << "Szybkosc: 100";
        stats.setString(ss2.str());

        float textWidth = stats.getLocalBounds().width;
        float x = window.getSize().x - textWidth - 20;
        stats.setPosition(x, 20);
        window.draw(stats);
    }
}

void Game::drawHealthBar(sf::Vector2f pos, float hp, float maxHp, bool isPlayer) {
    sf::RectangleShape bg(sf::Vector2f(40, 5));
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setPosition(pos.x + 12, pos.y - 10);

    sf::RectangleShape hpBar(sf::Vector2f(40 * (hp / maxHp), 5));
    hpBar.setFillColor(isPlayer ? sf::Color::Green : sf::Color::Red);
    hpBar.setPosition(pos.x + 12, pos.y - 10);

    window.draw(bg);
    window.draw(hpBar);
}
