#include <iostream>
#include <stdio.h>
// #include "Lib/cpptk/cpptk.h"
#include <SFML/Graphics.hpp>

int main()
{
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

/*
void hello(){
    puts("Hello C++/Tk!");
}

int main(int, char *argv[]){
    init(argv[0]);

    button(".b") -text("Say Hello") -command(hello);
    pack(".b") -padx(20) - pady(6);

    runEventLoop();
}
*/