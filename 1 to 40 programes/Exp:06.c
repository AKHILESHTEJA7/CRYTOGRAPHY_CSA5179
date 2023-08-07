#include <stdio.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void decryptAffineCipher(char ciphertext[], int a, int b) {
    int a_inv = modInverse(a, 26);
    
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int encryptedValue = ciphertext[i] - 'A';
            int decryptedValue = (a_inv * (encryptedValue - b + 26)) % 26;
            char decryptedChar = decryptedValue + 'A';
            printf("%c", decryptedChar);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "YOUR_CIPHERTEXT_HERE";
    
    // Try all possible combinations of a and b
    for (int a = 1; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            decryptAffineCipher(ciphertext, a, b);
        }
    }
    
    return 0;
}
