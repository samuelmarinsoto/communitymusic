#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"

class Interface {
public:
    Interface();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape button;

    void handleEvents();
    void draw();
};

#endif // INTERFACE_HPP
