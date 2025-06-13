#include "Game.h"
#include <sstream>
#include <algorithm>
#include <cmath>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    mapTexture.loadFromFile("assets/maps/forest_map.png");
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        (float)window.getSize().x / mapTexture.getSize().x,
        (float)window.getSize().y / mapTexture.getSize().y
        );

    font.loadFromFile("assets/fonts/PixelFont.ttf");
    spawnWave();
    lastRegenTime.restart();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }
}

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    player.update(deltaTime);

    for (auto& enemy : skeletons) {
        enemy.update(deltaTime, player.getPosition());
    }

    if (player.isAttacking()) {
        for (auto& enemy : skeletons) {
            if (player.getAttackBounds().intersects(enemy.getBounds())) {
                enemy.takeDamage(player.getAttackStrength());
            }
        }
    }

    for (auto& enemy : skeletons) {
        if (enemy.getBounds().intersects(player.getBounds())) {
            player.takeDamage(1.f);
        }
    }

    // Usuwanie martwych
    skeletons.erase(std::remove_if(skeletons.begin(), skeletons.end(), [&](SkeletonEnemy& e) {
                        if (e.getHealth() <= 0) {
                            player.heal(7.f);  // więcej leczenia
                            return true;
                        }
                        return false;
                    }), skeletons.end());

    // Nowa fala
    if (skeletons.empty() && wave < 10) {
        wave++;
        spawnWave();
    }
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& enemy : skeletons) {
        enemy.render(window);
        drawHealthBar(enemy.getPosition(), enemy.getHealth(), 100.f, false);
    }

    drawHealthBar(player.getPosition(), player.getHealth(), 100.f, true);
    drawUI();
}

void Game::spawnWave() {
    skeletons.clear();
    int count = 2 + wave;
    for (int i = 0; i < count; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos);
    }
}

void Game::drawUI() {
    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(26);
    info.setFillColor(sf::Color::White);

    std::stringstream ss;
    ss << "Fala: " << wave << "/10  |  Wrogowie: " << skeletons.size();
    info.setString(ss.str());
    info.setPosition(20, 20);
    window.draw(info);
}

void Game::drawHealthBar(sf::Vector2f pos, float hp, float maxHp, bool isPlayer) {
    sf::RectangleShape bg(sf::Vector2f(40, 5));
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setPosition(pos.x + 12, pos.y - 10);

    sf::RectangleShape bar(sf::Vector2f(40 * (hp / maxHp), 5));
    bar.setFillColor(isPlayer ? sf::Color::Green : sf::Color::Red);
    bar.setPosition(pos.x + 12, pos.y - 10);

    window.draw(bg);
    window.draw(bar);
}
