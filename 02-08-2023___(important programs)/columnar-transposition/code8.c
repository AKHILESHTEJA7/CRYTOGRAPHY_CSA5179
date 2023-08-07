#include <stdio.h>
#include <string.h>


void columnarTranspositionEncrypt(char message[], char key[]) {
    int messageLen = strlen(message);
    int keyLen = strlen(key);
    int rows = (messageLen + keyLen - 1) / keyLen; 

    char transpositionTable[rows][keyLen];
    int i, j, k = 0;

   
    for (i = 0; i < rows; i++) {
        for (j = 0; j < keyLen; j++) {
            if (k < messageLen)
                transpositionTable[i][j] = message[k++];
            else
                transpositionTable[i][j] = ' ';
        }
    }

   
    for (i = 0; i < keyLen; i++) {
        int col = key[i] - '0' - 1;
        for (j = 0; j < rows; j++) {
            printf("%c", transpositionTable[j][col]);
        }
    }
    printf("\n");
}

int main() {
    char message[100], key[100];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key for columnar transposition: ");
    fgets(key, sizeof(key), stdin);

   
    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    printf("\nEncrypted message: ");
    columnarTranspositionEncrypt(message, key);

    return 0;
}
