#include "InstructionState.h"
#include <iostream> // tylko do debugowania – można usunąć

// Konstruktor – ładowanie grafiki, czcionki, ustawianie tekstów
InstructionState::InstructionState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setColor(sf::Color(255, 255, 255, 150)); // lekki półprzezroczysty efekt

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    // Ustawienie instrukcji sterowania
    instructions.setFont(font);
    instructions.setCharacterSize(32);
    instructions.setFillColor(sf::Color::White);
    instructions.setString(
        "STEROWANIE:\n"
        "WASD - sterowanie bohaterem\n"
        "I - ekwipunek\n"
        "SPACEBAR - atak"
        );

    // Wyśrodkowanie tekstu
    sf::FloatRect bounds = instructions.getLocalBounds();
    instructions.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    instructions.setPosition(1536 / 2.f, 1024 / 2.f);

    // Ustawienie litery "X"
    xText.setFont(font);
    xText.setCharacterSize(32);
    xText.setString("X");
    xText.setFillColor(sf::Color::White);
    xText.setPosition(20.f, 20.f);

    // Niewidzialny prostokąt (hitbox) do kliknięcia na X
    xHitbox.setSize(sf::Vector2f(50.f, 50.f));
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0)); // przezroczysty
}

// Obsługa zdarzeń: zamknięcie okna, kliknięcie X
void InstructionState::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseMoved) {
            updateHover(); // podświetlanie X
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            updateHover();
            if (hovered) {
                backToMenu = true; // cofamy się do menu
            }
        }
    }
}

// Sprawdza czy myszka znajduje się nad X-em
void InstructionState::updateHover() {
    auto mousePos = sf::Mouse::getPosition(window);
    if (xHitbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        hovered = true;
        xText.setFillColor(sf::Color::Yellow); // podświetlenie
    } else {
        hovered = false;
        xText.setFillColor(sf::Color::White);
    }
}

// Nie ma nic do aktualizacji
void InstructionState::update() {}

// Rysowanie tła, instrukcji i przycisku X
void InstructionState::render() {
    window.draw(backgroundSprite);
    window.draw(instructions);
    window.draw(xText);
    // window.draw(xHitbox); // opcjonalnie – do debugowania
}
