#include "Interface.hpp"

void Interface::InitWinA(){
    sf::RenderWindow window(sf::VideoMode(std::get<0>(this->dimensions[0]), std::get<1>(this->dimensions[0])), "Comunity Playlist");

    sf::Text title;
    title.setFont(this->font);
    title.setString("SoundScore");
    title.setCharacterSize(22);
    title.setFillColor(sf::Color::White);
    title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 20.f);

    sf::RectangleShape button;
    button.setSize(sf::Vector2f(60.f, 25.f));
    button.setFillColor(sf::Color(191, 50, 207));
    button.setPosition(window.getSize().x / 2 - button.getSize().x / 2, window.getSize().y / 2 + button.getSize().y);

    sf::Text buttonText;
    buttonText.setFont(this->font);
    buttonText.setString("Start");
    buttonText.setCharacterSize(12);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(button.getPosition().x + button.getSize().x / 2 - buttonText.getGlobalBounds().width / 2, button.getPosition().y + button.getSize().y / 2 - buttonText.getGlobalBounds().height / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    if (button.getGlobalBounds().contains(mousePosF)) {
                        std::cout << "Button clicked" << std::endl;
                        window.close();
                        this->InitWinB1();
                    }
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(button);
        window.draw(buttonText); // draw the button text
        window.draw(title);
        window.display();
    }
}

void Interface::InitWinC(){
    sf::RenderWindow window(sf::VideoMode(std::get<0>(this->dimensions[1])/2, std::get<1>(this->dimensions[1])/3), "CMP: Configurations");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
    }
}