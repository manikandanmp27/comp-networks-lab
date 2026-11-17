#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Sends frames and receives acknowledgments from the receiver.
int main() {
    int sock, client, len, i = 1;
    char frame[30], ack[30];
    struct sockaddr_in addr = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(17000);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0 ||
        listen(sock, 5) < 0) {
        perror("Bind/Listen");
        return 1;
    }

    printf("Waiting for receiver...\n");

    // NULL, NULL can be used because we don't need client's IP address.
    // Old version:
    // len = sizeof(addr);
    // client = accept(sock, (struct sockaddr *)&addr, (socklen_t *)&len);
    client = accept(sock, NULL, NULL);

    while (1) {
        printf("Enter Data Frame %d (exit to end): ", i);
        scanf("%29s", frame);

        send(client, frame, strlen(frame) + 1, 0);
        if (strcmp(frame, "exit") == 0)
            break;

        int n = recv(client, ack, sizeof(ack) - 1, 0);
        if (n <= 0) break;
        ack[n] = '\0';
        printf("Acknowledgment: %s\n", ack);
        i++;
    }

    close(client);
    close(sock);
    return 0;
}