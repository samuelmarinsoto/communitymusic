#include "Interface.hpp"

Interface::Interface() {

    this->dimensions[0] = std::make_tuple(200,160);
    this->dimensions[1] = std::make_tuple(950,700);

    if (!this->font.loadFromFile("../app/res/CourierPrime-Bold.ttf")) {
        std::cerr << "Error cargando la fuente." << std::endl;
    }

    this->player = new CircularList<MP3Tags>(&this->songs);

    this->loader = new Loader("/home/frederick/Desktop/bib/.cmp");
    
    // Array to fill with randomly picked songs
    vector<string> songnames = loader->RetrieveFileNames("/home/frederick/Desktop/bib/playlist1");

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(0,songnames.size()-1);

    // Selected random indexes
    if (songnames.size() < 10){
        int randNums[songnames.size()];
        int counter = 0;

        while (counter < songnames.size()){
            int gen_int = dist(generator);
            std::cout << gen_int;

            bool repeated = false;
            for (int i = 0; i<counter; i++){
                if (randNums[i]==gen_int){
                    repeated = true;
                    break;
                }
            }

            if (!repeated){
                randNums[counter++] = gen_int;
            }
        }

        // Select all the songs from the random indexes
        for (int index : randNums){
            this->songs.InsertAtEnd(MP3Tags("/home/frederick/Desktop/bib/playlist1/" + songnames[index]));
        }
    } else {
        int randNums[10];
        int counter = 0;

        while (counter < 10){
            int gen_int = dist(generator);

            bool repeated = false;
            for (int i = 0; i<counter; i++){
                if (randNums[i]==gen_int){
                    repeated = true;
                    break;
                }
            }

            if (!repeated){
                randNums[counter++] = gen_int;
            }
        }

        // Select all the songs from the random indexes
        for (int index : randNums){
            this->songs.InsertAtEnd(MP3Tags("/home/frederick/Desktop/bib/playlist1/" + songnames[index]));
        }
    }
    this->player->conditioned = true;

    this->InitWinA();
}

Interface::~Interface(){

}

void Interface::find_replace(char value, char new_value, string& source){
    for (int i = 0; i<source.length(); i++){
        if (source[i] == value){
            source[i] = new_value;
        }
    }
}

void Interface::Load_INI(){

}