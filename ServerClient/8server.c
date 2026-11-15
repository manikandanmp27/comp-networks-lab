#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int sock;
    char buffer[1024];
    struct sockaddr_in server = {0}, client = {0};
    socklen_t len = sizeof(client);

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    while (1) {
        int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client, &len);
        buffer[n] = '\0';
        printf("Received a datagram: %s", buffer);

        sendto(sock, "Got your message\n", 17, 0, (struct sockaddr *)&client, len);
    }

    close(sock);
    return 0;
}

