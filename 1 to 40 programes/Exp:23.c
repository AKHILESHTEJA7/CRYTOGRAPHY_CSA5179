#include <stdio.h>
#include <stdint.h>

// S-DES key
uint8_t sdes_key[10] = {0x1F, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 01111 11101

// S-DES S-Box definitions
uint8_t sbox1[4][4] = {{0x1, 0x0, 0x3, 0x2}, {0x3, 0x2, 0x1, 0x0}, {0x0, 0x2, 0x1, 0x3}, {0x3, 0x1, 0x3, 0x2}};
uint8_t sbox2[4][4] = {{0x0, 0x1, 0x2, 0x3}, {0x2, 0x0, 0x1, 0x3}, {0x3, 0x0, 0x1, 0x0}, {0x2, 0x1, 0x0, 0x3}};

// Initial permutation
uint8_t initial_permutation[8] = {1, 5, 2, 0, 3, 7, 4, 6};

// Expansion permutation
uint8_t expansion_permutation[8] = {3, 0, 1, 2, 1, 2, 3, 0};

// S-DES functions
void initial_permute(uint8_t *data);
void expansion_permute(uint8_t *data);
void sbox_substitution(uint8_t *data);
void p4_permutation(uint8_t *data);
void xor_round_key(uint8_t *data, uint8_t *key);
void swap_nibbles(uint8_t *data);

int main() {
    uint8_t plaintext[8] = {0x01, 0x02, 0x04}; // 0000 0001 0000 0010 0000 0100
    uint8_t counter[8] = {0x00, 0x00, 0x00}; // Counter mode starting at 0000 0000

    // Encrypt plaintext using S-DES in counter mode
    for (int i = 0; i < 3; i++) {
        xor_round_key(&plaintext[i], &counter[i]);
        initial_permute(&plaintext[i]);
        expansion_permute(&plaintext[i]);
        sbox_substitution(&plaintext[i]);
        p4_permutation(&plaintext[i]);
        xor_round_key(&plaintext[i], &counter[i]);
        swap_nibbles(&plaintext[i]);
        xor_round_key(&plaintext[i], &counter[i]);
    }

    // Display encrypted ciphertext
    printf("Encrypted Ciphertext: ");
    for (int i = 0; i < 3; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    // Decrypt ciphertext using S-DES in counter mode
    for (int i = 0; i < 3; i++) {
        xor_round_key(&plaintext[i], &counter[i]);
        swap_nibbles(&plaintext[i]);
        xor_round_key(&plaintext[i], &counter[i]);
        p4_permutation(&plaintext[i]);
        sbox_substitution(&plaintext[i]);
        expansion_permute(&plaintext[i]);
        initial_permute(&plaintext[i]);
        xor_round_key(&plaintext[i], &counter[i]);
    }

    // Display decrypted plaintext
    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 3; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    return 0;
}

void initial_permute(uint8_t *data) {
    uint8_t temp = 0;
    for (int i = 0; i < 8; i++) {
        temp |= (((*data) >> (7 - initial_permutation[i])) & 0x01) << (7 - i);
    }
    *data = temp;
}

void expansion_permute(uint8_t *data) {
    uint8_t temp = 0;
    for (int i = 0; i < 8; i++) {
        temp |= (((*data) >> (7 - expansion_permutation[i])) & 0x01) << (7 - i);
    }
    *data = temp;
}

void sbox_substitution(uint8_t *data) {
    uint8_t row = ((*data) >> 4) & 0x02 | ((*data) & 0x01);
    uint8_t col = ((*data) >> 1) & 0x03;
    *data = (sbox1[row][col] << 2) | sbox2[row][col];
}

void p4_permutation(uint8_t *data) {
    uint8_t temp = 0;
    temp |= ((*data) & 0x08) >> 1;
    temp |= ((*data) & 0x02) << 1;
    temp |= ((*data) & 0x01) << 3;
    temp |= ((*data) & 0x04) >> 1;
    *data = temp;
}

void xor_round_key(uint8_t *data, uint8_t *key) {
    *data ^= *key;
}

void swap_nibbles(uint8_t *data) {
    *data = ((*data) << 4) | ((*data) >> 4);
}
