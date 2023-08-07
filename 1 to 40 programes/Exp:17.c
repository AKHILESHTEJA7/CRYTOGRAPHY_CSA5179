#include <stdio.h>

// Function to perform a right circular shift on a value
unsigned int rightCircularShift(unsigned int value, int shift) {
    return (value >> shift) | (value << (32 - shift));
}

// Function to generate decryption subkeys in reverse order
void generateDecryptionSubkeys(unsigned int keys[16], unsigned int initialKey) {
    unsigned int currentKey = initialKey;
    
    for (int i = 15; i >= 0; i--) {
        keys[i] = currentKey;
        currentKey = rightCircularShift(currentKey, i);
    }
}

int main() {
    unsigned int initialKey = 0x13345778; // Example initial key
    unsigned int decryptionKeys[16];

    generateDecryptionSubkeys(decryptionKeys, initialKey);

    printf("Initial Key: 0x%08X\n", initialKey);
    printf("Decryption Subkeys:\n");

    for (int i = 0; i < 16; i++) {
        printf("K%d: 0x%08X\n", i + 1, decryptionKeys[i]);
    }

    return 0;
}
