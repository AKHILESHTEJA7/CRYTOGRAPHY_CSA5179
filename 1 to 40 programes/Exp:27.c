#include <stdio.h>
#include <stdint.h>

// Simulated RSA encryption function
uint64_t rsa_encrypt(uint64_t plaintext, uint64_t e, uint64_t n) {
    // Simulate RSA encryption: ciphertext = (plaintext ^ e) mod n
    uint64_t ciphertext = 1;
    for (uint64_t i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

int main() {
    // Alice's public key (e, n)
    uint64_t e = 65537; // A large prime exponent
    uint64_t n = 1000000000000; // A very large modulus

    // Message: "HELLO"
    char message[] = "HELLO";
    uint64_t encrypted[5]; // Encrypted integers

    // Encrypt each character and store the encrypted integers
    for (int i = 0; i < 5; i++) {
        encrypted[i] = rsa_encrypt(message[i] - 'A', e, n);
    }

    // Display the encrypted integers
    printf("Encrypted integers: ");
    for (int i = 0; i < 5; i++) {
        printf("%llu ", encrypted[i]);
    }
    printf("\n");

    return 0;
}
