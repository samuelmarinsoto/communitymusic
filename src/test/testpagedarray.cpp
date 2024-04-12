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
        	std::string fullFilename = directoryPath + "/" + entry->d_name;
            filenames.push_back(fullFilename);
        }
    }

    closedir(dir);
    return filenames;
}

int main() {
    std::string directoryPath = "../musica";
    std::vector<std::string> filenames = loadFilenames(directoryPath);

	char archivo[25] = "swap.bin";
	PagedArray parray(55, 396, 1, 3168, archivo);
	
    size_t i = 0;
    // Print the loaded filenames
    for (const std::string& filename : filenames) {
    	std::cout << filename << std::endl;
    	MP3Tags cancion(filename);
    	parray[i] = cancion;
    	std::cout << cancion.title << "\n" << std::endl;
    	if (i<26)
    		std::cout << parray[i].title << "\n" << std::endl;
    	i++;
    }
    i = 0;
	for (const std::string& filename : filenames) {
		std::cout << parray[i].title << "\n" << std::endl;
    	i++;
    }

    return 0;
}
