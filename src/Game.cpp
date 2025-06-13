#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udalo sie zaladowac mapy.");
    }
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        (float)window.getSize().x / mapTexture.getSize().x,
        (float)window.getSize().y / mapTexture.getSize().y
        );

    if (!font.loadFromFile("assets/fonts/PixelFont.ttf")) {
        throw std::runtime_error("Nie udalo sie zaladowac czcionki.");
    }

    // Status text
    statusText.setFont(font);
    statusText.setCharacterSize(60);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(500, 400); // środek mniej więcej

    xText.setFont(font);
    xText.setCharacterSize(32);
    xText.setString("X");
    xText.setFillColor(sf::Color::White);
    xText.setPosition(20, 20);

    xHitbox.setSize(sf::Vector2f(50.f, 50.f));
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0)); // przezroczysty

    spawnWave();
    lastRegenTime.restart();
}

void Game::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
            showStats = !showStats;

        if (gameOver || gameWon) {
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                auto mousePos = sf::Mouse::getPosition(window);
                if (xHitbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    backToMenu = true;
                }
            }
        }
    }
}

void Game::update() {
    if (gameOver || gameWon)
        return;

    float deltaTime = clock.restart().asSeconds();
    player.update(deltaTime);

    for (auto& enemy : skeletons)
        enemy.update(deltaTime, player.getPosition());

    if (player.isAttacking()) {
        for (auto& enemy : skeletons) {
            if (player.getAttackBounds().intersects(enemy.getBounds()))
                enemy.takeDamage(player.getAttackStrength());
        }
    }

    for (auto& enemy : skeletons) {
        if (enemy.getBounds().intersects(player.getBounds()) && enemy.canAttack()) {
            player.takeDamage(enemy.getAttackStrength());
            enemy.resetAttackCooldown();
        }
    }

    skeletons.erase(
        std::remove_if(skeletons.begin(), skeletons.end(), [&](SkeletonEnemy& e) {
            if (e.getHealth() <= 0.f) {
                player.heal(3.f);
                return true;
            }
            return false;
        }),
        skeletons.end()
        );

    if (lastRegenTime.getElapsedTime().asSeconds() > 3.f) {
        player.heal(1.f);
        lastRegenTime.restart();
    }

    if (player.getHealth() <= 0.f) {
        gameOver = true;
        statusText.setString("PRZEGRANA");
        statusText.setFillColor(sf::Color::Red);
    }

    if (skeletons.empty() && wave >= 10) {
        gameWon = true;
        statusText.setString("WYGRANA");
        statusText.setFillColor(sf::Color::Green);
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

    if (gameOver || gameWon) {
        window.draw(statusText);
        window.draw(xText);
        window.draw(xHitbox);
    }
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
    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(24);
    info.setFillColor(sf::Color::White);
    std::stringstream ss;
    ss << "Fala: " << wave << "/10 | Wrogowie: " << skeletons.size();
    info.setString(ss.str());
    info.setPosition(10, 10);
    window.draw(info);

    if (showStats) {
        sf::Text stats;
        stats.setFont(font);
        stats.setCharacterSize(22);
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
