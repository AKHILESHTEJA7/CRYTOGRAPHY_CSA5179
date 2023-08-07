#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

void handleErrors() {
    // Handle OpenSSL errors here
    // This is a placeholder function
}

int main() {
    DES_key_schedule key_schedule;
    DES_cblock key;

    // Set your 56-bit key here (8 bytes)
    const unsigned char user_key[8] = "YourKey";

    // Initialize the key schedule
    if (DES_set_key_checked(&user_key, &key_schedule) != 0) {
        handleErrors();
        return 1;
    }

    // Set your plaintext here (64 bits)
    const unsigned char plaintext[8] = "PlainText";

    unsigned char ciphertext[8];

    // Encrypt the plaintext using DES
    DES_ecb_encrypt(&plaintext, &ciphertext, &key_schedule, DES_ENCRYPT);

    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
