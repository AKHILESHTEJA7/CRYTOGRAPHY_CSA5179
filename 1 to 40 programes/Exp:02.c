#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform monoalphabetic substitution encryption
void encryptMonoalphabetic(const char *plaintext, const char *cipherKey, char *ciphertext) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char uppercaseChar = toupper(plaintext[i]);
            ciphertext[i] = cipherKey[uppercaseChar - 'A'];
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters are not encrypted
        }
    }

    ciphertext[length] = '\0';
}

int main() {
    const char *plaintext = "HELLO WORLD";
    const char *cipherKey = "QWERTYUIOPASDFGHJKLZXCVBNM"; // Replace with your cipher key
    char ciphertext[100];

    encryptMonoalphabetic(plaintext, cipherKey, ciphertext);

    printf("Original Plaintext: %s\n", plaintext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
