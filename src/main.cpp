#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <string>


int main(int argc, char *argv[]){
    // Codigo de sever
    /* Server socket(49001 ,"127.0.0.1");
    while (true) {
        string* x = socket.access_event();
        cout << x[0] << " said " << x[1] << endl;
    } */
    // Codigo de interfaz
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}