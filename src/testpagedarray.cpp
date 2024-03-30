#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include "PagedArray.hpp"
#include "MP3Tags.hpp"

std::vector<std::string> loadFilenames(const std::string& directoryPath) {
    std::vector<std::string> filenames;

    DIR* dir = opendir(directoryPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << directoryPath << std::endl;
        return filenames;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {  // Regular file
            filenames.push_back(entry->d_name);
        }
    }

    closedir(dir);
    return filenames;
}

int main() {
    std::string directoryPath = "musica";
    std::vector<std::string> filenames = loadFilenames(directoryPath);

	char archivo[25] = "swap.bin";
	PagedArray parray(55, 396, 3, 3168, archivo);
	
    // size_t i = 0;
    // // Print the loaded filenames
    // for (const std::string& filename : filenames) {
    //     std::cout << filename << std::endl;
    //     MP3Tags cancion(filename);
    //     parray[i] = cancion;
    //     i++;
    // }
    std::string songfile = "smackdat.mp3";
    
    MP3Tags cancion(songfile);
	parray[31] = cancion;
    std::cout << "Artist 31: " << parray[31].artist << std::endl;

    return 0;
}
