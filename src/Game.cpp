#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>

Game::Game(sf::RenderWindow& window) : window(window), player() {
    mapTexture.loadFromFile("assets/maps/forest_map.png");
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        static_cast<float>(window.getSize().x) / mapTexture.getSize().x,
        static_cast<float>(window.getSize().y) / mapTexture.getSize().y
        );

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    xText.setFont(font);
    xText.setString("X");
    xText.setCharacterSize(30);
    xText.setFillColor(sf::Color::White);
    xText.setPosition(20, 20);

    xHitbox.setSize(sf::Vector2f(50, 50));
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0)); // transparent

    endText.setFont(font);
    endText.setCharacterSize(60);
    endText.setFillColor(sf::Color::White);
    endText.setPosition(500, 400);

    spawnWave();
    lastRegenTime.restart();
}

void Game::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (state != GameState::Playing) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (xHitbox.getGlobalBounds().contains(mousePos)) {
                    backToMenu = true;
                    // Reset stanu gry:
                    player = Player();
                    wave = 1;
                    skeletons.clear();
                    spawnWave();
                    state = GameState::Playing;
                }
            }
        }
    }
}

void Game::update() {
    if (state != GameState::Playing) return;

    float dt = clock.restart().asSeconds();

    player.update(dt);
    for (auto& skeleton : skeletons)
        skeleton.update(dt, player.getPosition());

    if (player.isAttacking()) {
        for (auto& skeleton : skeletons) {
            if (player.getAttackBounds().intersects(skeleton.getBounds())) {
                skeleton.takeDamage(player.getAttackStrength());
            }
        }
    }

    for (auto& skeleton : skeletons) {
        if (skeleton.getBounds().intersects(player.getBounds()) && skeleton.canAttack()) {
            player.takeDamage(skeleton.getAttackStrength());
            skeleton.resetAttackCooldown();
        }
    }

    skeletons.erase(std::remove_if(skeletons.begin(), skeletons.end(), [&](SkeletonEnemy& s) {
                        if (s.getHealth() <= 0) {
                            player.heal(8.f);
                            return true;
                        }
                        return false;
                    }), skeletons.end());

    if (lastRegenTime.getElapsedTime().asSeconds() > 4.f) {
        player.heal(2.f);
        lastRegenTime.restart();
    }

    if (player.getHealth() <= 0.f) {
        state = GameState::Lost;
        endText.setString("PRZEGRANA");
    }

    if (skeletons.empty() && wave < 10) {
        wave++;
        spawnWave();
    } else if (skeletons.empty() && wave == 10) {
        state = GameState::Won;
        endText.setString("WYGRANA");
    }
}

void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& s : skeletons) {
        s.render(window);
        drawHealthBar(s.getPosition(), s.getHealth(), 100.f);
    }

    drawHealthBar(player.getPosition(), player.getHealth(), 100.f);
    drawUI();

    if (state == GameState::Won || state == GameState::Lost) {
        window.draw(endText);
        window.draw(xText);
        window.draw(xHitbox);
    }
}

void Game::spawnWave() {
    skeletons.clear();
    for (int i = 0; i < 3 + wave; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos, 2.f + wave * 0.5f);
    }
}

void Game::drawUI() {
    sf::Text text;
    text.setFont(font);
    text.setString("Fala: " + std::to_string(wave) + "/10");
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 20);
    window.draw(text);
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

