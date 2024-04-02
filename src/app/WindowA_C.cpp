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
                        if (this->paged_mode){
                            std::cout << "Loading with pages" << std::endl;
                            this->InitWinB2();
                        } else {
                            this->InitWinB1();
                        }
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
    sf::RenderWindow window(sf::VideoMode(std::get<0>(this->dimensions[1])-100, std::get<1>(this->dimensions[1])-80), "CMP: Configurations");
    // Color palette for the theme of the window
        // [0]: Grey
        // [1]: Black
        // [2]: Purple
        // [3]: Violet
        // [4]: Dark magenta
    sf::Color palette[] = {sf::Color(27, 26, 27), sf::Color(12, 12, 12), sf::Color(128, 14, 174), sf::Color(56, 8, 151), sf::Color(127, 40, 135)};

    int selected_field = 0;
    bool caps = false;

    // ------------------------------------------ Text Fields
        // >>> Playlist field
    sf::Text header_bib;
        header_bib.setFont(this->font);
        header_bib.setString("Write the path to your playlist directory:");
        header_bib.setCharacterSize(18);
        header_bib.setFillColor(sf::Color::White);
        header_bib.setPosition(float(window.getSize().x)/20, 60.f);
    
    sf::RectangleShape BIB_field(sf::Vector2f(float(window.getSize().x)-(float(window.getSize().x)/20)*2, 40.f));
        BIB_field.setFillColor(palette[0]);
        BIB_field.setPosition(header_bib.getPosition().x, header_bib.getPosition().y + BIB_field.getSize().y + 5.f);

    sf::Text BIB_PATH;
        BIB_PATH.setFont(this->font);
        BIB_PATH.setString(this->playlist_path);
        BIB_PATH.setFillColor(sf::Color::White);
        BIB_PATH.setCharacterSize(16);
        BIB_PATH.setPosition(BIB_field.getPosition().x + 5.f, BIB_field.getPosition().y + BIB_PATH.getGlobalBounds().height/2);

        // >>> App directory field
    sf::Text header_app;
        header_app.setFont(this->font);
        header_app.setString("Write the path where you want to save CMP files:");
        header_app.setCharacterSize(18);
        header_app.setFillColor(sf::Color::White);
        header_app.setPosition(header_bib.getPosition().x ,BIB_field.getPosition().y + BIB_field.getSize().y + 30.f);
    
    sf::RectangleShape APP_field(BIB_field.getSize());
        APP_field.setFillColor(palette[0]);
        APP_field.setPosition(header_app.getPosition().x, header_app.getPosition().y + APP_field.getSize().y + 5.f);

    sf::Text APP_PATH;
        APP_PATH.setFont(this->font);
        APP_PATH.setString(this->program_data_path);
        APP_PATH.setFillColor(sf::Color::White);
        APP_PATH.setCharacterSize(16);
        APP_PATH.setPosition(APP_field.getPosition().x + 5.f, APP_field.getPosition().y + APP_PATH.getGlobalBounds().height/2);

        // >>> Server port field
    sf::Text header_port;
        header_port.setFont(this->font);
        header_port.setString("Write the port #number in which you want to host your playlist:");
        header_port.setCharacterSize(18);
        header_port.setFillColor(sf::Color::White);
        header_port.setPosition(header_bib.getPosition().x ,APP_field.getPosition().y + APP_field.getSize().y + 30.f);
    
    sf::RectangleShape PORT_field(BIB_field.getSize());
        PORT_field.setFillColor(palette[0]);
        PORT_field.setPosition(header_port.getPosition().x, header_port.getPosition().y + PORT_field.getSize().y + 5.f);

    sf::Text PORT_TEXT;
        PORT_TEXT.setFont(this->font);
        PORT_TEXT.setString(to_string(this->PORT));
        PORT_TEXT.setFillColor(sf::Color::White);
        PORT_TEXT.setCharacterSize(16);
        PORT_TEXT.setPosition(PORT_field.getPosition().x + 5.f, PORT_field.getPosition().y + PORT_TEXT.getGlobalBounds().height/2);
        // >>> Paged array field
    // ------------------------------------------ Buttons

    while (window.isOpen()) {
        // --------------- GUI elements updating
        if (selected_field == 0){
            BIB_PATH.setFillColor(sf::Color::White);
            APP_PATH.setFillColor(sf::Color::White);
            PORT_TEXT.setFillColor(sf::Color::White);
        } else if (selected_field == 1){
            BIB_PATH.setFillColor(palette[2]);
            APP_PATH.setFillColor(sf::Color::White);
            PORT_TEXT.setFillColor(sf::Color::White);
        } else if (selected_field == 2){
            BIB_PATH.setFillColor(sf::Color::White);
            APP_PATH.setFillColor(palette[2]);
            PORT_TEXT.setFillColor(sf::Color::White);
        }
        else if (selected_field == 3){
            BIB_PATH.setFillColor(sf::Color::White);
            APP_PATH.setFillColor(sf::Color::White);
            PORT_TEXT.setFillColor(palette[2]);
        }

        // --------------- Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                this->Write_INI();
            }
            // ----------------------- Keyboard inputs
            if (event.type == sf::Event::KeyPressed){
                sf::Event::KeyEvent key_typed = event.key;
                string selected_text = "";
                switch (key_typed.code){
                case sf::Keyboard::A:
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'A';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'a';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'A';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'a';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'A';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'a';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::Q :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'Q';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'q';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'Q';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'q';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'Q';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'q';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::W :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'W';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'w';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'W';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'w';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'W';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'w';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::E :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'E';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'e';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'E';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'e';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'E';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'e';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::R :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'R';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'r';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'R';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'r';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'R';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'r';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::T:
                if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'T';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 't';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'T';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 't';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'T';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 't';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Y :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'Y';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'y';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'Y';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'y';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'Y';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'y';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::U :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'U';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'u';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'U';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'u';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'U';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'u';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::I :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'I';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'i';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'I';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'i';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'I';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'i';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::O :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'O';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'o';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'O';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'o';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'O';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'o';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::P :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'P';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'p';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'P';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'p';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'P';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'p';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::S :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'S';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 's';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'S';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 's';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'S';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 's';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::D :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'D';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'd';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'D';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'd';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'D';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'd';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::F :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'F';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'f';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'F';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'f';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'F';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'f';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::G :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'G';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'g';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'G';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'g';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'G';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'g';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::H :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'H';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'h';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'H';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'h';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'H';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'h';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::J :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'J';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'j';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'J';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'j';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'J';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'j';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::K :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'K';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'k';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'K';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'k';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'K';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'k';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::L :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'L';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'l';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'L';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'l';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'L';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'l';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::Z :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'Z';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'z';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'Z';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'z';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'Z';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'z';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::X :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'X';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'x';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'X';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'x';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'X';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'x';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::C :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'C';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'c';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'C';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'c';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'C';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'c';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::V :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'V';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'v';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'V';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'v';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'V';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'v';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::B :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'B';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'b';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'B';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'b';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'B';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'b';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::N :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'N';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'n';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'N';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'n';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'N';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'n';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::M :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + 'M';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + 'm';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + 'M';
                        } else {
                            selected_text = string(APP_PATH.getString()) + 'm';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + 'M';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + 'm';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Space :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + ' ';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + ' ';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + ' ';
                        } else {
                            selected_text = string(APP_PATH.getString()) + ' ';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + ' ';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + ' ';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Slash:
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '?';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '/';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '?';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '/';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '?';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '/';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Period:
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '>';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '.';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '>';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '.';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '>';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '.';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num0:
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + ')';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '0';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + ')';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '0';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + ')';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '0';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num1:
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '!';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '1';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '!';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '1';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '!';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '1';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num2 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '@';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '2';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '@';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '2';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '@';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '2';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num3:
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '#';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '3';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '#';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '3';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '#';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '3';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::Num4 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '$';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '4';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '$';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '4';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '$';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '4';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num5 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '%';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '5';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '%';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '5';
                        }
                        
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '%';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '5';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num6 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '^';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '6';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '^';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '6';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '^';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '6';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num7 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '&';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '7';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '&';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '7';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '&';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '7';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::Num8 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '*';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '8';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '*';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '8';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '*';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '8';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                
                case sf::Keyboard::Num9 :
                    if (selected_field == 1){
                        if (caps){
                            selected_text = string(BIB_PATH.getString()) + '(';
                        } else {
                            selected_text = string(BIB_PATH.getString()) + '9';
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        if (caps){
                            selected_text = string(APP_PATH.getString()) + '(';
                        } else {
                            selected_text = string(APP_PATH.getString()) + '9';
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        if (caps){
                            selected_text = string(PORT_TEXT.getString()) + '(';
                        } else {
                            selected_text = string(PORT_TEXT.getString()) + '9';
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;

                case sf::Keyboard::BackSpace:
                    if (selected_field == 1){
                        selected_text = string(BIB_PATH.getString());
                        if (selected_text.size() > 0){
                            selected_text.pop_back();
                        }
                        BIB_PATH.setString(selected_text);
                    } else if (selected_field == 2){
                        selected_text = string(APP_PATH.getString());
                        if (selected_text.size() > 0){
                            selected_text.pop_back();
                        }
                        APP_PATH.setString(selected_text);
                    } else if (selected_field == 3){
                        selected_text = string(PORT_TEXT.getString());
                        if (selected_text.size() > 0){
                            selected_text.pop_back();
                        }
                        PORT_TEXT.setString(selected_text);
                    }
                    break;
                case sf::Keyboard::LShift:
                    if (caps){
                        caps = false;
                    } else {
                        caps = true;
                    }
                    break;
                default:
                    break;
                }
            }
            // ----------------------- Mouse inputs
            if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                if (event.mouseButton.button == sf::Mouse::Left){
                    if (BIB_field.getGlobalBounds().contains(mousePosF)){
                        selected_field = 1;
                    }
                    if (APP_field.getGlobalBounds().contains(mousePosF)){
                        selected_field = 2;
                    }
                    if (PORT_field.getGlobalBounds().contains(mousePosF)){
                        selected_field = 3;
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right){
                    if (!BIB_field.getGlobalBounds().contains(mousePosF) && !APP_field.getGlobalBounds().contains(mousePosF) && !PORT_field.getGlobalBounds().contains(mousePosF)){
                        selected_field = 0;
                    }
                }
            }
        }

        // Clear the window
        window.clear(palette[1]);

        // >>> Field 1[Playlist path] elements
        window.draw(header_bib);
        window.draw(BIB_field);
        window.draw(BIB_PATH);

        // >>> Field 2[Program path] elements
        window.draw(header_app);
        window.draw(APP_field);
        window.draw(APP_PATH);

        // >>> Field 3[port] elements
        window.draw(header_port);
        window.draw(PORT_field);
        window.draw(PORT_TEXT);

        // >>> Field 4[Paged mode toggle] elements

        window.display();
    }
}