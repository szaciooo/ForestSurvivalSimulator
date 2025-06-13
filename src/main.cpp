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
    InstructionState instruction(window);
    Game* game = nullptr;

    while (window.isOpen()) {
        switch (currentState) {
        case State::MENU:
            menu.handleEvents();
            menu.update();
            window.clear();
            menu.render();
            window.display();

            if (menu.shouldShowInstructions()) {
                currentState = State::HOWTO;
                menu.resetState();
            } else if (menu.shouldStartGame()) {
                if (game) delete game;
                game = new Game(window);
                currentState = State::GAME;
                menu.resetState();
            }
            break;

        case State::HOWTO: {
            bool back = false;
            instruction.handleEvents(back);
            window.clear();
            instruction.render();
            window.display();

            if (back) {
                currentState = State::MENU;
            }
            break;
        }

        case State::GAME:
            game->handleEvents();
            game->update();
            window.clear();
            game->render();
            window.display();
            break;
        }
    }

    delete game;
    return 0;
}
