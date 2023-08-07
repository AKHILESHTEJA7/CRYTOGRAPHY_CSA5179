#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random key
void generateRandomKey(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 27; // Generate random numbers between 0 and 26
    }
}

// Function to perform one-time pad encryption
void encryptOneTimePadVigenere(const char *plaintext, const int *key, char *ciphertext) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char baseChar = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - baseChar + key[i]) % 26 + baseChar;
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }

    ciphertext[length] = '\0';
}

int main() {
    const char *plaintext = "hello world";
    int keyLength = strlen(plaintext);
    int key[keyLength];
    char ciphertext[100];

    srand(time(NULL)); // Seed the random number generator

    generateRandomKey(key, keyLength);
    encryptOneTimePadVigenere(plaintext, key, ciphertext);

    printf("Original Plaintext: %s\n", plaintext);
    printf("Generated Key: ");
    for (int i = 0; i < keyLength; i++) {
        printf("%d ", key[i]);
    }
    printf("\nEncrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
