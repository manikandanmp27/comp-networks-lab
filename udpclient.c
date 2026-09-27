#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sock, n, len;
    char file[100], data[1024];
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    len = sizeof(server);

    printf("Enter file name: ");
    scanf("%s", file);

    /* Send file name */
    sendto(sock, file, strlen(file), 0,
           (struct sockaddr *)&server, len);

    /* Receive file contents */
    while (1)
    {
        n = recvfrom(sock, data, 1023, 0,
                     (struct sockaddr *)&server, &len);

        data[n] = '\0';

        if (strcmp(data, "EOF") == 0)
            break;

        printf("%s", data);
    }

    close(sock);
    return 0;
}