#include <stdio.h>
#include <string.h>
#include <ctype.h>

int char_to_int(char c) {
    return tolower(c) - 'a';
}

void extend_key(const char *text, const char *key, char *ek) {
    int klen = strlen(key), j = 0;

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i]))
            ek[i] = key[(j++) % klen];
        else
            ek[i] = text[i];
    }

    ek[strlen(text)] = '\0';
}

void vigenere_encrypt(const char *text, const char *key, char *res) {
    char ek[100];

    extend_key(text, key, ek);

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            res[i] = base + ((text[i] - base) + char_to_int(ek[i])) % 26;
        } else {
            res[i] = text[i];
        }
    }

    res[strlen(text)] = '\0';
}

void vigenere_decrypt(const char *text, const char *key, char *res) {
    char ek[100];

    extend_key(text, key, ek);

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            res[i] = base + ((text[i] - base) - char_to_int(ek[i]) + 26) % 26;
        } else {
            res[i] = text[i];
        }
    }

    res[strlen(text)] = '\0';
}

int main() {
    char text[100], key[100], enc[100], dec[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the key: ");
    scanf("%s", key);

    vigenere_encrypt(text, key, enc);
    vigenere_decrypt(enc, key, dec);

    printf("Encrypted Text: %s\n", enc);
    printf("Decrypted Text: %s\n", dec);

    return 0;
}
