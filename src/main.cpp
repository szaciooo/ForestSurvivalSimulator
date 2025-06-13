#include <SFML/Graphics.hpp>
#include "InstructionState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1536, 1024), "Forest Survival Simulator");
    window.setFramerateLimit(60);

    bool showHowToPlay = true;  // Od razu pokaż instrukcje na tym etapie

    InstructionState instruction(window);

    while (window.isOpen()) {
        if (showHowToPlay) {
            bool backToMenu = false;
            instruction.handleEvents(backToMenu);
            instruction.update();
            window.clear();
            instruction.render();
            window.display();
            if (backToMenu) {
                // W commit 2 po prostu zakończ aplikację zamiast wracać do menu
                window.close();
            }
        }
    }

    return 0;
}