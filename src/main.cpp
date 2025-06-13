#include <SFML/Graphics.hpp>
#include "MenuState.h"
#include "InstructionState.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1536, 1024), "Forest Survival Simulator");
    window.setFramerateLimit(60);

    enum class State { MENU, HOWTO, GAME };
    State currentState = State::MENU;

    MenuState menu(window);
    InstructionState instructions(window);
    Game game(window);

    while (window.isOpen()) {
        switch (currentState) {
        case State::MENU:
            menu.handleEvents();
            if (menu.shouldStartGame()) {
                currentState = State::GAME;
                break;
            }
            if (menu.shouldShowInstructions()) {
                currentState = State::HOWTO;
                break;
            }
            menu.update();
            window.clear();
            menu.render();
            window.display();
            break;

        case State::HOWTO: {
            bool backToMenu = false;
            instructions.handleEvents(backToMenu);

            window.clear();
            instructions.render();
            window.display();
            if (backToMenu) {
                menu.resetState();
                currentState = State::MENU;
            }
            break;
        }

        case State::GAME:
            game.handleEvents();
            game.update();
            window.clear();
            game.render();
            window.display();
            break;
        }
    }

    return 0;
}
