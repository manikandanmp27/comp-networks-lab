#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

// Receive filename through FIFO1 and send file contents through FIFO2.
int main() {
    char filename[100], buffer[3000];
    int fd1, fd2, file;
    ssize_t n;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("SERVER ONLINE\nWaiting for request...\n");
    fd1 = open(FIFO1, O_RDONLY);
    n = read(fd1, filename, sizeof(filename) - 1);
    if (n <= 0) {
        perror("Filename read failed");
        return 1;
    }
    filename[n] = '\0';

    file = open(filename, O_RDONLY);
    fd2 = open(FIFO2, O_WRONLY);

    if (file < 0) {
        write(fd2, "File not found!", 15);
        perror("File not found");
    } else {
        printf("Server: %s found\nTransferring contents...\n", filename);
        while ((n = read(file, buffer, sizeof(buffer))) > 0)
            write(fd2, buffer, n);
        close(file);
        printf("Transfer completed\n");
    }

    close(fd1);
    close(fd2);
    return 0;
}

