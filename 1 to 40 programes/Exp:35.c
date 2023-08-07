#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Function to encrypt a single character using Vigenère cipher
char vigenereEncrypt(char plaintext, int key) {
    if (isalpha(plaintext)) {
        int base = islower(plaintext) ? 'a' : 'A';
        return ((plaintext - base + key) % 26) + base;
    }
    return plaintext;
}

// Function to perform Vigenère cipher encryption on a string using a key stream
void oneTimePadVigenereEncrypt(char *text, int *keyStream, int keyLength) {
    int keyIndex = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            text[i] = vigenereEncrypt(text[i], keyStream[keyIndex]);
            keyIndex = (keyIndex + 1) % keyLength;
        }
    }
}

int main() {
    char plaintext[1000];
    int key[1000]; // Key stream
    int keyLength;

    srand(time(NULL)); // Seed the random number generator with current time

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the length of the key: ");
    scanf("%d", &keyLength);

    // Generate the key stream with random numbers between 0 and 26
    for (int i = 0; i < keyLength; i++) {
        key[i] = rand() % 26;
        printf("%d ", key[i]);
    }
    printf("\n");

    oneTimePadVigenereEncrypt(plaintext, key, keyLength);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
