#include "MenuState.h"

// Konstruktor – ładowanie tekstur, ustawienie tła i przycisków
MenuState::MenuState(sf::RenderWindow& window) : window(window) {
    backgroundTexture.loadFromFile("assets/backgrounds/menu_bg1.png");
    backgroundSprite.setTexture(backgroundTexture);

    sf::Texture temp;

    // Przycisk START
    temp.loadFromFile("assets/ui/button_start.png");
    buttonTexturesIdle.push_back(temp);
    temp.loadFromFile("assets/ui/button_start_hover.png");
    buttonTexturesHover.push_back(temp);

    // Przycisk JAK GRAĆ
    temp.loadFromFile("assets/ui/button_howtoplay.png");
    buttonTexturesIdle.push_back(temp);
    temp.loadFromFile("assets/ui/button_howtoplay_hover.png");
    buttonTexturesHover.push_back(temp);

    // Ustawienie pozycji i kształtu przycisków
    sf::Vector2f buttonSize(300.f, 100.f);
    float buttonX = (1536 - 300) / 2.f;
    std::vector<float> buttonYs = {580.f, 680.f};

    for (size_t i = 0; i < 2; ++i) {
        sf::RectangleShape button(buttonSize);
        button.setPosition(buttonX, buttonYs[i]);
        button.setTexture(&buttonTexturesIdle[i]);
        buttonShapes.push_back(button);
    }
}

// Obsługa kliknięć myszą i zamknięcia
void MenuState::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseMoved) {
            updateButtonStates(); // podświetlenie przycisków
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (hoveredButton == 0) {
                startGame = true;
            } else if (hoveredButton == 1) {
                showInstructions = true;
            }
        }
    }
}

// Nie używana w tym projekcie, ale można tu dodać animacje
void MenuState::update() {}

// Rysowanie tła i przycisków
void MenuState::render() {
    window.draw(backgroundSprite);
    for (const auto& button : buttonShapes) {
        window.draw(button);
    }
}

// Sprawdza pozycję myszy względem przycisków
void MenuState::updateButtonStates() {
    hoveredButton = -1;
    for (size_t i = 0; i < buttonShapes.size(); ++i) {
        auto bounds = buttonShapes[i].getGlobalBounds();
        if (bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            buttonShapes[i].setTexture(&buttonTexturesHover[i]); // podświetl
            hoveredButton = static_cast<int>(i);
        } else {
            buttonShapes[i].setTexture(&buttonTexturesIdle[i]); // normalny wygląd
        }
    }
}

// --- GETTERY FLAG ---

bool MenuState::shouldStartGame() const {
    return startGame;
}

bool MenuState::shouldShowInstructions() const {
    return showInstructions;
}

void MenuState::resetState() {
    startGame = false;
    showInstructions = false;
}
