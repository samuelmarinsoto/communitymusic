#include <fcntl.h>
#include <unistd.h>
#include "Cancion.cpp"

int main() {
    // Open a file for writing in binary mode
    int fd = open("binary_data.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        // Handle error if unable to open the file
        perror("open");
        return 1;
    }

    // Example binary data
    char archivo[25] = "smackdat.mp3";
    Cancion cancion(archivo);

    // Write the binary data to the file
    ssize_t bytes_written = write(fd, cancion, 524);
    if (bytes_written == -1) {
        // Handle error if unable to write
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}
