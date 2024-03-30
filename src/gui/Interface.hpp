#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <tuple>
#include <string>

// Class for interacting with SFML resources
class Interface {
    // ----------------------------- ATTRIBUTES
protected:
    std::tuple<int, int> dimensions[2];
    sf::Font font;
    // ----------------------------- METHODS
public:
    // Creates an instance of the class which automatically runs window [A]
    Interface();
private:
    // Initializes the first window[A] of the app
    // This is the welcome window
    void InitWinA();
    // Initializes the second window[B] of the app
    // This is the main program window where the user can use the playlist functions
    void InitWinB();
    // Initializes the third window[C] of the app
    // This is the configurations window
    void InitWinC();
};

#endif // INTERFACE_HPP
