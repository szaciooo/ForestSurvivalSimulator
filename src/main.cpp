#include <SFML/Graphics.hpp>
#include "MenuState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1536, 1024), "Forest Survival Simulator");
    window.setFramerateLimit(60);

    MenuState menu(window);

    while (window.isOpen()) {
        menu.handleEvents();
        menu.update();

        window.clear();
        menu.render();
        window.display();

        if (menu.shouldStartGame()) {
            // Kolejny commit będzie wczytywał grę
            break;
        }
        if (menu.shouldShowInstructions()) {
            // Kolejny commit wyświetli instrukcje
            break;
        }
    }

    return 0;
}
