#include "Interface.hpp"
#include <iostream>

Interface::Interface() {

    this->dimensions[0] = std::make_tuple(200,160);
    this->dimensions[1] = std::make_tuple(950,700);

    if (!this->font.loadFromFile("../app/res/CourierPrime-Bold.ttf")) {
        std::cerr << "Error cargando la fuente." << std::endl;
    }

    this->player = new CircularList<MP3Tags>(&this->songs);

    this->loader = new Loader("/home/frederick/Desktop/bib/.cmp");
    
    vector<string> songnames = loader->RetrieveFileNames("/home/frederick/Desktop/bib/playlist1");

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(0,songnames.size()-1);
    for (int i = 0; i<10; i++){
        int gen_int = dist(generator);
        this->songs.InsertAtEnd(MP3Tags("/home/frederick/Desktop/bib/playlist1/" + songnames[gen_int]));
    }

    this->InitWinA();
}

Interface::~Interface(){

}

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
                        this->InitWinB();
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

void Interface::InitWinB(){
        sf::RenderWindow window(sf::VideoMode(std::get<0>(this->dimensions[1]), std::get<1>(this->dimensions[1])), "Comunity Playlist");
        // Color palette for the theme of the window
            // [0]: Grey
            // [1]: Black
            // [2]: Purple
            // [3]: Violet
            // [4]: Dark magenta
        sf::Color palette[] = {sf::Color(27, 26, 27), sf::Color(12, 12, 12), sf::Color(128, 14, 174), sf::Color(56, 8, 151), sf::Color(127, 40, 135)};
        bool paused = true;
        bool performance = false;
        bool dragging_scrub = false;
        int volume_percentage = 50;

        // Music player for window [B]
        std::cout << this->songs.GetNode(0)->data.title << std::endl;
        this->loader->Convert(string(this->songs.GetNode(0)->data.file), "current.wav");
        sf::Music music_player;
            music_player.openFromFile("/home/frederick/Desktop/bib/.cmp/current.wav");
            music_player.setVolume(volume_percentage);
        
        // Total duration of the current song
        int duration = music_player.getDuration().asMilliseconds();
        int offset = music_player.getPlayingOffset().asMilliseconds();

        // Sidebar elements creation
            // Sidebar
        sf::RectangleShape sidebar(sf::Vector2f(float(window.getSize().x/5) + 15.f, float(window.getSize().y)));
            sidebar.setPosition(0.f,0.f);
            sidebar.setFillColor(palette[0]);
            //TODO: Load songs
        
        // Scrub creation
        sf::Text curr_time;
            curr_time.setFont(this->font);
            curr_time.setString("0:00");
            curr_time.setCharacterSize(17);
            curr_time.setFillColor(sf::Color::White);
            curr_time.setPosition(sidebar.getPosition().x + sidebar.getSize().x + 15.f, float(window.getSize().y) - 100.f - curr_time.getGlobalBounds().height/2);

        sf::Text total_time;
            total_time.setFont(this->font);
            total_time.setString("0:00");
            total_time.setCharacterSize(17);
            total_time.setFillColor(sf::Color::White);
            total_time.setPosition(float(window.getSize().x) - total_time.getGlobalBounds().width - 15.f, curr_time.getPosition().y);
        
        sf::CircleShape scrub;
            scrub.setRadius(6.f);
            scrub.setPosition(curr_time.getPosition().x + curr_time.getGlobalBounds().width + 10.f + float(offset), curr_time.getPosition().y + curr_time.getGlobalBounds().height/2);
            scrub.setFillColor(palette[2]);

        sf::RectangleShape scrub_line(sf::Vector2f(scrub.getPosition().x - (sidebar.getSize().x + curr_time.getGlobalBounds().width + 15.f), scrub.getRadius()/1.5));
            scrub_line.setFillColor(scrub.getFillColor());
            scrub_line.setPosition(curr_time.getPosition().x + curr_time.getGlobalBounds().width + 10.f, scrub.getPosition().y + scrub.getRadius()/2);

        float total_scrub_size = (total_time.getPosition().x - 15.f) - (scrub_line.getPosition().x) ;

        // Settings button creation
        sf::RectangleShape topbar(sf::Vector2f(float(window.getSize().x) - (sidebar.getPosition().x + sidebar.getSize().x), 50.f));
            topbar.setFillColor(palette[2]);
            topbar.setPosition(sidebar.getPosition().x + sidebar.getSize().x, 0.f);

        sf::Text settings;
            settings.setFont(this->font);
            settings.setString("Settings");
            settings.setCharacterSize(19);
            settings.setFillColor(sf::Color::White);
            settings.setPosition(sidebar.getPosition().x + sidebar.getSize().x + 15.f, 10.f);
        
        // Memory usage widget creation(TODO)
        sf::Text boost;
            boost.setFont(this->font);
            boost.setString("Boost? OFF");
            boost.setCharacterSize(17);
            boost.setFillColor(sf::Color::White);
            boost.setPosition(float(window.getSize().x) - 275.f, settings.getPosition().y + boost.getGlobalBounds().height/4);
        
        sf::RectangleShape boost_block(sf::Vector2f(12.f, 12.f));
            boost_block.setFillColor(sf::Color::Red);
            boost_block.setPosition(boost.getPosition().x + boost.getGlobalBounds().width + 5.f , boost.getPosition().y + boost_block.getSize().y/2);

        sf::RectangleShape boost_toggle(sf::Vector2f(boost_block.getSize().x*2 , boost_block.getSize().y));
            boost_toggle.setFillColor(palette[1]);
            boost_toggle.setPosition(boost_block.getPosition().x , boost_block.getPosition().y);
        
        // Button 1 creation
        sf::CircleShape back_shape;
            back_shape.setRadius(20.f);
            back_shape.setPosition( sidebar.getPosition().x + sidebar.getSize().x + 20.f + window.getSize().x/4.2 , float(window.getSize().y) - 70.f);
            back_shape.setFillColor(palette[3]);
        sf::Text backward;
            backward.setFont(this->font);
            backward.setString("<<");
            backward.setCharacterSize(16);
            backward.setFillColor(sf::Color::White);
            backward.setPosition( back_shape.getPosition().x + back_shape.getRadius()/2, back_shape.getPosition().y + back_shape.getRadius()/2 );

        // Button 2 creation
        sf::CircleShape minus_shape;
            minus_shape.setRadius(20.f);
            minus_shape.setPosition( back_shape.getPosition().x + 50.f, back_shape.getPosition().y );
            minus_shape.setFillColor(palette[3]);
        sf::Text minus5;
            minus5.setFont(this->font);
            minus5.setString("-5");
            minus5.setCharacterSize(15);
            minus5.setFillColor(sf::Color::White);
            minus5.setPosition( minus_shape.getPosition().x + minus_shape.getRadius()/2 - 5.f, minus_shape.getPosition().y + minus_shape.getRadius()/2 );


        // Button 3 creation
        sf::CircleShape pause_shape;
            pause_shape.setRadius(20.f);
            pause_shape.setPosition( minus_shape.getPosition().x + 50.f, minus_shape.getPosition().y );
            pause_shape.setFillColor(palette[3]);
        sf::Text pause;
            pause.setFont(this->font);
            pause.setString("||");
            pause.setCharacterSize(16);
            pause.setFillColor(sf::Color::White);
            pause.setPosition( pause_shape.getPosition().x + pause_shape.getRadius()/2, pause_shape.getPosition().y + pause_shape.getRadius()/2 );
        
        // Button 4 creation
        sf::CircleShape plus_shape;
            plus_shape.setRadius(20.f);
            plus_shape.setPosition( pause_shape.getPosition().x + 50.f, pause_shape.getPosition().y );
            plus_shape.setFillColor(palette[3]);
        sf::Text plus5;
            plus5.setFont(this->font);
            plus5.setString("+5");
            plus5.setCharacterSize(15);
            plus5.setFillColor(sf::Color::White);
            plus5.setPosition( plus_shape.getPosition().x + plus_shape.getRadius()/2 - 5.f, plus_shape.getPosition().y + plus_shape.getRadius()/2 );

        // Button 5 creation
        sf::CircleShape forw_shape;
            forw_shape.setRadius(20.f);
            forw_shape.setPosition( plus_shape.getPosition().x + 50.f, plus_shape.getPosition().y );
            forw_shape.setFillColor(palette[3]);
        sf::Text forward;
            forward.setFont(this->font);
            forward.setString(">>");
            forward.setCharacterSize(16);
            forward.setFillColor(sf::Color::White);
            forward.setPosition( forw_shape.getPosition().x + forw_shape.getRadius()/2, forw_shape.getPosition().y + forw_shape.getRadius()/2 );

        // Volume control buttons
        sf::Text volume;
            volume.setFont(this->font);
            volume.setString("Volume:");
            volume.setCharacterSize(15);
            volume.setFillColor(sf::Color::White);
            volume.setPosition(forw_shape.getPosition().x + 145.f - volume.getGlobalBounds().width/2, forw_shape.getPosition().y - 5.f);

        sf::Text volume_num;
            volume_num.setFont(this->font);
            volume_num.setString("45%");
            volume_num.setCharacterSize(15);
            volume_num.setFillColor(sf::Color::White);
            volume_num.setPosition(volume.getPosition().x + volume.getGlobalBounds().width/2, volume.getPosition().y + 25.f);

        sf::RectangleShape decrease_shape(sf::Vector2f(15.f, 15.f));
            decrease_shape.setFillColor(palette[4]);
            decrease_shape.setPosition(volume_num.getPosition().x - volume_num.getGlobalBounds().width, volume_num.getPosition().y + decrease_shape.getSize().y/4);
        sf::Text decrease;
            decrease.setFont(this->font);
            decrease.setString("-");
            decrease.setCharacterSize(16);
            decrease.setFillColor(sf::Color::White);
            decrease.setPosition(decrease_shape.getPosition().x + decrease.getGlobalBounds().width/2, decrease_shape.getPosition().y - 2.5f);   

        sf::RectangleShape increase_shape(sf::Vector2f(15.f, 15.f));
            increase_shape.setFillColor(palette[4]);
            increase_shape.setPosition(volume_num.getPosition().x + volume_num.getGlobalBounds().width + 15.f, volume_num.getPosition().y + increase_shape.getSize().y/4);     
        sf::Text increase;
            increase.setFont(this->font);
            increase.setString("+");
            increase.setCharacterSize(16);
            increase.setFillColor(sf::Color::White);
            increase.setPosition(increase_shape.getPosition().x + increase.getGlobalBounds().width/2, increase_shape.getPosition().y - 2.5f);   

        while (window.isOpen()) {
        // -------------------------------------------- Song time management
        if (music_player.getStatus() == sf::Music::Playing){
            offset = music_player.getPlayingOffset().asMilliseconds();
            float time_proportions = float(offset)/float(duration);
            scrub.setPosition(scrub_line.getPosition().x + total_scrub_size*time_proportions, scrub.getPosition().y);
            scrub_line.setSize(sf::Vector2f(scrub.getPosition().x - (sidebar.getSize().x + curr_time.getGlobalBounds().width + 15.f), scrub.getRadius()/1.5));
        }
        if (music_player.getStatus() == sf::Music::Stopped && !paused){
            std::cout << "Song starting again" << std::endl;
            music_player.setPlayingOffset(sf::Time(sf::microseconds(0)));
            paused = true;
        }
        // -------------------------------------------- Events
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // ------------------- Settings interaction
                    if(settings.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Opening configurations" << std::endl;
                        this->InitWinC();
                    };
                    // ------------------- Boost toggle button
                    if (boost_toggle.getGlobalBounds().contains(mousePosF)){
                        if (!performance){
                            boost_block.setPosition(boost_block.getPosition().x + boost_block.getSize().x, boost_block.getPosition().y);
                            boost.setString("Boost? ON");
                            performance = true;
                            // TODO: Change from list to paged array
                        }else{
                            boost_block.setPosition(boost_block.getPosition().x - boost_block.getSize().x, boost_block.getPosition().y);
                            boost.setString("Boost? OFF");
                            performance = false;
                            // TODO: Change from paged array back to list
                        }
                    }
                    // ------------------- Music controls
                    if (pause_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Pause/Continue" << std::endl;
                        if(paused){
                            music_player.play();
                            pause.setString("|>");
                            paused = false;
                        }else{
                            music_player.pause();
                            pause.setString("||");
                            paused = true;
                        }
                    }
                    if (minus_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Went back 5s" << std::endl;
                        // Pause the player
                        music_player.pause();
                        // Move the offset to desired location
                        offset = music_player.getPlayingOffset().asMilliseconds() - 5000;
                        if (offset < 0){
                            offset = 0;
                        }
                        sf::Time moved(sf::microseconds(offset * int(std::pow(10.0,3.0)) ));
                        // Set the playing offset
                        music_player.setPlayingOffset(moved);
                        // Move the scrub
                        float time_proportions = float(offset)/float(duration);
                        scrub.setPosition(scrub_line.getPosition().x + total_scrub_size*time_proportions, scrub.getPosition().y);
                        scrub_line.setSize(sf::Vector2f(scrub.getPosition().x - (sidebar.getSize().x + curr_time.getGlobalBounds().width + 15.f), scrub.getRadius()/1.5));
                        // Continue the reproduction
                        if(!paused){
                            music_player.play();
                        }
                    }
                    if (plus_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Went forward 5s" << std::endl;
                        // Pause the player
                        music_player.pause();
                        // Move the offset to desired location
                        offset = music_player.getPlayingOffset().asMilliseconds() + 5000;
                        if (offset > duration){
                            offset = duration;
                        }
                        sf::Time moved(sf::microseconds(offset * int(std::pow(10.0,3.0)) ));
                        // Set the playing offset
                        music_player.setPlayingOffset(moved);
                        // Move the scrub
                        float time_proportions = float(offset)/float(duration);
                        scrub.setPosition(scrub_line.getPosition().x + total_scrub_size*time_proportions, scrub.getPosition().y);
                        scrub_line.setSize(sf::Vector2f(scrub.getPosition().x - (sidebar.getSize().x + curr_time.getGlobalBounds().width + 15.f), scrub.getRadius()/1.5));
                        // Continue the reproduction
                        if(!paused){
                            music_player.play();
                        }
                    }
                    if (back_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Going to previous song" << std::endl;
                    }
                    if (forw_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Going to next song" << std::endl;
                    }
                    // ------------------- Scrub
                    if (scrub.getGlobalBounds().contains(mousePosF)){
                        dragging_scrub = true;
                    }
                    // ------------------- Volume
                    if (increase_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Volume up" << std::endl;
                        if (volume_percentage < 100){
                            volume_percentage += 5;
                            volume_num.setString(std::to_string(volume_percentage) + "%");
                            music_player.setVolume(volume_percentage);
                        }
                    }
                    if (decrease_shape.getGlobalBounds().contains(mousePosF)){
                        std::cout << "Volume down" << std::endl;
                        if (volume_percentage > 0){
                            volume_percentage -= 5;
                            volume_num.setString(std::to_string(volume_percentage) + "%");
                            music_player.setVolume(volume_percentage);
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (dragging_scrub){
                        if (mousePosF.x > scrub_line.getPosition().x && mousePosF.x < total_time.getPosition().x - 15.f){
                            music_player.pause();
                            // Move scrub
                            scrub.setPosition(mousePosF.x - 7.5f , scrub.getPosition().y);
                            scrub_line.setSize(sf::Vector2f(scrub.getPosition().x - (sidebar.getSize().x + curr_time.getGlobalBounds().width + 15.f), scrub.getRadius()/1.5));
                            dragging_scrub = false;
                            // Move song offset
                            float scrub_proportions = scrub_line.getSize().x/total_scrub_size;
                            sf::Time moved(sf::microseconds( int(duration*scrub_proportions) * int(std::pow(10.0,3.0)) ));
                            music_player.setPlayingOffset(moved);
                            if(!paused){
                                music_player.play();
                            }
                        }
                    }
                }
            }
        }
        window.clear(palette[1]);
        // >>> Draw sidebar(song list) elements
        window.draw(sidebar);   
            // [Missing code implementation]

        // >>> Draw settings button
        window.draw(topbar);
        window.draw(settings);

        // >>> Draw memory usage widget
        window.draw(boost);
        window.draw(boost_toggle);
        window.draw(boost_block);

        // >>> Draw scrub elements
        window.draw(scrub);
        window.draw(curr_time);
        window.draw(total_time);
        window.draw(scrub_line);

        // >>> Draw volume controls
        window.draw(volume);
        window.draw(volume_num);
        window.draw(increase_shape);
        window.draw(increase);
        window.draw(decrease_shape);
        window.draw(decrease);

        // >>> Draw button 1 (Go previous song)
        window.draw(back_shape);
        window.draw(backward);

        // >>> Draw button 2 (--10s)
        window.draw(minus_shape);
        window.draw(minus5);

        // >>> Draw button 3 (Pause//Unpause)
        window.draw(pause_shape);
        window.draw(pause);

        // >>> Draw button 4 (++10s)
        window.draw(plus_shape);
        window.draw(plus5); // draw text4

        // >>> Draw button 5 (Go next song)
        window.draw(forw_shape);
        window.draw(forward); // draw text5


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