#include <stdio.h>
#include <stdlib.h>

#define SIZE 2

int mod_inverse(int num, int mod) {
    int inverse = 1;
    while ((num * inverse) % mod != 1) {
        inverse++;
    }
    return inverse;
}

// Function to perform Hill cipher decryption
void decryptHillCipher(int key[SIZE][SIZE], const char *ciphertext, char *plaintext) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + 26) % 26;
    int det_inv = mod_inverse(det, 26);

    int inv_key[SIZE][SIZE] = {
        { key[1][1], -key[0][1]},
        {-key[1][0],  key[0][0]}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv_key[i][j] = (inv_key[i][j] * det_inv + 26) % 26;
        }
    }

    int length = strlen(ciphertext);
    int rows = length / SIZE + (length % SIZE != 0);
    int columns = SIZE;

    int cipherNum[rows][columns];

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cipherNum[i][j] = ciphertext[index] - 'A';
            index++;
        }
    }

    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int num = 0;
            for (int k = 0; k < columns; k++) {
                num += (inv_key[i][k] * cipherNum[k][j]) % 26;
            }
            plaintext[index] = (num % 26) + 'A';
            index++;
        }
    }
    plaintext[index] = '\0';
}

int main() {
    int key[SIZE][SIZE] = {
        {9, 4},
        {5, 7}
    };
    const char *ciphertext = "KWMFHVHTTOHJCFGNNV";
    char plaintext[100];

    decryptHillCipher(key, ciphertext, plaintext);

    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
