#include "Interface.hpp"

Interface::Interface() {

    this->dimensions[0] = std::make_tuple(200,160);
    this->dimensions[1] = std::make_tuple(950,700);

    if (!this->font.loadFromFile("./res/CourierPrime-Bold.ttf")) {
        std::cerr << "ERROR: Couldn't load font file" << std::endl; // TODO: Change for a LOG
    }

    // Load all the attributes(and INI properties)
    this->Load_INI();
    if ( this->program_data_path == "None" || this->playlist_path == "None"){
        this->InitWinC();
    }
    this->player = new CircularList<MP3Tags>(&this->songs);
    this->loader = new Loader(this->program_data_path);

    // Pick songs anc condition the observer circular list
    this->Song_Selection();
    this->player->conditioned = true;

    // Define the program startup
    this->LIST_TO_PAGED(); // Must change
    this->InitWinA();
}

Interface::~Interface(){
    delete this->player;
}

void Interface::find_replace(char value, char new_value, string& source){
    for (int i = 0; i<source.length(); i++){
        if (source[i] == value){
            source[i] = new_value;
        }
    }
}

void Interface::Song_Selection(){
    // Array to fill with randomly picked songs
    vector<string> songnames = loader->RetrieveFileNames(this->playlist_path);

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
            this->songs.InsertAtEnd(MP3Tags(this->playlist_path + "/" + songnames[index]));
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
}

void Interface::Load_INI(){
    // Vector in which to save all the INI data
    vector< tuple <string, string> > ini_data;

    // Open the file strea,
    ifstream file("./res/config.ini");
    if (!file.is_open()){
        throw std::runtime_error("ERROR: Failed to load file"); // TODO: Change for a LOG & exception
    }
    std::cout << "File loaded! & Reading..." << std::endl; // TODO: Change for a LOG
    // String for reading each line of the file
    string line_buff;

    // Buffers for saving INI values as they are written
    string key = "";
    string value = "";
    bool separator = false;
    // Read the file lines
    while(getline(file, line_buff)){
        for (char c: line_buff){
            if (c != ' ' && c != '='){
                if (separator){
                    value += c;
                }else{
                    key += c;
                }
            }
            if (c == '=' && !separator){
                separator = true;
            }
        }
        ini_data.push_back(make_tuple(key, value));
        separator = false;
        key = "";
        value = "";
    }
    file.close();

    // Retrieve the INI data and save to class attributes
    for (int i =0; i<ini_data.size(); i++){
        std::cout << get<0>(ini_data[i]) << " || " << get<1>(ini_data[i]) <<std::endl;
        if (get<0>(ini_data[i]) == "BIB_PATH"){
            this->playlist_path = get<1>(ini_data[i]);
        } else if (get<0>(ini_data[i]) == "APP_DIR"){
            this->program_data_path = get<1>(ini_data[i]);
        } else if (get<0>(ini_data[i]) == "PAGED_MODE"){
            if (get<1>(ini_data[i]) == "true"){
                this->paged_mode = true;
            } else {
                this->paged_mode = false;
            }
        } else if (get<0>(ini_data[i]) == "PORT"){
            stringstream(get<1>(ini_data[i])) >> this->PORT;
        }
    }
}

void Interface::Write_INI(){

}

void Interface::LIST_TO_PAGED(){
    // this->player->stopObserving();
    // delete this->player;

    this->songs_array = new PagedArray(this->songs.size,this->songs.getHead()->data.GetSize(), 3, this->songs.getHead()->data.GetSize(), "res/swap.bin");

    Node<MP3Tags>* current = this->songs.getHead();
    for (int i = 0; i<this->songs.size; i++){
        this->songs_array->operator[](i) = current->data;
        current = current->next;
    }

    for (int i = 0; i<this->songs_array->getSize();i++){
        MP3Tags song = this->songs_array->operator[](i);

        std::cout << "[" << i+1 << "]" <<song.file << std::endl;
        std::cout << "[" << i+1 << "]" << song.title << std::endl;
        std::cout << "[" << i+1 << "]" << song.artist << std::endl;
        std::cout << "[" << i+1 << "]" << song.album << std::endl;
    }
}

void Interface::PAGED_TO_LIST(){

}