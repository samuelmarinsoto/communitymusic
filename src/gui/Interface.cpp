#include "Interface.hpp"
#include <iostream>

Interface::Interface() : window(sf::VideoMode(200, 200), "Comunity Playlist") {
    if (!font.loadFromFile("/home/ema/Downloads/Courier_Prime/CourierPrime-Bold.ttf")) {
        std::cerr << "Error cargando la fuente." << std::endl;
    }

    text.setFont(font);
    text.setString("SoundScore");
    text.setCharacterSize(22);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, 20.f);

    button.setSize(sf::Vector2f(60.f, 25.f));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(window.getSize().x / 2 - button.getSize().x / 2, window.getSize().y / 2 + button.getSize().y);
}

void Interface::run() {
    while (window.isOpen()) {
        handleEvents();
        draw();
    }
}
// Codigo de sever

void Interface::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (button.getGlobalBounds().contains(mousePosF)) {
                    sf::RenderWindow newWindow(sf::VideoMode(800, 600), "Comunity Playlist");
                    while (newWindow.isOpen()) {
                        sf::Event newEvent;
                        while (newWindow.pollEvent(newEvent)) {
                            if (newEvent.type == sf::Event::Closed)
                                newWindow.close();
                        }

                        newWindow.clear(sf::Color::White);
                        newWindow.display();
                    }
                }
            }
        }
    }
}

void Interface::draw() {
    window.clear(sf::Color::White);
    window.draw(button);
    window.draw(text);
    window.display();
}