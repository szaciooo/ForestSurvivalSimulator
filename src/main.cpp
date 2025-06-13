#include <SFML/Graphics.hpp>
#include "MenuState.h"
#include "Game.h"
#include "InstructionState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1536, 1024), "Forest Survival Simulator");
    window.setFramerateLimit(60);

    enum class State { MENU, GAME, HOWTO };
    State currentState = State::MENU;

    MenuState menu(window);
    Game game(window);
    InstructionState instruction(window);

    while (window.isOpen()) {
        switch (currentState) {
        case State::MENU:
            menu.handleEvents();
            if (menu.shouldStartGame()) {
                game = Game(window); // restart gry
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
            instruction.handleEvents(backToMenu);
            instruction.update();
            window.clear();
            instruction.render();
            window.display();
            if (backToMenu) {
                menu.resetState();
                currentState = State::MENU;
            }
            break;
        }

        case State::GAME: {
            bool backToMenu = false;
            game.handleEvents(backToMenu);
            if (backToMenu) {
                currentState = State::MENU;
                menu.resetState();
                break;
            }
            game.update();
            window.clear();
            game.render();
            window.display();
            break;
        }
        }
    }

    return 0;
}
