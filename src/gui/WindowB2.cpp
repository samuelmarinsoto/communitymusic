#include "Interface.hpp"

void Interface::InitWinB2(){
    sf::RenderWindow window(sf::VideoMode(std::get<0>(this->dimensions[1]), std::get<1>(this->dimensions[1])), "Comunity Playlist");

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::Black);
    }
}