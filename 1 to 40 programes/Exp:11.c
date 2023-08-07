#include <stdio.h>
#include <math.h>

int main() {
    double possibleKeys = 1;
    int keyLength = 25;

    for (int i = keyLength; i >= 1; i--) {
        possibleKeys *= i;
    }

    printf("Approximate number of possible keys: %.0lf\n", possibleKeys);

    return 0;
}
