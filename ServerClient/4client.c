#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd, n;
    char filename[256], buffer[1024];
    struct sockaddr_in addr = {0};

    if (argc != 3) {                          // server IP and port
        printf("Usage: %s server-ip port\n", argv[0]);
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 1. create TCP socket

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) { // 2. connect
        perror("connect");
        return 1;
    }

    printf("Enter file name: ");
    scanf("%255s", filename);
    write(sockfd, filename, strlen(filename)); // 3. send file name

    printf("\nFile contents:\n");
    // 4. read whatever the server sends until it closes the connection
    while ((n = read(sockfd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close(sockfd);
    return 0;
}