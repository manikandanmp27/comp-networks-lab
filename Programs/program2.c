#include <stdio.h>
#include <string.h>
#define POLY "10001000000100001"
// Perform modulo-2 division to calculate the CRC remainder.
void calculateCRC(char bits[], char remainder[]) {
    char temp[200];
    int len = strlen(bits);
     strcpy(temp, bits);
    for (int i = 0; i <= len - 17; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < 17; j++)
                temp[i + j] = (temp[i + j] == POLY[j]) ? '0' : '1';
        }
    }
    // Extract the final 16 bits as the CRC remainder.
    strncpy(remainder, temp + len - 16, 16);
    remainder[16] = '\0';
}

int main() {
    char data[100], padded[200], crc[17];
    char frame[200], receivedCRC[17];
    printf("Enter the data to be sent: ");
    scanf("%99s", data);

    // Append 16 zeros before calculating the sender's CRC.
    strcpy(padded, data);
    strcat(padded, "0000000000000000");
    calculateCRC(padded, crc);
    
    // Append the CRC to the original data to form the frame.
    strcpy(frame, data);
    strcat(frame, crc);
     printf("\nCRC: %s\n", crc);
    printf("Transmitted frame: %s\n", frame);
     printf("\nEnter the received frame: ");
    scanf("%199s", frame);
    
    // A zero remainder indicates that no error was detected.
    calculateCRC(frame, receivedCRC);
    printf("Receiver CRC: %s\n", receivedCRC);
    if (strcmp(receivedCRC, "0000000000000000") == 0)
        printf("Received frame is error-free.\n");
    else
        printf("Received frame has one or more errors.\n");
    
    return 0;
}