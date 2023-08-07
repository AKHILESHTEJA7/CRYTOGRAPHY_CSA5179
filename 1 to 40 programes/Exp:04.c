#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Vigenère cipher encryption
void vigenereEncrypt(const char *plaintext, const char *keyword, char *ciphertext) {
    int keywordLength = strlen(keyword);
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        char currentChar = plaintext[i];
        char keyChar = keyword[i % keywordLength];

        if (isalpha(currentChar)) {
            char baseChar = isupper(currentChar) ? 'A' : 'a';
            int shift = toupper(keyChar) - 'A';
            ciphertext[i] = ((currentChar - baseChar + shift) % 26) + baseChar;
        } else {
            ciphertext[i] = currentChar; // Non-alphabetic characters remain unchanged
        }
    }

    ciphertext[length] = '\0';
}

// Function to perform Vigenère cipher decryption
void vigenereDecrypt(const char *ciphertext, const char *keyword, char *plaintext) {
    int keywordLength = strlen(keyword);
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        char currentChar = ciphertext[i];
        char keyChar = keyword[i % keywordLength];

        if (isalpha(currentChar)) {
            char baseChar = isupper(currentChar) ? 'A' : 'a';
            int shift = toupper(keyChar) - 'A';
            plaintext[i] = ((currentChar - baseChar - shift + 26) % 26) + baseChar;
        } else {
            plaintext[i] = currentChar; // Non-alphabetic characters remain unchanged
        }
    }

    plaintext[length] = '\0';
}

int main() {
    const char *keyword = "KEY";
    const char *message = "Hello, Vigenere cipher!";
    char encrypted[100];
    char decrypted[100];

    printf("Original Message: %s\n\n", message);

    vigenereEncrypt(message, keyword, encrypted);
    printf("Encrypted: %s\n", encrypted);

    vigenereDecrypt(encrypted, keyword, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
