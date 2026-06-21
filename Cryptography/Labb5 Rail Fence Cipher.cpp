#include <stdio.h>
#include <string.h>

void encrypt(const char *text, int rails, char *enc) {
    int len = strlen(text), idx = 0, row = 0, dir = 1;
    char fence[rails][len];

    memset(fence, 0, sizeof(fence));

    for (int i = 0; i < len; i++) {
        fence[row][i] = text[i];
        row += dir;

        if (row == rails - 1 || row == 0)
            dir *= -1;
    }

    for (int r = 0; r < rails; r++)
        for (int c = 0; c < len; c++)
            if (fence[r][c])
                enc[idx++] = fence[r][c];

    enc[idx] = '\0';
}

void decrypt(const char *enc, int rails, char *dec) {
    int len = strlen(enc), idx = 0, row = 0, dir = 1;
    char fence[rails][len];

    memset(fence, 0, sizeof(fence));

    for (int i = 0; i < len; i++) {
        fence[row][i] = '*';
        row += dir;

        if (row == rails - 1 || row == 0)
            dir *= -1;
    }

    for (int r = 0; r < rails; r++)
        for (int c = 0; c < len; c++)
            if (fence[r][c] == '*')
                fence[r][c] = enc[idx++];

    row = 0;
    dir = 1;

    for (int i = 0; i < len; i++) {
        dec[i] = fence[row][i];
        row += dir;

        if (row == rails - 1 || row == 0)
            dir *= -1;
    }

    dec[len] = '\0';
}

int main() {
    char text[100], enc[100], dec[100];
    int rails;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    if (rails < 2) {
        printf("Invalid number of rails!\n");
        return 1;
    }

    encrypt(text, rails, enc);
    decrypt(enc, rails, dec);

    printf("Encrypted Text: %s\n", enc);
    printf("Decrypted Text: %s\n", dec);

    return 0;
}
