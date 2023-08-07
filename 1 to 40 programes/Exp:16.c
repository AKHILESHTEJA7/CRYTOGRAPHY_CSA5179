#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Expected letter frequencies in English text (percentage)
const double englishFreq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.361, 0.150, 1.974, 0.074
};

// Function to calculate the sum of squared differences between two arrays
double calculateDiff(const double freq1[], const double freq2[], int length) {
    double diff = 0.0;
    for (int i = 0; i < length; i++) {
        double diffSquared = (freq1[i] - freq2[i]) * (freq1[i] - freq2[i]);
        diff += diffSquared;
    }
    return diff;
}

// Function to decrypt monoalphabetic substitution cipher with a given key
void decryptMonoalphabetic(const char *ciphertext, const char *key, char *plaintext) {
    int length = strlen(ciphertext);
    
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char baseChar = isupper(ciphertext[i]) ? 'A' : 'a';
            int index = tolower(ciphertext[i]) - 'a';
            plaintext[i] = key[index] + (baseChar - 'A');
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    
    plaintext[length] = '\0';
}

int main() {
    const char *ciphertext = "RDY LKDG DYS ZYMROK"; // Example ciphertext
    int numTopPlaintexts = 10;
    
    char key[26] = "QWERTYUIOPASDFGHJKLZXCVBNM"; // Initial key assumption
    
    double minDiff = 1e9; // Initialize a large value for minimum difference
    char bestKey[26];
    
    char plaintext[100];
    
    do {
        decryptMonoalphabetic(ciphertext, key, plaintext);
        
        // Calculate letter frequency for the decrypted text
        double freq[26] = {0.0};
        int totalLetters = 0;
        
        for (int i = 0; i < strlen(plaintext); i++) {
            if (isalpha(plaintext[i])) {
                int index = tolower(plaintext[i]) - 'a';
                freq[index]++;
                totalLetters++;
            }
        }
        
        for (int i = 0; i < 26; i++) {
            freq[i] = (freq[i] / totalLetters) * 100; // Convert to percentages
        }
        
        // Calculate the difference in letter frequencies
        double diff = calculateDiff(englishFreq, freq, 26);
        
        if (diff < minDiff) {
            minDiff = diff;
            strcpy(bestKey, key);
        }
        
    } while (next_permutation(key, key + 26));
    
    decryptMonoalphabetic(ciphertext, bestKey, plaintext);
    
    printf("Original Ciphertext: %s\n", ciphertext);
    printf("Best Key: %s\n", bestKey);
    printf("Decrypted Plaintext: %s\n", plaintext);
    
    return 0;
}
