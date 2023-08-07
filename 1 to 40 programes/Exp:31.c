#include <stdio.h>
#include <stdint.h>

// Function to generate subkeys for CMAC
void generateSubkeys(uint8_t key[8], uint8_t subkey1[8], uint8_t subkey2[8]) {
    uint8_t L[8] = {0};
    uint8_t constant = 0x87; // For 64-bit block size, constant is 0x87

    // Generate L from the key
    aes_encrypt(L, key, L); // Assume AES encryption

    // Derive the first subkey
    if (L[0] & 0x80) {
        // If the most significant bit of L is 1, left shift and XOR constant
        for (int i = 0; i < 7; i++) {
            subkey1[i] = (L[i] << 1) | ((L[i + 1] & 0x80) >> 7);
        }
        subkey1[7] = (L[7] << 1) ^ constant;
    } else {
        // If the most significant bit of L is 0, only left shift
        for (int i = 0; i < 8; i++) {
            subkey1[i] = (L[i] << 1) | ((L[i + 1] & 0x80) >> 7);
        }
    }

    // Derive the second subkey
    if (subkey1[0] & 0x80) {
        for (int i = 0; i < 7; i++) {
            subkey2[i] = (subkey1[i] << 1) | ((subkey1[i + 1] & 0x80) >> 7);
        }
        subkey2[7] = (subkey1[7] << 1) ^ constant;
    } else {
        for (int i = 0; i < 8; i++) {
            subkey2[i] = (subkey1[i] << 1) | ((subkey1[i + 1] & 0x80) >> 7);
        }
    }
}

int main() {
    uint8_t key[8] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6}; // 64-bit key
    uint8_t subkey1[8], subkey2[8];

    generateSubkeys(key, subkey1, subkey2);

    printf("Subkey 1: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", subkey2[i]);
    }
    printf("\n");

    return 0;
}
