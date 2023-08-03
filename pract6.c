#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<unistd.h>

#define PACKET_SIZE 32
#define TIMEOUT_SEC 2

// Function to validate if the input contains only 0s and 1s
bool isValidBinaryString(const char* str) {
    while (*str) {
        if (*str != '0' && *str != '1') {
            return false;
        }
        str++;
    }
    return true;
}

// Simulate a reliable channel with 80% success rate
bool isChannelSuccessful() {
    return rand() % 100 < 80;
}

void sender(int seq_num, const char* data) {
    printf("Sending packet %d\n", seq_num);
    // Simulate transmission delay
    sleep(1);

    if (isChannelSuccessful()) {
        printf("Packet %d successfully received by receiver\n", seq_num);
    } else {
        printf("Packet %d lost, resending...\n", seq_num);
        sender(seq_num, data); // Resend the packet
    }
}

void receiver(int seq_num, const char* data) {
    if (isChannelSuccessful()) {
        printf("ACK for packet %d received by sender\n", seq_num);
    } else {
        printf("ACK for packet %d lost, requesting resend...\n", seq_num);
        receiver(seq_num, data); // Request resend of the packet
    }
}

int main() {
    srand(time(NULL));

    int totalPackets;
    printf("Enter the total number of packets to send: ");
    scanf("%d", &totalPackets);

    char data[PACKET_SIZE + 1]; // +1 for null terminator

    for (int currentPacket = 0; currentPacket < totalPackets; currentPacket++) {
        int seq_num = currentPacket;
        
        printf("Enter binary data for packet %d (up to %d characters): ", seq_num, PACKET_SIZE);
        scanf(" %[^\n]", &data);
        
        if (strlen(data) > PACKET_SIZE || !isValidBinaryString(data)) {
            printf("Invalid input. Please enter a valid binary string (up to %d characters).\n", PACKET_SIZE);
            currentPacket--; // Retry for the current packet
            continue;
        }
        
        sender(seq_num, data);
        receiver(seq_num, data);
    }

    printf("Data transmission completed!\n");

    return 0;
}
