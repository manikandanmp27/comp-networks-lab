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
    int fd1, fd2, n;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter file path: ");
    scanf("%s", filename);

    fd1 = open(FIFO1, O_WRONLY); // send filename
    write(fd1, filename, strlen(filename));

    fd2 = open(FIFO2, O_RDONLY); // wait for content
    n = read(fd2, buffer, BUF-1);
    buffer[n] = '\0';

    printf("\nFile received! Contents:\n%s\n", buffer);

    close(fd1); close(fd2);
    return 0;
}