#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int s;
    char frame[20], ack[20];
    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(17000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *)&server, sizeof(server));

    while(1)
    {
        printf("Enter frame (exit to stop): ");
        scanf("%s", frame);

        send(s, frame, strlen(frame), 0);

        if(strcmp(frame, "exit") == 0)
            break;

        recv(s, ack, sizeof(ack), 0);
        printf("Acknowledgement: %s\n", ack);
    }

    close(s);
    return 0;
}
