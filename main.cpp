#include <iostream>
#include "PlayerRayCaster.h"

int main() {
    auto clock = sf::Clock();
    auto deltaTime = clock.restart().asSeconds();

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280, 720), "RayCast");
    window.setFramerateLimit(60);
    PlayerRayCaster playerRayCaster = PlayerRayCaster(sf::Vector2f(0, 0), deltaTime);
    auto mousePos = (sf::Vector2f) sf::Mouse::getPosition(window);
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
            else if (ev.type == sf::Event::MouseMoved)
                mousePos = (sf::Vector2f) sf::Mouse::getPosition(window) ;
        }

        deltaTime = clock.restart().asSeconds();
        playerRayCaster.update();
        playerRayCaster.lookOn(mousePos);
        window.clear(sf::Color::White);
        playerRayCaster.draw(window);
        window.display();
    }
}
