#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the cipher sequence from the keyword
void generateCipherSequence(const char *keyword, char *cipherSequence) {
    int used[26] = {0};
    int keywordLength = strlen(keyword);
    int index = 0;

    // Copy the keyword to the cipher sequence
    strcpy(cipherSequence, keyword);

    // Mark letters in the keyword as used
    for (int i = 0; i < keywordLength; i++) {
        used[toupper(keyword[i]) - 'A'] = 1;
    }

    // Fill the remaining unused letters
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (!used[letter - 'A']) {
            cipherSequence[keywordLength + index] = letter;
            index++;
        }
    }
}

// Function to perform monoalphabetic encryption
void encryptMonoalphabetic(const char *plaintext, const char *cipherSequence, char *ciphertext) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char uppercaseChar = toupper(plaintext[i]);
            ciphertext[i] = cipherSequence[uppercaseChar - 'A'];
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters are not encrypted
        }
    }

    ciphertext[length] = '\0';
}

int main() {
    const char *keyword = "CIPHER";
    char cipherSequence[26];
    char plaintext[100];
    char ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    generateCipherSequence(keyword, cipherSequence);
    encryptMonoalphabetic(plaintext, cipherSequence, ciphertext);

    printf("Generated Cipher Sequence: %s\n", cipherSequence);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
