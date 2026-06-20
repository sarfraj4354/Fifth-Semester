#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
 
// Function to encrypt the text using Rail Fence Cipher
void rail_fence_encrypt(const char *text, int rails, char *encrypted) {
    int len = strlen(text);
    char fence[rails][len];
    memset(fence, 0, sizeof(fence)); // Clear the fence array

    int row = 0, dir = 1;

    // Fill the fence in zigzag pattern
    for (int i = 0; i < len; i++) {
        fence[row][i] = text[i];
        row += dir;

        if (row == rails - 1 || row == 0) {
            dir *= -1; // Change direction
        }
    }

    // Read the fence row by row
    int index = 0;
    for (int r = 0; r < rails; r++) {
        for (int c = 0; c < len; c++) {
            if (fence[r][c] != 0) {
                encrypted[index++] = fence[r][c];
            }
        }
    }

    encrypted[index] = '\0'; // Null-terminate the string
}

// Function to decrypt the text using Rail Fence Cipher
void rail_fence_decrypt(const char *encrypted, int rails, char *decrypted) {
    int len = strlen(encrypted);
    char fence[rails][len];
    memset(fence, 0, sizeof(fence)); // Clear the fence array

    int row = 0, dir = 1;

    // Mark positions in the fence
    for (int i = 0; i < len; i++) {
        fence[row][i] = '*';
        row += dir;

        if (row == rails - 1 || row == 0) {
            dir *= -1; // Change direction
        }
    }

    // Fill the marked positions with the encrypted text
    int index = 0;
    for (int r = 0; r < rails; r++) {
        for (int c = 0; c < len; c++) {
            if (fence[r][c] == '*' && index < len) {
                fence[r][c] = encrypted[index++];
            }
        }
    }

    // Read the fence in zigzag order
    row = 0;
    dir = 1;

    for (int i = 0; i < len; i++) {
        decrypted[i] = fence[row][i];
        row += dir;

        if (row == rails - 1 || row == 0) {
            dir *= -1; // Change direction
        }
    }

    decrypted[len] = '\0'; // Null-terminate the string
}

int main() {
    char text[100], encrypted[100], decrypted[100];
    int rails;

    printf("===========================\n");
    printf("    Rail Fence Cipher\n");
    printf("===========================\n");

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the number of rails: ");
    scanf("%d", &rails);

    if (rails < 2) {
        printf("\nInvalid number of rails! Must be at least 2.\n");
        return 1;
    }

    // Encrypt and decrypt the text
    rail_fence_encrypt(text, rails, encrypted);
    rail_fence_decrypt(encrypted, rails, decrypted);

    // Display results
    printf("\nOriginal Text: %s\n", text);
    printf("Encrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
