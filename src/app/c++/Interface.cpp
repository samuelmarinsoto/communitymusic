#include "Interface.hpp"

Interface::Interface() {
    this->user = nullptr;
    this->memUsage = 0.0;
    this->dimensions[0] = std::make_tuple(200,160);
    this->dimensions[1] = std::make_tuple(950,700);

    if (!this->font.loadFromFile("./res/CourierPrime-Bold.ttf")){
        LOG(INFO) << "ERROR: Couldn't load font file";
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
            LOG(INFO) << gen_int;

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
            this->songs.InsertAtEnd(MP3Tags(this->playlist_path +"/" + songnames[index]));
        }
    }
}

void Interface::Load_INI(){
    // Vector in which to save all the INI data
    vector< tuple <string, string> > ini_data;

    // Open the file stream
    ifstream file("res/config.ini");
    if (!file.is_open()){
    	LOG(INFO) << "ERROR: Failed to load file";
        throw std::runtime_error("ERROR: Failed to load file"); // TODO: Change for exception
    }
    LOG(INFO) << "File loaded! & Reading...";
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
        LOG(INFO) << get<0>(ini_data[i]) << " || " << get<1>(ini_data[i]);
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

    // Create the paged array
    char bin_path[] = "./res/swap.bin";
    this->songs_array = new PagedArray(this->songs.size,this->songs.getHead()->data.GetSize(), 3, this->songs.getHead()->data.GetSize(), bin_path);

    Node<MP3Tags>* current = this->songs.getHead();
    for (int i = 0; i<this->songs.size; i++){
        this->songs_array->operator[](i) = current->data;
        current = current->next;
    }

    // Liberate all data from the linked list
    for (int j = this->songs.size-1; j>=0; j--){
        this->songs.deleteNode(j);
    }

   LOG(INFO) << this->songs.size;

    this->player->stopObserving();
    delete this->player;
    this->player = nullptr;
}

void Interface::PAGED_TO_LIST(){
    this->player = new CircularList<MP3Tags>(&this->songs);
    for (int i = 0; i<this->songs_array->getSize(); i++){
        MP3Tags song = this->songs_array->operator[](i);
        this->songs.InsertAtEnd(song);
    }
    this->player->conditioned = true;

    delete this->songs_array;
    this->songs_array = nullptr;

    LOG(INFO) << this->songs.size;
    Node<MP3Tags>* ref = this->songs.getHead();
    while (ref!=nullptr){
        LOG(INFO) << ref->data.title;
        ref = ref->next;
    }
}
