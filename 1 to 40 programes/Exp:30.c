#include <stdio.h>
#include <string.h>
#include <stdint.h>

// AES block size is 128 bits (16 bytes)
#define BLOCK_SIZE 16

// Simulated AES encryption function
void aes_encrypt(const uint8_t *input, const uint8_t *key, uint8_t *output) {
    // Simulate AES encryption using XOR with key
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

// Function to compute the CBC MAC of a message X using key K
void cbc_mac(const uint8_t *X, const uint8_t *K, uint8_t *T) {
    uint8_t ciphertext[BLOCK_SIZE] = {0};

    // Encrypt the message X using CBC mode
    aes_encrypt(X, K, ciphertext);

    // Set the CBC MAC output
    memcpy(T, ciphertext, BLOCK_SIZE);
}

int main() {
    // Define the message X and key K
    uint8_t X[BLOCK_SIZE] = "OneBlockMessage";
    uint8_t K[BLOCK_SIZE] = "SecretKey";

    uint8_t T[BLOCK_SIZE];

    // Compute the CBC MAC for the one-block message X
    cbc_mac(X, K, T);

    printf("CBC MAC for X: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X", T[i]);
    }
    printf("\n");

    // Compute the XOR of X with T and append it to X
    uint8_t X_concatenated[2 * BLOCK_SIZE];
    memcpy(X_concatenated, X, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        X_concatenated[BLOCK_SIZE + i] = X[i] ^ T[i];
    }

    // Compute the CBC MAC for the two-block message X || (X ⊕ T)
    cbc_mac(X_concatenated, K, T);

    printf("CBC MAC for X || (X ⊕ T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X", T[i]);
    }
    printf("\n");

    return 0;
}
