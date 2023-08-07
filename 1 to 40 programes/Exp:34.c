#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// AES block size is 128 bits (16 bytes)
#define BLOCK_SIZE 16

// AES key size is 128 bits (16 bytes)
#define KEY_SIZE 16

// AES round key structure
typedef struct {
    uint8_t roundKey[176];
} AES_KEY;

// AES encryption function
void aes_encrypt(const uint8_t *input, const AES_KEY *key, uint8_t *output) {
    // Implement AES encryption here
    // This is just a placeholder function
    // You can use a library or your own AES implementation
}

// Function to perform padding on the input data
void add_padding(uint8_t *data, size_t data_length, size_t block_size) {
    size_t padding_length = block_size - (data_length % block_size);
    data[data_length] = 0x80; // Add 1 bit followed by zeros
    for (size_t i = data_length + 1; i < data_length + padding_length; i++) {
        data[i] = 0x00;
    }
}

// Electronic Codebook (ECB) encryption
void ecb_encrypt(const uint8_t *plaintext, size_t plaintext_length, const AES_KEY *key, uint8_t *ciphertext) {
    for (size_t i = 0; i < plaintext_length; i += BLOCK_SIZE) {
        aes_encrypt(plaintext + i, key, ciphertext + i);
    }
}

// Cipher Block Chaining (CBC) encryption
void cbc_encrypt(const uint8_t *plaintext, size_t plaintext_length, const AES_KEY *key, const uint8_t *iv, uint8_t *ciphertext) {
    uint8_t xor_result[BLOCK_SIZE];
    memcpy(xor_result, iv, BLOCK_SIZE);

    for (size_t i = 0; i < plaintext_length; i += BLOCK_SIZE) {
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            xor_result[j] ^= plaintext[i + j];
        }
        aes_encrypt(xor_result, key, ciphertext + i);
        memcpy(xor_result, ciphertext + i, BLOCK_SIZE);
    }
}

// Cipher Feedback (CFB) encryption
void cfb_encrypt(const uint8_t *plaintext, size_t plaintext_length, const AES_KEY *key, const uint8_t *iv, uint8_t *ciphertext) {
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (size_t i = 0; i < plaintext_length; i += BLOCK_SIZE) {
        aes_encrypt(feedback, key, feedback);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ feedback[j];
        }
        memcpy(feedback, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    // Define the plaintext and key
    uint8_t plaintext[] = "Hello, world! This is a test message.";
    uint8_t key[KEY_SIZE] = "ThisIsASecretKey";

    // Pad the plaintext
    size_t plaintext_length = strlen((char *)plaintext);
    size_t padded_length = (plaintext_length / BLOCK_SIZE + 1) * BLOCK_SIZE;
    uint8_t *padded_plaintext = (uint8_t *)malloc(padded_length);
    memcpy(padded_plaintext, plaintext, plaintext_length);
    add_padding(padded_plaintext, plaintext_length, BLOCK_SIZE);

    // Initialize the AES key
    AES_KEY aes_key;
    // You should initialize the AES key using the provided key material

    // Define the initialization vector (IV) for CBC and CFB modes
    uint8_t iv[BLOCK_SIZE] = "InitializationVec";

    // Allocate memory for ciphertexts
    uint8_t ecb_ciphertext[padded_length];
    uint8_t cbc_ciphertext[padded_length];
    uint8_t cfb_ciphertext[padded_length];

    // Perform encryption using different modes
    ecb_encrypt(padded_plaintext, padded_length, &aes_key, ecb_ciphertext);
    cbc_encrypt(padded_plaintext, padded_length, &aes_key, iv, cbc_ciphertext);
    cfb_encrypt(padded_plaintext, padded_length, &aes_key, iv, cfb_ciphertext);

    // Display ciphertexts
    printf("ECB Ciphertext: ");
    for (size_t i = 0; i < padded_length; i++) {
        printf("%02X", ecb_ciphertext[i]);
    }
    printf("\n");

    printf("CBC Ciphertext: ");
    for (size_t i = 0; i < padded_length; i++) {
        printf("%02X", cbc_ciphertext[i]);
    }
    printf("\n");

    printf("CFB Ciphertext: ");
    for (size_t i = 0; i < padded_length; i++) {
        printf("%02X", cfb_ciphertext[i]);
    }
    printf("\n");

    // Clean up memory
    free(padded_plaintext);

    return 0;
}
