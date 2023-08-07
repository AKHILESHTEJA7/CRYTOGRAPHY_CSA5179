#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8 // 64 bits (8 bytes)

// Function to perform 3DES encryption in CBC mode
void encrypt3DESCBC(const char *plaintext, const char *key1, const char *key2, const char *iv, char *ciphertext) {
    DES_key_schedule key1_schedule, key2_schedule;
    DES_cblock ivec;

    DES_set_key((DES_cblock *)key1, &key1_schedule);
    DES_set_key((DES_cblock *)key2, &key2_schedule);
    memcpy(ivec, iv, sizeof(ivec));

    int length = strlen(plaintext);
    int numBlocks = (length + BLOCK_SIZE - 1) / BLOCK_SIZE;
    char inputBlock[BLOCK_SIZE];
    char outputBlock[BLOCK_SIZE];

    for (int i = 0; i < numBlocks; i++) {
        int blockStart = i * BLOCK_SIZE;
        int blockEnd = blockStart + BLOCK_SIZE;
        if (blockEnd > length) {
            blockEnd = length;
        }

        memset(inputBlock, 0, BLOCK_SIZE);
        memcpy(inputBlock, plaintext + blockStart, blockEnd - blockStart);

        // XOR input block with previous ciphertext or IV
        for (int j = 0; j < BLOCK_SIZE; j++) {
            inputBlock[j] ^= ivec[j];
        }

        DES_ncbc_encrypt(inputBlock, outputBlock, BLOCK_SIZE, &key1_schedule, &ivec, DES_ENCRYPT);
        DES_ncbc_encrypt(outputBlock, outputBlock, BLOCK_SIZE, &key2_schedule, &ivec, DES_DECRYPT);

        // Copy ciphertext to the output buffer
        memcpy(ciphertext + blockStart, outputBlock, blockEnd - blockStart);
        memcpy(ivec, outputBlock, BLOCK_SIZE);
    }
}

int main() {
    const char *plaintext = "Hello, this is a test message.";
    const char *key1 = "1234567890ABCDEF";
    const char *key2 = "FEDCBA0987654321";
    const char *iv = "0000000000000000";
    char ciphertext[100];

    encrypt3DESCBC(plaintext, key1, key2, iv, ciphertext);

    printf("Original Plaintext: %s\n", plaintext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
