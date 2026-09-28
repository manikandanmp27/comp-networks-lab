

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char hostname[100];
    struct hostent *host;

    printf("Enter domain name: ");
    scanf("%s", hostname);

    host = gethostbyname(hostname);

    if (host == NULL) {
        printf("DNS lookup failed.\n");
        return 1;
    }

    printf("Official name: %s\n", host->h_name);
    printf("IP Address: %s\n",
           inet_ntoa(*(struct in_addr *)host->h_addr));

    return 0;
}