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
int64_t mod_inverse(int64_t e, int64_t phi) {
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
    // Given public key values
    uint64_t e = 31;
    uint64_t n = 3599;

    // Find prime factors p and q through trial-and-error
    uint64_t p = 59;
    uint64_t q = 61;

    // Calculate Euler's totient function φ(n)
    uint64_t phi_n = (p - 1) * (q - 1);

    // Calculate the modular multiplicative inverse of e mod φ(n)
    int64_t d = mod_inverse(e, phi_n);

    printf("Private key (d): %lld\n", d);

    return 0;
}
