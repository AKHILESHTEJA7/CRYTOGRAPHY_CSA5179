#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

// Function to perform Hill cipher encryption
void encryptHillCipher(const char *message, int key[SIZE][SIZE], char *ciphertext) {
    int length = strlen(message);
    int rows = length / SIZE + (length % SIZE != 0);
    int columns = SIZE;

    char plaintext[rows][columns];
    int cipherNum[rows][columns];

    // Initialize the plaintext matrix
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (index < length) {
                plaintext[i][j] = toupper(message[index]);
                index++;
            } else {
                plaintext[i][j] = 'X'; // Add padding if necessary
            }
        }
    }

    // Perform matrix multiplication for encryption
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cipherNum[i][j] = 0;
            for (int k = 0; k < columns; k++) {
                cipherNum[i][j] += (key[i][k] * (plaintext[k][j] - 'A'));
            }
            cipherNum[i][j] %= 26;
        }
    }

    // Convert numbers back to letters
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            ciphertext[index] = cipherNum[i][j] + 'A';
            index++;
        }
    }
    ciphertext[index] = '\0';
}

int main() {
    const char *message = "meet me at the usual place at ten rather than eight oclock";
    int key[SIZE][SIZE] = {
        {9, 4},
        {5, 7}
    };
    char ciphertext[100];

    encryptHillCipher(message, key, ciphertext);

    printf("Original Message: %s\n", message);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
