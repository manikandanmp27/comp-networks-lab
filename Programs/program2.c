#include <stdio.h>
#include <string.h>

#define POLY "10001000000100001"

// Perform modulo-2 division to calculate the 16-bit CRC remainder
void calculateCRC(char bits[], char rem[]) {
    char temp[200];
    strcpy(temp, bits);

    for (int i = 0; i <= strlen(temp) - 17; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < 17; j++)
                temp[i + j] = (temp[i + j] == POLY[j]) ? '0' : '1';
        }
    }
    // Copy the final 16 bits (including null terminator)
    strcpy(rem, temp + strlen(temp) - 16);
}

int main() {
    char data[100], frame[200], rem[17];

    printf("Enter the data to be sent: ");
    scanf("%s", data);

    // 1. Sender: Append 16 zeros & calculate CRC
    strcpy(frame, data);
    strcat(frame, "0000000000000000");
    calculateCRC(frame, rem);

    // 2. Transmitted frame = data + CRC
    strcpy(frame, data);
    strcat(frame, rem);
    printf("\nCRC: %s\n", rem);
    printf("Transmitted frame: %s\n", frame);

    // 3. Receiver: Check received frame
    printf("\nEnter the received frame: ");
    scanf("%s", frame);
    calculateCRC(frame, rem);

    printf("Receiver CRC: %s\n", rem);
    if (strcmp(rem, "0000000000000000") == 0)
        printf("Received frame is error-free.\n");
    else
        printf("Received frame has one or more errors.\n");

    return 0;
}
