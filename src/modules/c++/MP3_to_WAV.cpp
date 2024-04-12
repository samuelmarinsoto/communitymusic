#include "MP3_to_WAV.h"

#include <iostream>
Loader::Loader(string output_dir){
    // Set the output directory
    this->output = output_dir;

    // Read the output directory and pick any wave file as the cache
    int limit = 1;
    try{
        boost::filesystem::directory_iterator end;
        for( boost::filesystem::directory_iterator dir(this->output); dir != end; ++dir){
            if (boost::filesystem::is_regular_file(*dir)){
                this->cache_file = dir->path().filename().string();
            }
            if (limit == 1){
                break;
            }
        }
    }catch (const std::exception& ex) {
        LOG(INFO) << "MP3_to_Wav.h: Error loading output directory" << ex.what();
        // TODO: Manage exception
    }
}

int Loader::Convert(string path_to_MP3, string output_name){
    string old_out_path = this->output + "/" + this->cache_file;
    string new_out_path = this->output + "/" + output_name + ".wav";
    this->cache_file = output_name + ".wav";

    try {
        // Renaming the file
        boost::filesystem::rename(old_out_path, new_out_path);
    } 
    catch (const std::exception& ex) {
        LOG(INFO) << "MP3_to_Wav.h: Error renaming output file" << ex.what();
        // TODO: Manage exception
    }

    // Initialize libmpg123
    mpg123_init();

    // Create mpg123 handle
    mpg123_handle *mh;
    mh = mpg123_new(NULL, NULL);
    if (!mh) {
        // std::cerr << "Failed to initialize mpg123" << std::endl;
        return 400;
    }

    // Open MP3 file for decoding
    int err = mpg123_open(mh, path_to_MP3.c_str());
    if (err != MPG123_OK) {
        // std::cerr << "Failed to open MP3 file: " << mpg123_plain_strerror(err) << std::endl;
        mpg123_delete(mh);
        mpg123_exit();
        return 401;
    }

    // Get MP3 file information
    long rate;
    int channels, encoding;
    mpg123_getformat(mh, &rate, &channels, &encoding);

    // Initialize libsndfile
    SF_INFO info;
    info.samplerate = rate;
    info.channels = channels;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open WAV file for writing
    SNDFILE* wavFile = sf_open(new_out_path.c_str(), SFM_WRITE, &info);
    if (!wavFile) {
        // std::cerr << "Error when opening output WAV file" << std::endl;
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        return 403;
    }

    // Buffer to hold decoded audio data
    constexpr int BUFFER_SIZE = 4096;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    // Decode MP3 and write to WAV
    while (mpg123_read(mh, buffer, BUFFER_SIZE, &bytesRead) == MPG123_OK) {
        sf_write_raw(wavFile, buffer, bytesRead);
    }

    // Close files and cleanup
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    sf_close(wavFile);

    return 0;
}

vector<string> Loader::RetrieveFileNames(string path_to_dir){
    vector<string> names;

    try{
        boost::filesystem::directory_iterator end;
        for (boost::filesystem::directory_iterator dir(path_to_dir); dir != end; ++dir){
            if (boost::filesystem::is_regular_file(*dir)){
                names.push_back(dir->path().filename().string());
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error loading directory\n" << ex.what() << std::endl;
        // TODO: Manage exception
    }

    return names;
}
