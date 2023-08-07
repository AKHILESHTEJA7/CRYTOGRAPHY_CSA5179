#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decryptAdditiveCipher(const char *ciphertext, int shift) {
    printf("Shift %d:\n", shift);
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char decrypted = ((ciphertext[i] - base + shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            printf("%c", decrypted);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n\n");
}

int main() {
    char ciphertext[1000]; // Adjust the size as needed
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    int topPlaintexts = 10;
    printf("Enter the number of top possible plaintexts to generate (default is 10): ");
    scanf("%d", &topPlaintexts);
    getchar(); // Clear the newline character from the buffer

    int frequencies[ALPHABET_SIZE] = {0};
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            frequencies[tolower(ciphertext[i]) - 'a']++;
        }
    }

    int mostFrequentIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > frequencies[mostFrequentIndex]) {
            mostFrequentIndex = i;
        }
    }

    int shift = (mostFrequentIndex + ALPHABET_SIZE - ('e' - 'a')) % ALPHABET_SIZE;

    printf("Assuming 'e' maps to the most frequent letter in the ciphertext (shift = %d).\n\n", shift);

    for (int i = 0; i < topPlaintexts; i++) {
        decryptAdditiveCipher(ciphertext, shift);
        shift = (shift + 1) % ALPHABET_SIZE;
    }

    return 0;
}
