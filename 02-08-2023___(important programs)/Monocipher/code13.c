#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptMonoCipher(char *plaintext, char *ciphertext, char *key) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            int index = ch - base;
            ciphertext[i] = islower(ch) ? tolower(key[index]) : toupper(key[index]);
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[] = "ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba";
    char plaintext[] = "Hello, World!";
    char ciphertext[strlen(plaintext)];

    encryptMonoCipher(plaintext, ciphertext, key);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
