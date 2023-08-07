#include <stdio.h>

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to decrypt using the Hill cipher
void decryptHill(const char *ciphertext, int key[2][2], char *plaintext) {
    int a = key[0][0];
    int b = key[0][1];
    int c = key[1][0];
    int d = key[1][1];

    int det = (a * d) - (b * c);
    int modInverseDet = modInverse(det, 26);

    // Calculate the inverse of the key matrix
    int invKey[2][2] = {
        { d, -b },
        { -c, a }
    };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            invKey[i][j] = (invKey[i][j] * modInverseDet + 26) % 26;
        }
    }

    int length = strlen(ciphertext);
    for (int i = 0; i < length; i += 2) {
        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';

        int p1 = (invKey[0][0] * c1 + invKey[0][1] * c2) % 26;
        int p2 = (invKey[1][0] * c1 + invKey[1][1] * c2) % 26;

        plaintext[i] = p1 + 'A';
        plaintext[i + 1] = p2 + 'A';
    }

    plaintext[length] = '\0';
}

int main() {
    const char *ciphertext = "GYBNQKURP"; // Example ciphertext
    int knownPlaintext[2][2] = {
        { 2, 3 },
        { 1, 4 }
    }; // Known plaintext matrix

    char plaintext[100];

    decryptHill(ciphertext, knownPlaintext, plaintext);

    printf("Ciphertext: %s\n", ciphertext);
    printf("Known Plaintext Matrix:\n");
    printf("%d %d\n", knownPlaintext[0][0], knownPlaintext[0][1]);
    printf("%d %d\n", knownPlaintext[1][0], knownPlaintext[1][1]);
    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
