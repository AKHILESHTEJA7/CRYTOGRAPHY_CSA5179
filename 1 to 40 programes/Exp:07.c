#include <stdio.h>
#include <string.h>

char decryptChar(char cipherChar) {
    // Sample substitution key (modify this based on your knowledge)
    char substitutionKey[26] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    
    if (cipherChar >= 'A' && cipherChar <= 'Z') {
        int index = cipherChar - 'A';
        return substitutionKey[index];
    } else {
        return cipherChar;
    }
}

void decryptCiphertext(char ciphertext[]) {
    int length = strlen(ciphertext);
    
    for (int i = 0; i < length; i++) {
        char decryptedChar = decryptChar(ciphertext[i]);
        printf("%c", decryptedChar);
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    decryptCiphertext(ciphertext);
    
    return 0;
}
