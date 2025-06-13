#include <SFML/Graphics.hpp>
#include "MenuState.h"
#include "InstructionState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1536, 1024), "Forest Survival Simulator");
    window.setFramerateLimit(60);

    enum class State { MENU, HOWTO };
    State currentState = State::MENU;

    MenuState menu(window);
    InstructionState instruction(window);

    while (window.isOpen()) {
        switch (currentState) {
        case State::MENU:
            menu.handleEvents();
            if (menu.shouldShowInstructions()) {
                currentState = State::HOWTO;
                break;
            }
            window.clear();
            menu.render();
            window.display();
            break;

        case State::HOWTO: {
            bool backToMenu = false;
            instruction.handleEvents(backToMenu);
            window.clear();
            instruction.render();
            window.display();
            if (backToMenu) {
                menu.resetState();
                currentState = State::MENU;
            }
            break;
        }
        }
    }

    return 0;
}
