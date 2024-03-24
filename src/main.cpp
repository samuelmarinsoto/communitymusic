// #include "SFML/Graphics.hpp"
// #include "SFML/Window.hpp"
#include "lib/Vector.hpp"
#include "lib/fJSON.hpp"
#include "modules/c++/LinkedList.hpp"

#include <iostream>
#include <string>
#include <tuple>

using namespace std;
int main(int argc, char *argv[]){
    // Codigo de sever
    /* Server socket(49001 ,"127.0.0.1");
    while (true) {
        string* x = socket.access_event();
        cout << x[0] << " said " << x[1] << endl;
    } */

    // Codigo de interfaz
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

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
    }*/
    Dictionary json = JSON::parse("{\"cmd\":\"print\",\"attch\":[4,false,null],\"extra\":{\"key\":67,\"status\":\"ok\"}}");
        json.add("extra", JSON::convert_to_value<string>("jhbjbdjkabd"));
    std::cout << json["extra"].content << std::endl;

    LinkedList<int> list;
        list.insert(41);
        list.insert(90);
        list.insert(0);
        list.insert(7);
        list.find_remove(0);
        list.pop();
        list[1] = 2;
    std::cout << "Node data: " << list[1] << "\nList size: " << list.size << std::endl;


    vect<tuple <string, int> > arr;
        arr.push(make_tuple("fff", 47));
    //Array dict;
        //dict.append(JSON::convert_to_value<int>(76));
    //Value val = JSON::convert_to_value<Array>(dict);
    std::cout << get<1> (arr[0]) << std::endl;
    return 0;
}