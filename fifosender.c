#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUF 1024

int main() {
    char filename[100], buffer[BUF];
    int fd1, fd2, fd_file, n;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("SERVER ONLINE\nWaiting for request...\n");

    fd1 = open(FIFO1, O_RDONLY); // wait for client
    
    n = read(fd1, filename, sizeof(filename));
    filename[n] = '\0';
    printf("Client requested: %s\n", filename);

    fd_file = open(filename, O_RDONLY);
    if(fd_file < 0) {
        strcpy(buffer, "File not found");
    } else {
        n = read(fd_file, buffer, BUF-1);
        buffer[n] = '\0';
        close(fd_file);
        printf("File found. Sending...\n");
    }

    fd2 = open(FIFO2, O_WRONLY); // send back
    write(fd2, buffer, strlen(buffer));
    printf("Transfer completed\n");

    close(fd1); close(fd2);
    return 0;
}



