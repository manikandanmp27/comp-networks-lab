#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int s, c, n;
    char file[100], data[1000];
    struct sockaddr_in a;
    FILE *fp;

    s = socket(AF_INET, SOCK_STREAM, 0);

    a.sin_family = AF_INET;
    a.sin_port = htons(5000);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 1);

    printf("Waiting for client...\n");
    c = accept(s, NULL, NULL);

    n = read(c, file, 100);
    file[n] = '\0';

    fp = fopen(file, "r");

    if(fp == NULL)
        write(c, "File not found", 15);
    else
    {
        n = fread(data, 1, 999, fp);
        data[n] = '\0';
        write(c, data, n);
        fclose(fp);
    }

    close(c);
    close(s);
    return 0;
}