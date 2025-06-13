#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

// Konstruktor – ładowanie mapy, czcionki, start 1. fali
Game::Game(sf::RenderWindow& window) : window(window), player() {
    if (!mapTexture.loadFromFile("assets/maps/forest_map.png")) {
        throw std::runtime_error("Nie udało się załadować mapy!");
    }

    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(
        (float)window.getSize().x / mapTexture.getSize().x,
        (float)window.getSize().y / mapTexture.getSize().y
        );

    if (!font.loadFromFile("assets/fonts/PixelFont.ttf")) {
        throw std::runtime_error("Nie udało się załadować czcionki!");
    }

    // Tekst końca gry
    endText.setFont(font);
    endText.setCharacterSize(60);
    endText.setFillColor(sf::Color::White);
    endText.setStyle(sf::Text::Bold);

    // Tekst "X" do powrotu
    xBackText.setFont(font);
    xBackText.setCharacterSize(32);
    xBackText.setFillColor(sf::Color::White);
    xBackText.setString("X");
    xBackText.setPosition(20.f, 20.f);

    // Niewidoczny hitbox do kliknięcia X
    xHitbox.setSize(sf::Vector2f(50.f, 50.f));
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0));

    spawnWave();
    lastRegenTime.restart();
}

// Obsługa zdarzeń – ruch, zamknięcie, kliknięcie X, toggle statów
void Game::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && !gameOver && !victory) {
            if (event.key.code == sf::Keyboard::I) {
                showStats = !showStats;
            }
        }

        if ((gameOver || victory) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (xHitbox.getGlobalBounds().contains(mousePos)) {
                backToMenu = true;
            }
        }
    }
}

// Główna logika gry – ruch, kolizje, fala, leczenie, śmierć
void Game::update() {
    float deltaTime = clock.restart().asSeconds();

    if (gameOver || victory) return; // nie aktualizujemy po zakończeniu

    player.update(deltaTime);

    for (auto& enemy : skeletons) {
        enemy.update(deltaTime, player.getPosition());
    }

    // Jeśli gracz atakuje – sprawdź czy trafia wrogów
    if (player.isAttacking()) {
        for (auto& enemy : skeletons) {
            if (player.getAttackBounds().intersects(enemy.getBounds())) {
                enemy.takeDamage(player.getAttackStrength());
            }
        }
    }

    // Jeśli wróg uderza gracza (i ma cooldown odświeżony)
    for (auto& enemy : skeletons) {
        if (enemy.getBounds().intersects(player.getBounds()) && enemy.canAttack()) {
            player.takeDamage(enemy.getAttackStrength());
            enemy.resetAttackCooldown();
        }
    }

    // Usuwanie martwych wrogów i leczenie gracza
    skeletons.erase(std::remove_if(skeletons.begin(), skeletons.end(), [&](const SkeletonEnemy& e) {
                        if (e.getHealth() <= 0) {
                            player.heal(8.f); // więcej HP za zabójstwo
                            return true;
                        }
                        return false;
                    }), skeletons.end());

    // Regeneracja życia co 3 sekundy
    if (lastRegenTime.getElapsedTime().asSeconds() > 3.f) {
        player.heal(2.f);
        lastRegenTime.restart();
    }

    // Sprawdzenie końca gry
    if (player.getHealth() <= 0.f) {
        gameOver = true;
        endText.setString("PRZEGRANA");
        endText.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - 100.f);
    }

    // Przejście do kolejnej fali lub wygrana
    if (skeletons.empty() && wave < 10) {
        wave++;
        spawnWave();
    } else if (skeletons.empty() && wave == 10) {
        victory = true;
        endText.setString("WYGRANA!");
        endText.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - 100.f);
    }
}

// Render – rysowanie mapy, gracza, przeciwników, pasek HP, UI, końcówka
void Game::render() {
    window.draw(mapSprite);
    player.render(window);

    for (auto& enemy : skeletons) {
        enemy.render(window);
        drawHealthBar(enemy.getPosition(), enemy.getHealth(), 100.f);
    }

    drawHealthBar(player.getPosition(), player.getHealth(), 100.f);
    drawUI();

    if (gameOver || victory) {
        window.draw(endText);
        window.draw(xBackText);
        window.draw(xHitbox);
    }
}

// Tworzenie nowej fali przeciwników
void Game::spawnWave() {
    int count = 3 + wave;
    skeletons.clear();

    for (int i = 0; i < count; ++i) {
        sf::Vector2f pos(rand() % 1400 + 50, rand() % 900 + 50);
        skeletons.emplace_back(pos, wave * 0.8f + 2.f);
    }
}

// UI – fala, liczba wrogów, statystyki
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

    // Statystyki gracza po kliknięciu I
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

// Pasek zdrowia nad jednostką
void Game::drawHealthBar(sf::Vector2f pos, float hp, float maxHp) {
    sf::RectangleShape bg(sf::Vector2f(40, 5));
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setPosition(pos.x + 12, pos.y - 10);

    sf::RectangleShape hpBar(sf::Vector2f(40 * (hp / maxHp), 5));
    hpBar.setFillColor(sf::Color::Green);
    hpBar.setPosition(pos.x + 12, pos.y - 10);

    window.draw(bg);
    window.draw(hpBar);
}
