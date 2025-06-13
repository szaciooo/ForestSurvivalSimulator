
#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);
}

void MenuState::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void MenuState::update() {
    // Tu można dodać animacje menu
}

void MenuState::render() {
    window.draw(backgroundSprite);
}
