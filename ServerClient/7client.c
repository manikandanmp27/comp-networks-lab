#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// Send filename through FIFO1 and display the received file contents.
int main() {
    char filename[100], buffer[3000];
    int fd1, fd2;
    ssize_t n;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    printf("Enter filename: ");
    scanf("%99s", filename);

    fd1 = open("fifo1", O_WRONLY);
    write(fd1, filename, strlen(filename));
    close(fd1);

    fd2 = open("fifo2", O_RDONLY);
    printf("\nReceived file contents:\n");
    while ((n = read(fd2, buffer, sizeof(buffer))) > 0)
        fwrite(buffer, 1, n, stdout);

    close(fd2);
    return 0;
}

