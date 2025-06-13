#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "SkeletonEnemy.h"

// Klasa odpowiada za główną logikę gry: zarządzanie grą, falami wrogów, renderingiem itp.
class Game {
public:
    Game(sf::RenderWindow& window); // Konstruktor z referencją do okna SFML

    void handleEvents(bool& backToMenu); // Obsługa zdarzeń (klawiatura, mysz)
    void update();                       // Aktualizacja stanu gry (ruchy, ataki, fale)
    void render();                       // Renderowanie mapy, gracza, przeciwników, UI

private:
    sf::RenderWindow& window; // Główne okno gry (przekazywane z main.cpp)

    // Tło gry (mapa)
    sf::Texture mapTexture;
    sf::Sprite mapSprite;

    sf::Clock clock; // Zegar do obliczania deltaTime (płynność animacji)
    sf::Font font;   // Czcionka gry (PixelFont.ttf)

    Player player;                      // Obiekt gracza
    std::vector<SkeletonEnemy> skeletons; // Wektor wrogów (szkielety)

    int wave = 1; // Numer aktualnej fali
    sf::Clock lastRegenTime; // Timer do regeneracji życia
    bool showStats = false;  // Czy pokazywać statystyki (po kliknięciu I)

    bool gameOver = false;  // Czy gra została przegrana
    bool victory = false;   // Czy gracz wygrał (10 fal pokonanych)

    sf::Text endText;       // Napis „WYGRANA” / „PRZEGRANA”
    sf::Text xBackText;     // Litera „X” do powrotu do menu
    sf::RectangleShape xHitbox; // Niewidzialny hitbox dla „X”

    // Metody pomocnicze
    void spawnWave();                                     // Tworzy nową falę przeciwników
    void drawUI();                                        // Wyświetla UI (fala, liczba wrogów, staty)
    void drawHealthBar(sf::Vector2f pos, float hp, float maxHp); // Pasek zdrowia nad wrogiem/graczem
};
