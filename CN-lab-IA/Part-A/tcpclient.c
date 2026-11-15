#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int s, n;
    char file[100], data[1000];
    struct sockaddr_in a;

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(5000);
    a.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr*)&a, sizeof(a));

    printf("Enter filename: ");
    scanf("%s", file);

    write(s, file, strlen(file));

    n = read(s, data, 999);
    data[n] = '\0';

    printf("\nFile contents:\n%s\n", data);

    close(s);
    return 0;
}