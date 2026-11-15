#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sock;
    char buf[256];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    if(argc!= 3) {
        printf("Usage:./client <server_ip> <port>\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server.sin_addr);

    printf("Please enter the message: ");
    fgets(buf, 256, stdin);

    sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&server, len);

    int n = recvfrom(sock, buf, 256, 0, (struct sockaddr*)&server, &len);
    buf[n] = '\0';
    printf("Got an ack: %s", buf); // same as your 

    close(sock);
}