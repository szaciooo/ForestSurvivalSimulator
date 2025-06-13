#include "InstructionState.h"

InstructionState::InstructionState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);

    font.loadFromFile("assets/fonts/PixelFont.ttf");

    instructions.setFont(font);
    instructions.setCharacterSize(32);
    instructions.setFillColor(sf::Color::White);
    instructions.setString("WASD - poruszanie\nSPACJA - atak\nI - statystyki");
    instructions.setPosition(600.f, 600.f);

    xText.setFont(font);
    xText.setCharacterSize(32);
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
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseMoved) {
            updateHover();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (hovered) {
                backToMenu = true;
            }
        }
    }
}

void InstructionState::updateHover() {
    auto mousePos = sf::Mouse::getPosition(window);
    if (xHitbox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        hovered = true;
        xText.setFillColor(sf::Color::Yellow);
    } else {
        hovered = false;
        xText.setFillColor(sf::Color::White);
    }
}

void InstructionState::render() {
    window.draw(backgroundSprite);
    window.draw(instructions);
    window.draw(xText);
}
