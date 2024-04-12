#ifndef MP3_TO_WAV_H
#define MP3_TO_WAV_H

#include <sndfile.h>
#include <mpg123.h>
#include <boost/filesystem.hpp>

#include <string>
#include <cstring>
#include <vector>
#include <glog/logging.h>

using namespace std;
// Allows converting MP3 files to WAV for playing the music
class Loader {
    private:
        string output;
        string cache_file;
    public:
    // Creates a loader instance with the output directory where the WAV files should be written(this directory should contain existing WAVS to write over)
    Loader(string output_dir);
    // Destroys the loader;
    ~Loader(){}
    // Converts a given MP3 file to WAV at the specified output dir with the filename "{output_name}.wav"
    int Convert(string path_to_MP3, string output_name);
    // Retrieves all file names in a directory
    vector<string> RetrieveFileNames(string path_to_dir);
};

#endif // MP3_TO_WAV_H
