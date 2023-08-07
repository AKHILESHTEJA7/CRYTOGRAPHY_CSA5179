#include<stdio.h>
char monocipher_encr(char);
char alpha[27][3] = { { 'a', 'b' }, { 'b', 'c' }, { 'c', 'd' }, { 'd', 'e' }, {
        'e', 'f' }, { 'f', 'g' }, { 'g', 'h' }, { 'h', 'i' }, { 'i', 'j' }, {
        'j', 'k' }, { 'k', 'l' }, { 'l', 'm' }, { 'm', 'n' }, { 'n', 'o' }, {
        'o', 'p' }, { 'p', 'q' }, { 'q', 'r' }, { 'r', 's' }, { 's', 't' }, {
        't', 'u' }, { 'u', 'v' }, { 'v', 'w' }, { 'w', 'x' }, { 'x', 'y' }, {
        'y', 'z' }, { 'z', 'a' } };
char str[20];
int main() {
    char str[20], str2[20];
    int i;
    printf("\n Enter String..");
    gets(str);
    for (i = 0; str[i]; i++) {
        str2[i] = monocipher_encr(str[i]);
    }
    str2[i] = '\0';
    printf("\n Before Decryption..%s", str);
    printf("\n After Decryption..%s\n", str2);
}
char monocipher_encr(char a) {
    int i;
    for (i = 0; i < 27; i++) {
        if (a == alpha[i][0])
            break;
    }
    return alpha[i][1];
}
