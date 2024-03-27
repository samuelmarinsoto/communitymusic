#include "MP3_to_WAV.h"

Loader::Loader(string output_dir){
    this->output = output_dir;
}

int Loader::Convert(string path_to_MP3, string output_name){
    string full_out_path = this->output + "/"+ output_name + ".wav";

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
    SNDFILE* wavFile = sf_open(full_out_path.c_str(), SFM_WRITE, &info);
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
}