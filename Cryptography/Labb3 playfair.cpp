#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_matrix(const char *key, char m[5][5]) {
    int used[26] = {0}, k = 0, idx = 0;
    char temp[26];

    for (int i = 0; key[i]; i++) {
        char c = tolower(key[i]);

        if (c == 'j')
            c = 'i';

        if (isalpha(c) && !used[c - 'a']) {
            temp[k++] = c;
            used[c - 'a'] = 1;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j')
            continue;

        if (!used[c - 'a']) {
            temp[k++] = c;
            used[c - 'a'] = 1;
        }
    }

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            m[i][j] = temp[idx++];
}

void find_position(char c, char m[5][5], int *r, int *col) {
    if (c == 'j')
        c = 'i';

    c = tolower(c);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (m[i][j] == c) {
                *r = i;
                *col = j;
                return;
            }
        }
    }
}

void process(const char *text, char m[5][5], int enc, char *res) {
    char alpha[100] = "", dig[100] = "";
    int k = 0, d = 0;

    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i]))
            alpha[k++] = tolower(text[i]);
    }

    for (int i = 0; i < k; i++) {
        dig[d++] = alpha[i];

        if (i + 1 < k && alpha[i] == alpha[i + 1]) {
            dig[d++] = 'x';
        }
        else if (i + 1 == k) {
            dig[d++] = 'x';
        }
        else {
            dig[d++] = alpha[++i];
        }
    }

    int len = 0;

    for (int i = 0; i < d; i += 2) {
        int r1, c1, r2, c2;

        find_position(dig[i], m, &r1, &c1);
        find_position(dig[i + 1], m, &r2, &c2);

        if (r1 == r2) {
            int s = enc ? 1 : -1;

            res[len++] = m[r1][(c1 + s + 5) % 5];
            res[len++] = m[r2][(c2 + s + 5) % 5];
        }
        else if (c1 == c2) {
            int s = enc ? 1 : -1;

            res[len++] = m[(r1 + s + 5) % 5][c1];
            res[len++] = m[(r2 + s + 5) % 5][c2];
        }
        else {
            res[len++] = m[r1][c2];
            res[len++] = m[r2][c1];
        }
    }

    res[len] = '\0';
}

void playfair(const char *text, const char *key, int enc, char *out) {
    char m[5][5];

    generate_matrix(key, m);
    process(text, m, enc, out);
}

int main() {
    char text[100], key[100], enc[100], dec[100];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the key: ");
    scanf("%s", key);

    playfair(text, key, 1, enc);
    playfair(enc, key, 0, dec);

    printf("Original Text: %s\n", text);
    printf("Encrypted Text: %s\n", enc);
    printf("Decrypted Text: %s\n", dec);

    return 0;
}
