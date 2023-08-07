#include <stdio.h>
#include <ctype.h>

// Function to encrypt using the affine Caesar cipher
char affineEncrypt(char p, int a, int b) {
    if (isalpha(p)) {
        int shift = (a * (toupper(p) - 'A') + b) % 26;
        return 'A' + shift;
    }
    return p; // Non-alphabetic characters remain unchanged
}

int main() {
    int a, b;
    char plaintext[100];
    char ciphertext[100];

    printf("Enter the value of 'a': ");
    scanf("%d", &a);

    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);

    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[length] = '\0';

    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
