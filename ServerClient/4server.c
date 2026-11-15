#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, n;
    char filename[256], buffer[1024];
    struct sockaddr_in addr = {0};
    FILE *fp;

    if (argc != 2) {                          // port is given on command line
        printf("Usage: %s port\n", argv[0]);
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 1. create TCP socket

    addr.sin_family = AF_INET;                // IPv4
    addr.sin_addr.s_addr = INADDR_ANY;        // accept on any local IP
    addr.sin_port = htons(atoi(argv[1]));     // port number

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)); // 2. bind
    listen(sockfd, 5);                                    // 3. listen
    printf("Server waiting for client...\n");

    newsockfd = accept(sockfd, NULL, NULL);   // 4. accept the client

    n = read(newsockfd, filename, 255);       // 5. read file name from client
    filename[n] = '\0';
    printf("Requested file: %s\n", filename);

    fp = fopen(filename, "r");                // 6. try to open the file
    if (fp == NULL) {
        write(newsockfd, "File not found!\n", 16);
        printf("File not found\n");
    } else {
        // send the file in chunks until end of file
        while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
            write(newsockfd, buffer, n);
        fclose(fp);
        printf("File sent\n");
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}