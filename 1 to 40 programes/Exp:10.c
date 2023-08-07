#include <stdio.h>
#include <string.h>

#define SIZE 5

void createPlayfairMatrix(char matrix[SIZE][SIZE], const char *sequence) {
    int sequenceLength = strlen(sequence);
    int index = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (index < sequenceLength) {
                matrix[i][j] = sequence[index++];
            }
        }
    }
}

void printPlayfairMatrix(const char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    const char *sequence = "MFHIJKUNOPQZVWXYELARGDSTBC";
    char playfairMatrix[SIZE][SIZE];

    createPlayfairMatrix(playfairMatrix, sequence);

    printf("Playfair Matrix:\n");
    printPlayfairMatrix(playfairMatrix);

    return 0;
}
