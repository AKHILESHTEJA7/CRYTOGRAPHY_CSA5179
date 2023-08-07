#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

typedef struct {
    char letter;
    int count;
} LetterFrequency;

void countLetterFrequencies(const char *text, int frequencies[ALPHABET_SIZE]) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            frequencies[index]++;
        }
    }
}

int compareLetterFrequencies(const void *a, const void *b) {
    return ((LetterFrequency *)b)->count - ((LetterFrequency *)a)->count;
}

int main() {
    char ciphertext[1000]; // Adjust the size as needed
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    int frequencies[ALPHABET_SIZE] = {0};
    countLetterFrequencies(ciphertext, frequencies);

    LetterFrequency letterFreq[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letterFreq[i].letter = 'a' + i;
        letterFreq[i].count = frequencies[i];
    }

    qsort(letterFreq, ALPHABET_SIZE, sizeof(LetterFrequency), compareLetterFrequencies);

    printf("Top 10 possible plaintexts:\n");
    for (int i = 0; i < 10; i++) {
        char key[ALPHABET_SIZE + 1];
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            key[letterFreq[j].letter - 'a'] = 'a' + (j + i) % ALPHABET_SIZE;
        }
        key[ALPHABET_SIZE] = '\0';

        printf("Key: %s\n", key);

        for (int j = 0; ciphertext[j]; j++) {
            if (isalpha(ciphertext[j])) {
                int index = tolower(ciphertext[j]) - 'a';
                printf("%c", isupper(ciphertext[j]) ? toupper(key[index]) : key[index]);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n\n");
    }

    return 0;
}
