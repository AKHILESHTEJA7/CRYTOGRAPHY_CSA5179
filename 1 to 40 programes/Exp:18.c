#include <stdio.h>

// Function to perform a left circular shift on a value
unsigned int leftCircularShift(unsigned int value, int shift) {
    return (value << shift) | (value >> (28 - shift));
}

// Function to generate DES subkeys from an initial key
void generateSubkeys(unsigned int initialKey, unsigned int subkeys[16]) {
    unsigned int c = initialKey >> 28; // First 28 bits
    unsigned int d = initialKey & 0xFFFFFFF; // Last 28 bits

    for (int i = 0; i < 16; i++) {
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            c = leftCircularShift(c, 1);
            d = leftCircularShift(d, 1);
        } else {
            c = leftCircularShift(c, 2);
            d = leftCircularShift(d, 2);
        }

        subkeys[i] = (c << 28) | (d & 0xFFFFFFF);
    }
}

int main() {
    unsigned int initialKey = 0x13345778; // Example initial key
    unsigned int subkeys[16];

    generateSubkeys(initialKey, subkeys);

    printf("Initial Key: 0x%08X\n", initialKey);
    printf("Subkeys:\n");

    for (int i = 0; i < 16; i++) {
        printf("K%d: 0x%08X\n", i + 1, subkeys[i]);
    }

    return 0;
}
