#include <stdio.h>
#include <string.h>

#define SIZE 5

void createPlayfairGrid(char grid[SIZE][SIZE], const char *key) {
    int i, j, k = 0;
    int used[26] = {0};

    // Fill the key in the grid
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (*key != '\0') {
                if (!used[*key - 'A']) {
                    grid[i][j] = *key;
                    used[*key - 'A'] = 1;
                } else {
                    j--;
                }
                key++;
            } else {
                while (used[k]) {
                    k++;
                }
                grid[i][j] = 'A' + k;
                used[k] = 1;
            }
        }
    }
}

void findCharPosition(const char grid[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPlayfair(const char *cipherText, const char *key) {
    char grid[SIZE][SIZE];
    int i, row1, col1, row2, col2;
    createPlayfairGrid(grid, key);

    for (i = 0; i < strlen(cipherText); i += 2) {
        findCharPosition(grid, cipherText[i], &row1, &col1);
        findCharPosition(grid, cipherText[i + 1], &row2, &col2);

        if (row1 == row2) {
            col1 = (col1 - 1 + SIZE) % SIZE;
            col2 = (col2 - 1 + SIZE) % SIZE;
        } else if (col1 == col2) {
            row1 = (row1 - 1 + SIZE) % SIZE;
            row2 = (row2 - 1 + SIZE) % SIZE;
        } else {
            int temp = col1;
            col1 = col2;
            col2 = temp;
        }

        printf("%c%c", grid[row1][col1], grid[row2][col2]);
    }
    printf("\n");
}

int main() {
    const char *cipherText = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    const char *key = "PT109"; // Keyword used for encryption

    decryptPlayfair(cipherText, key);

    return 0;
}
