#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8 // 64 bits (8 bytes)

// Function to perform DES encryption in ECB mode
void encryptECB(const char *plaintext, const char *key, char *ciphertext) {
    DES_key_schedule key_schedule;
    
    DES_set_key((DES_cblock *)key, &key_schedule);
    
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
        
        DES_ecb_encrypt((DES_cblock *)inputBlock, (DES_cblock *)outputBlock, &key_schedule, DES_ENCRYPT);
        
        // Copy ciphertext to the output buffer
        memcpy(ciphertext + blockStart, outputBlock, blockEnd - blockStart);
    }
}

// Function to perform DES decryption in ECB mode
void decryptECB(const char *ciphertext, const char *key, char *plaintext) {
    DES_key_schedule key_schedule;
    
    DES_set_key((DES_cblock *)key, &key_schedule);
    
    int length = strlen(ciphertext);
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
        memcpy(inputBlock, ciphertext + blockStart, blockEnd - blockStart);
        
        DES_ecb_encrypt((DES_cblock *)inputBlock, (DES_cblock *)outputBlock, &key_schedule, DES_DECRYPT);
        
        // Copy plaintext to the output buffer
        memcpy(plaintext + blockStart, outputBlock, blockEnd - blockStart);
    }
}

int main() {
    const char *plaintext = "Hello, this is a test message.";
    const char *key = "1234567890ABCDEF";
    char ciphertext[100];
    char decryptedText[100];

    encryptECB(plaintext, key, ciphertext);

    // Introducing an error in the transmitted ciphertext
    ciphertext[8] ^= 0x01; // Flipping a bit in the first block

    decryptECB(ciphertext, key, decryptedText);

    printf("Original Plaintext: %s\n", plaintext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);
    printf("Decrypted Plaintext with Error: %s\n", decryptedText);

    return 0;
}
