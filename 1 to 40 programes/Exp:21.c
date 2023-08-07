#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16 // AES block size in bytes

// Function to encrypt using AES in ECB mode
void encryptECB(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, size_t length) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &aes_key);
    }
}

// Function to decrypt using AES in ECB mode
void decryptECB(const unsigned char *ciphertext, const unsigned char *key, unsigned char *plaintext, size_t length) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        AES_decrypt(ciphertext + i, plaintext + i, &aes_key);
    }
}

int main() {
    const unsigned char key[] = "0123456789ABCDEF"; // 128-bit key
    const unsigned char plaintext[] = "This is a test message for AES encryption.";
    unsigned char ciphertext[256];
    unsigned char decryptedText[256];
    size_t length = strlen((const char *)plaintext);

    // ECB mode encryption
    encryptECB(plaintext, key, ciphertext, length);

    // ECB mode decryption
    decryptECB(ciphertext, key, decryptedText, length);

    printf("Original Plaintext: %s\n", plaintext);
    printf("Encrypted Ciphertext (ECB mode): ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\nDecrypted Plaintext (ECB mode): %s\n", decryptedText);

    return 0;
}
