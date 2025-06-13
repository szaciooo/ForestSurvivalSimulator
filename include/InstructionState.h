#pragma once
#include <SFML/Graphics.hpp>

// Klasa odpowiadająca za stan wyświetlania instrukcji sterowania
class InstructionState {
public:
    InstructionState(sf::RenderWindow& window);   // Konstruktor

    void handleEvents(bool& backToMenu); // Obsługa zdarzeń – zamknięcie, kliknięcie X
    void update();                       // Ewentualne aktualizacje (nieużywane)
    void render();                       // Rysowanie instrukcji i przycisku X

private:
    sf::RenderWindow& window;

    // Tło instrukcji (obraz menu z lekkim przyciemnieniem)
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Czcionka i tekst instrukcji
    sf::Font font;
    sf::Text instructions;

    // Tekst "X" oraz jego hitbox do powrotu do menu
    sf::Text xText;
    sf::RectangleShape xHitbox;
    bool hovered = false;

    void updateHover(); // Sprawdza czy myszka jest nad X-em
};
