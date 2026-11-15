#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s, i;
    char frame[20], ack[20];
    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(17000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *)&server, sizeof(server));

    for(i = 1; i <= 6; i += 3)
    {
        printf("\nSending window:\n");

        for(int j = i; j < i + 3 && j <= 6; j++)
        {
            sprintf(frame, "%d", j);
            send(s, frame, strlen(frame), 0);
            printf("Frame %d sent\n", j);
        }

        for(int j = i; j < i + 3 && j <= 6; j++)
        {
            recv(s, ack, sizeof(ack), 0);
            printf("Acknowledgement received: %s\n", ack);
        }
    }

    strcpy(frame, "exit");
    send(s, frame, strlen(frame), 0);

    close(s);
    return 0;
}