#include <stdio.h>
#include <stdint.h>

// Function to calculate (base^exponent) % modulus
uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    uint64_t p = 23;  // Prime modulus
    uint64_t g = 5;   // Generator
    uint64_t secret_a = 6; // Alice's secret
    uint64_t secret_b = 15; // Bob's secret

    // Alice sends A = g^a mod p to Bob
    uint64_t A = mod_pow(g, secret_a, p);

    // Bob sends B = g^b mod p to Alice
    uint64_t B = mod_pow(g, secret_b, p);

    // Both Alice and Bob calculate the shared secret key
    uint64_t shared_secret_a = mod_pow(B, secret_a, p);
    uint64_t shared_secret_b = mod_pow(A, secret_b, p);

    printf("Shared secret key (Alice's perspective): %llu\n", shared_secret_a);
    printf("Shared secret key (Bob's perspective): %llu\n", shared_secret_b);

    return 0;
}
