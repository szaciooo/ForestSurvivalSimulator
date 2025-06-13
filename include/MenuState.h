#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Klasa reprezentująca menu główne gry
class MenuState {
public:
    MenuState(sf::RenderWindow& window); // Konstruktor

    void handleEvents();  // Obsługa kliknięć, zamknięcie
    void update();        // Ewentualne animacje/przejścia (nieużywane)
    void render();        // Rysowanie tła i przycisków

    bool shouldStartGame() const;       // Czy kliknięto START
    bool shouldShowInstructions() const;// Czy kliknięto Jak Grać
    void resetState();                  // Resetuje flagi kliknięć

private:
    sf::RenderWindow& window;

    // Tło menu
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Tekstury przycisków (START i JAK GRAĆ)
    std::vector<sf::Texture> buttonTexturesIdle;
    std::vector<sf::Texture> buttonTexturesHover;

    // Figury przycisków
    std::vector<sf::RectangleShape> buttonShapes;

    int hoveredButton = -1; // numer przycisku nad którym jest myszka
    bool startGame = false; // flaga kliknięcia START
    bool showInstructions = false; // flaga kliknięcia Jak Grać

    void updateButtonStates(); // aktualizacja podświetlenia przycisków
};
