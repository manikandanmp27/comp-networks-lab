#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Receives each frame and sends an acknowledgment.
int main() {
    int sock, n, i = 1;
    char frame[30];
    struct sockaddr_in addr = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(17000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connect");
        return 1;
    }

    while ((n = recv(sock, frame, sizeof(frame) - 1, 0)) > 0) {
        frame[n] = '\0';
        if (strcmp(frame, "exit") == 0)
            break;

        printf("Frame %d data %s received\n", i++, frame);
        char ack[] = "ACK";
        send(sock, ack, sizeof(ack), 0);
    }

    close(sock);
    return 0;
}