#include <stdio.h>
#include <ctype.h>

void caesar_encrypt(char *text, int shift, char *result) {
    int i = 0;

    while (text[i]) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            result[i] = base + (text[i] - base + shift) % 26;
        } else {
            result[i] = text[i];
        }
        i++;
    }
    result[i] = '\0';
}

void caesar_decrypt(char *text, int shift, char *result) {
    int i = 0;

    while (text[i]) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            result[i] = base + (text[i] - base - shift + 26) % 26;
        } else {
            result[i] = text[i];
        }
        i++;
    }
    result[i] = '\0';
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    int shift;

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the shift value: ");
    scanf("%d", &shift);

    caesar_encrypt(text, shift, encrypted);
    caesar_decrypt(encrypted, shift, decrypted);

    printf("Encrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
