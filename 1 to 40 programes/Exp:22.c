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

// Initialization vector (IV)
uint8_t iv[8] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}; // 1010 1010

// S-DES functions
void initial_permute(uint8_t *data);
void expansion_permute(uint8_t *data);
void sbox_substitution(uint8_t *data);
void p4_permutation(uint8_t *data);
void xor_round_key(uint8_t *data, uint8_t *key);
void swap_nibbles(uint8_t *data);

int main() {
    uint8_t plaintext[8] = {0x01, 0x23}; // 0000 0001 0010 0011
    uint8_t ciphertext[8];
    uint8_t decrypted[8];
    uint8_t prev_ciphertext[8] = {0}; // Initialization vector

    // Encrypt plaintext using S-DES in CBC mode
    for (int i = 0; i < 2; i++) {
        xor_round_key(&plaintext[i], &prev_ciphertext[i]);
        initial_permute(&plaintext[i]);
        expansion_permute(&plaintext[i]);
        sbox_substitution(&plaintext[i]);
        p4_permutation(&plaintext[i]);
        xor_round_key(&plaintext[i], &prev_ciphertext[i]);
        swap_nibbles(&plaintext[i]);
        xor_round_key(&plaintext[i], &prev_ciphertext[i]);
        prev_ciphertext[i] = plaintext[i];
        ciphertext[i] = plaintext[i];
    }

    // Display encrypted ciphertext
    printf("Encrypted Ciphertext: ");
    for (int i = 0; i < 2; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt ciphertext using S-DES in CBC mode
    for (int i = 0; i < 2; i++) {
        uint8_t temp_ciphertext = ciphertext[i];
        xor_round_key(&ciphertext[i], &prev_ciphertext[i]);
        swap_nibbles(&ciphertext[i]);
        xor_round_key(&ciphertext[i], &prev_ciphertext[i]);
        p4_permutation(&ciphertext[i]);
        sbox_substitution(&ciphertext[i]);
        expansion_permute(&ciphertext[i]);
        initial_permute(&ciphertext[i]);
        xor_round_key(&ciphertext[i], &prev_ciphertext[i]);
        prev_ciphertext[i] = temp_ciphertext;
        decrypted[i] = ciphertext[i];
    }

    // Display decrypted plaintext
    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 2; i++) {
        printf("%02X ", decrypted[i]);
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
