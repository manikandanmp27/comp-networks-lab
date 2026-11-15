#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int sock;
    char buf[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    if(argc < 2) {
        printf("Usage:./server <port>\n");
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(sock, (struct sockaddr*)&server, sizeof(server));
    printf("SERVER ONLINE on port %s\n", argv[1]);

    while(1) {
        int n = recvfrom(sock, buf, 1024, 0, (struct sockaddr*)&client, &len);
        buf[n] = '\0';
        printf("Received a datagram: %s", buf); // same as your write(1,buf,n)

        sendto(sock, "Got your message\n", 17, 0, (struct sockaddr*)&client, len);
    }
    close(sock);
}