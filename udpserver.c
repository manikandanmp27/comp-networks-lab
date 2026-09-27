#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sock, n, len;
    char file[100], data[1024];
    FILE *fp;
    struct sockaddr_in server, client;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    len = sizeof(client);

    printf("Server waiting...\n");

    /* Receive file name */
    n = recvfrom(sock, file, 100, 0,
                 (struct sockaddr *)&client, &len);
    file[n] = '\0';

    printf("Requested file: %s\n", file);

    fp = fopen(file, "r");

    if (fp == NULL)
    {
        strcpy(data, "File not found");
        sendto(sock, data, strlen(data), 0,
               (struct sockaddr *)&client, len);
    }
    else
    {
        while (fgets(data, 1024, fp) != NULL)
        {
            sendto(sock, data, strlen(data), 0,
                   (struct sockaddr *)&client, len);
        }

        fclose(fp);

        /* End of file */
        strcpy(data, "EOF");
        sendto(sock, data, strlen(data), 0,
               (struct sockaddr *)&client, len);

        printf("File sent successfully\n");
    }

    close(sock);
    return 0;
}