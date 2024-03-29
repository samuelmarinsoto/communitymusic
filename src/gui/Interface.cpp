#include "Interface.hpp"
#include <iostream>

Interface::Interface() {
    this->crc = 'g';
    this->InitWinA();
}

void Interface::InitWinA(){
    sf::RenderWindow window(sf::VideoMode(200, 200), "Comunity Playlist");

    if (!this->font.loadFromFile("../app/res/CourierPrime-Bold.ttf")) {
        std::cerr << "Error cargando la fuente." << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("SoundScore");
    text.setCharacterSize(22);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, 20.f);

    sf::RectangleShape button;
    button.setSize(sf::Vector2f(60.f, 25.f));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(window.getSize().x / 2 - button.getSize().x / 2, window.getSize().y / 2 + button.getSize().y);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Play");
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
                        this->InitWinB();
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(button);
        window.draw(buttonText); // draw the button text
        window.draw(text);
        window.display();
    }
}

void Interface::InitWinB(){
        sf::RenderWindow newWindow(sf::VideoMode(800, 600), "Comunity Playlist");

        sf::RectangleShape button1(sf::Vector2f(100.f, 50.f));
        button1.setFillColor(sf::Color::Transparent);
        button1.setOutlineThickness(2.f);
        button1.setOutlineColor(sf::Color::Black);
        button1.setPosition(50.f, 100.f);
        sf::Text text1;
        text1.setFont(font);
        text1.setString("<<-");
        text1.setCharacterSize(22);
        text1.setFillColor(sf::Color::Black);
        text1.setStyle(sf::Text::Bold);
        text1.setPosition(button1.getPosition().x + button1.getSize().x / 2 - text1.getGlobalBounds().width / 2, button1.getPosition().y + button1.getSize().y / 2 - text1.getGlobalBounds().height / 2);


        sf::RectangleShape button2(sf::Vector2f(100.f, 50.f));
        button2.setFillColor(sf::Color::Transparent);
        button2.setOutlineThickness(2.f);
        button2.setOutlineColor(sf::Color::Black);
        button2.setPosition(200.f, 100.f);
        sf::Text text2;
        text2.setFont(font);
        text2.setString("10<-");
        text2.setCharacterSize(22);
        text2.setFillColor(sf::Color::Black);
        text2.setStyle(sf::Text::Bold);
        text2.setPosition(button2.getPosition().x + button2.getSize().x / 2 - text2.getGlobalBounds().width / 2, button2.getPosition().y + button2.getSize().y / 2 - text2.getGlobalBounds().height / 2);


        sf::RectangleShape button3(sf::Vector2f(100.f, 50.f));
        button3.setFillColor(sf::Color::Transparent);
        button3.setOutlineThickness(2.f);
        button3.setOutlineColor(sf::Color::Black);
        button3.setPosition(350.f, 100.f);
        sf::Text text3;
        text3.setFont(font);
        text3.setString("P");
        text3.setCharacterSize(22);
        text3.setFillColor(sf::Color::Black);
        text3.setStyle(sf::Text::Bold);
        text3.setPosition(button3.getPosition().x + button3.getSize().x / 2 - text3.getGlobalBounds().width / 2, button3.getPosition().y + button3.getSize().y / 2 - text3.getGlobalBounds().height / 2);
        

        sf::RectangleShape button4(sf::Vector2f(100.f, 50.f));
        button4.setFillColor(sf::Color::Transparent);
        button4.setOutlineThickness(2.f);
        button4.setOutlineColor(sf::Color::Black);
        button4.setPosition(500.f, 100.f);
        sf::Text text4;
        text4.setPosition(button4.getPosition().x + 10, button4.getPosition().y + 10);
        text4.setFont(font);
        text4.setString("->10");
        text4.setCharacterSize(22);
        text4.setFillColor(sf::Color::Black);
        text4.setStyle(sf::Text::Bold);
        text4.setPosition(button4.getPosition().x + button4.getSize().x / 2 - text4.getGlobalBounds().width / 2, button4.getPosition().y + button4.getSize().y / 2 - text4.getGlobalBounds().height / 2);

        sf::RectangleShape button5(sf::Vector2f(100.f, 50.f));
        button5.setFillColor(sf::Color::Transparent);
        button5.setOutlineThickness(2.f);
        button5.setOutlineColor(sf::Color::Black);
        button5.setPosition(650.f, 100.f);
        sf::Text text5;
        text5.setFont(font);
        text5.setString("->>");
        text5.setCharacterSize(22);
        text5.setFillColor(sf::Color::Black);
        text5.setStyle(sf::Text::Bold);
        text5.setPosition(button5.getPosition().x + button5.getSize().x / 2 - text5.getGlobalBounds().width / 2, button5.getPosition().y + button5.getSize().y / 2 - text5.getGlobalBounds().height / 2);

        while (newWindow.isOpen()) {
        button1.setFillColor(sf::Color(255, 165, 0));
        button2.setFillColor(sf::Color(255, 165, 0));
        button3.setFillColor(sf::Color(255, 165, 0));
        button4.setFillColor(sf::Color(255, 165, 0));
        button5.setFillColor(sf::Color(255, 165, 0));
        sf::Event newEvent;
        while (newWindow.pollEvent(newEvent)) {
            if (newEvent.type == sf::Event::Closed)
                newWindow.close();
        }

        newWindow.clear(sf::Color::White);
        newWindow.draw(button1);
        newWindow.draw(text1); // draw text1
        newWindow.draw(button2);
        newWindow.draw(text2); // draw text2
        newWindow.draw(button3);
        newWindow.draw(text3); // draw text3
        newWindow.draw(button4);
        newWindow.draw(text4); // draw text4
        newWindow.draw(button5);
        newWindow.draw(text5); // draw text5
        newWindow.display();
    }
}

void Interface::InitWinC(){

}