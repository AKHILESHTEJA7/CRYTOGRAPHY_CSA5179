#include <stdio.h>
#include <stdint.h>

// Calculate the greatest common divisor (GCD) using the Euclidean algorithm
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Calculate the modular multiplicative inverse using the extended Euclidean algorithm
uint64_t mod_inverse(uint64_t e, uint64_t phi) {
    int64_t d = 0, x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    while (phi > 0) {
        int64_t q = e / phi;
        int64_t r = e - q * phi;
        d = x2 - q * x1;
        e = phi;
        phi = r;
        x2 = x1;
        x1 = d;
        y2 = y1;
        y1 = e;
    }
    return y2;
}

int main() {
    // Modulus n
    uint64_t n = 3233;

    // Leaked private key d
    uint64_t leaked_d = 17;

    // Calculate Euler's totient function φ(n)
    uint64_t phi_n = n - 1;

    // Calculate the modular multiplicative inverse of leaked_d mod φ(n)
    uint64_t leaked_d_inverse = mod_inverse(leaked_d, phi_n);

    // Calculate new public and private keys using the same modulus
    uint64_t new_e = 65537; // New public exponent
    uint64_t new_d = leaked_d_inverse; // New private exponent

    printf("New public key (e): %llu\n", new_e);
    printf("New private key (d): %llu\n", new_d);

    return 0;
}
