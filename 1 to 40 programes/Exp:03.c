#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to generate the Playfair matrix from a keyword
void generatePlayfairMatrix(const char *keyword, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int keywordLength = strlen(keyword);
    int matrixIndex = 0;
    int isUsed[26] = {0}; // To keep track of used letters

    // Fill in the keyword
    for (int i = 0; i < keywordLength; i++) {
        char currentChar = toupper(keyword[i]);
        if (currentChar >= 'A' && currentChar <= 'Z' && !isUsed[currentChar - 'A']) {
            matrix[matrixIndex / MATRIX_SIZE][matrixIndex % MATRIX_SIZE] = currentChar;
            isUsed[currentChar - 'A'] = 1;
            matrixIndex++;
        }
    }

    // Fill in the remaining alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && !isUsed[c - 'A']) {
            matrix[matrixIndex / MATRIX_SIZE][matrixIndex % MATRIX_SIZE] = c;
            isUsed[c - 'A'] = 1;
            matrixIndex++;
        }
    }
}

// Function to find the coordinates of a letter in the Playfair matrix
void findLetterCoordinates(const char matrix[MATRIX_SIZE][MATRIX_SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of letters using the Playfair matrix
void encryptPair(const char matrix[MATRIX_SIZE][MATRIX_SIZE], char letter1, char letter2, char *cipherPair) {
    int row1, col1, row2, col2;
    findLetterCoordinates(matrix, letter1, &row1, &col1);
    findLetterCoordinates(matrix, letter2, &row2, &col2);

    if (row1 == row2) {
        cipherPair[0] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
        cipherPair[1] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
    } else if (col1 == col2) {
        cipherPair[0] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
        cipherPair[1] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
    } else {
        cipherPair[0] = matrix[row1][col2];
        cipherPair[1] = matrix[row2][col1];
    }
}

// Function to encrypt plaintext using the Playfair cipher
void playfairEncrypt(const char matrix[MATRIX_SIZE][MATRIX_SIZE], const char *plaintext, char *ciphertext) {
    int length = strlen(plaintext);
    char cipherPair[2];

    for (int i = 0; i < length; i += 2) {
        char letter1 = plaintext[i];
        char letter2 = (i + 1 < length) ? plaintext[i + 1] : 'X'; // Pad with 'X' if odd length
        encryptPair(matrix, letter1, letter2, cipherPair);
        ciphertext[i] = cipherPair[0];
        ciphertext[i + 1] = cipherPair[1];
    }

    ciphertext[length] = '\0';
}

int main() {
    const char *keyword = "KEYWORD";
    const char *plaintext = "HELLOPLAYFAIR";
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char ciphertext[100];

    generatePlayfairMatrix(keyword, matrix);
    playfairEncrypt(matrix, plaintext, ciphertext);

    printf("Keyword: %s\n", keyword);
    printf("Plaintext: %s\n", plaintext);
    printf("Cipher Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
