#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Caesar cipher encryption
void caesarEncrypt(const char *plaintext, int key, char *ciphertext) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char baseChar = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - baseChar + key) % 26) + baseChar;
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }

    ciphertext[length] = '\0';
}

// Function to perform Caesar cipher decryption
void caesarDecrypt(const char *ciphertext, int key, char *plaintext) {
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char baseChar = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - baseChar - key + 26) % 26) + baseChar;
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }

    plaintext[length] = '\0';
}

int main() {
    const char *message = "Hello, Caesar cipher!";
    char encrypted[100];
    char decrypted[100];

    printf("Original Message: %s\n\n", message);

    for (int key = 1; key <= 25; key++) {
        caesarEncrypt(message, key, encrypted);
        caesarDecrypt(encrypted, key, decrypted);
        printf("Key = %2d | Encrypted: %s | Decrypted: %s\n", key, encrypted, decrypted);
    }

    return 0;
}
