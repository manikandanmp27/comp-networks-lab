#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sock;
    char buffer[256];
    struct sockaddr_in server = {0};

    if (argc != 3) {
        printf("Usage: %s <server-ip> <port>\n", argv[0]);
        return 1;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Please enter the message: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send to server
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));

    // Receive acknowledgment (no need to store sender address, pass NULL)
    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Got an ack: %s", buffer);

    close(sock);
    return 0;
}

