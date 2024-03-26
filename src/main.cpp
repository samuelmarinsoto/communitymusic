// #include "SFML/Graphics.hpp"
// #include "SFML/Window.hpp"
// #include "lib/Vector.hpp"
// #include "lib/fJSON.hpp"
// #include "modules/c++/LinkedList.hpp"
// #include "SFML/Graphics.hpp" // Include statement for sf::Font
#include "gui/Interface.hpp"
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

int main(int argc, char *argv[]){
    Interface interface;
    interface.run();
    return 0;   
}
    // Codigo de sever
    /* Server socket(49001 ,"127.0.0.1");
    while (true) {
        string* x = socket.access_event();
        cout << x[0] << " said " << x[1] << endl;
    } */

    // // Codigo de interfaz

    // sf::RenderWindow window(sf::VideoMode(200, 200), "Comunity Playlist");
    // sf::Font font;
    //     if (!font.loadFromFile("/home/ema/Downloads/Courier_Prime/CourierPrime-Bold.ttf")) {
        
    // }


    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear(sf::Color::White); // Set background color to white

    //     window.display();


    // sf::Text text;
    // text.setFont(font);
    // text.setString("SoundScore");
    // text.setCharacterSize(22);
    // text.setFillColor(sf::Color::Black);
    // text.setStyle(sf::Text::Bold);
    // text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, 20.f); // Centered the text at the top

    // sf::RectangleShape button;
    // button.setSize(sf::Vector2f(60.f, 25.f)); // Made the button smaller
    // button.setFillColor(sf::Color::Blue); // Button color set to Blue
    // button.setPosition(window.getSize().x / 2 - button.getSize().x / 2, window.getSize().y / 2 + button.getSize().y); // Positioned the button lower

    //         while (window.isOpen())
    //         {
    //             sf::Event event;
    //             while (window.pollEvent(event))
    //             {
    //                 if (event.type == sf::Event::Closed)
    //                     window.close();

    //                 if (event.type == sf::Event::MouseButtonPressed) {
    //                     if (event.mouseButton.button == sf::Mouse::Left) {
    //                         sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //                         sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //                         if (button.getGlobalBounds().contains(mousePosF)) {
    //                             sf::RenderWindow newWindow(sf::VideoMode(800, 600), "Comunity Playlist");
    //                             while (newWindow.isOpen())
    //                             {
    //                                 sf::Event newEvent;
    //                                 while (newWindow.pollEvent(newEvent))
    //                                 {
    //                                     if (newEvent.type == sf::Event::Closed)
    //                                         newWindow.close();
    //                                 }

    //                                 newWindow.clear(sf::Color::White); // Set background color to white
    //                                 newWindow.display();
    //                             }
    //                         }
    //                     }
    //                 }
    //             }

    //             window.clear(sf::Color::White); // Set background color to white
    //             window.draw(button);
    //             window.draw(text);
    //             window.display();
    