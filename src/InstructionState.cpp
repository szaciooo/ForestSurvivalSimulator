#include "InstructionState.h"

InstructionState::InstructionState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    instructions.setFont(font);
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::White);
    instructions.setString("STEROWANIE:\nWASD - ruch\nSPACJA - atak\nI - statystyki");
    instructions.setPosition(300, 400);

    xText.setFont(font);
    xText.setCharacterSize(30);
    xText.setString("X");
    xText.setFillColor(sf::Color::White);
    xText.setPosition(20.f, 20.f);

    xHitbox.setSize(sf::Vector2f(50.f, 50.f));
    xHitbox.setPosition(15.f, 15.f);
    xHitbox.setFillColor(sf::Color(255, 255, 255, 0));
}

void InstructionState::handleEvents(bool& backToMenu) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (xHitbox.getGlobalBounds().contains(
                    static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                backToMenu = true;
            }
        }
    }
}

void InstructionState::render() {
    window.draw(backgroundSprite);
    window.draw(instructions);
    window.draw(xText);
}
