#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to encrypt using the affine Caesar cipher
char encrypt(char p, int a, int b) {
    if (isalpha(p)) {
        if (islower(p)) {
            return ((a * (p - 'a') + b) % 26) + 'a';
        } else if (isupper(p)) {
            return ((a * (p - 'A') + b) % 26) + 'A';
        }
    }
    return p;
}

// Function to perform the affine Caesar cipher encryption on a string
void affineCaesarEncrypt(char *text, int a, int b) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = encrypt(text[i], a, b);
    }
}

int main() {
    char plaintext[1000];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the value of 'a': ");
    scanf("%d", &a);

    if (a % 2 == 0 || a % 13 == 0) {
        printf("'a' value is not suitable. It should be relatively prime to 26.\n");
        return 1;
    }

    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    affineCaesarEncrypt(plaintext, a, b);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
