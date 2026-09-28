#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
//Socket → Connect → Send → Receive
int main()
{
    int s, c;
    char frame[20], ack[20];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(17000);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 5);

    printf("Waiting for sender...\n");
    c = accept(s, (struct sockaddr *)&client, &len);

    while(1)
    {
        int n = recv(c, frame, sizeof(frame)-1, 0);
        frame[n] = '\0';

        if(strcmp(frame, "exit") == 0)
            break;

        printf("Frame received: %s\n", frame);

        strcpy(ack, "ACK");
        send(c, ack, strlen(ack), 0);
    }

    close(c);
    close(s);
    return 0;
}
