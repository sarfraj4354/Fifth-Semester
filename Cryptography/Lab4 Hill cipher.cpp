#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h> 
#include <string.h> 
 
// Convert character to position (0-25) or vice versa
int char_to_int(char c) {     
    return tolower(c) - 'a'; 
}  

char int_to_char(int n) {     
    n = (n % 26 + 26) % 26; // Ensure n is in 0-25     
    return 'a' + n; 
} 
 
// Compute GCD for checking matrix invertibility
int gcd(int a, int b) {     
    while (b) {         
        a %= b;         
        int temp = a;         
        a = b;         
        b = temp;     
    }     
    return a; 
} 
 
// Find modular multiplicative inverse of a modulo m
int mod_inverse(int a, int m) {     
    a = a % m;     
    for (int x = 1; x < m; x++) {         
        if ((a * x) % m == 1) {             
            return x; 
        }     
    }     
    return -1; // No inverse exists 
} 
 
// Check if 2x2 key matrix is valid (invertible modulo 26)
int is_valid_key(int key[2][2]) {     
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;     
    det = (det + 26) % 26; // Ensure non-negative     
    return gcd(det, 26) == 1; // Determinant must be coprime with 26 
} 
 
// Compute inverse of 2x2 key matrix modulo 26
void get_inverse_key(int key[2][2], int inv[2][2]) {     
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;     
    det = (det + 26) % 26; // Ensure non-negative     
    int det_inv = mod_inverse(det, 26); 
 
    inv[0][0] = (key[1][1] * det_inv) % 26;     
    inv[0][1] = (-key[0][1] * det_inv) % 26;     
    inv[1][0] = (-key[1][0] * det_inv) % 26;     
    inv[1][1] = (key[0][0] * det_inv) % 26; 
 
    // Ensure all elements are non-negative
    for (int i = 0; i < 2; i++) { 
        for (int j = 0; j < 2; j++) {             
            inv[i][j] = (inv[i][j] + 26) % 26; 
        } 
    } 
} 
 
// Encrypt or Decrypt text using Hill cipher (2x2 matrix)
void hill_cipher(const char *text, int key[2][2], char *result) {     
    int len = strlen(text);     
    char alpha_text[100] = "";     
    int k = 0; 
 
    // Extract alphabetic characters
    for (int i = 0; i < len; i++) {         
        if (isalpha(text[i])) {             
            alpha_text[k++] = tolower(text[i]); 
        } 
    } 
 
    // Pad with 'x' if needed
    if (k % 2 != 0) {         
        alpha_text[k++] = 'x'; 
    }     
    alpha_text[k] = '\0'; 
 
    // Process in pairs
    for (int i = 0; i < k; i += 2) {         
        int p1 = char_to_int(alpha_text[i]);         
        int p2 = char_to_int(alpha_text[i + 1]); 
 
        // Matrix multiplication: C = K * P mod 26
        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;         
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26; 
 
        result[i] = int_to_char(c1);         
        result[i + 1] = int_to_char(c2); 
    }     
    result[k] = '\0'; 
}  

int main() {     
    char text[100];     
    int key[2][2];     
    int inv_key[2][2];     
    char encrypted[100], decrypted[100]; 
 
    printf("=========================\n");     
    printf("       Hill Cipher\n");     
    printf("=========================\n"); 
 
    printf("Enter the text: ");     
    fgets(text, sizeof(text), stdin);     
    text[strcspn(text, "\n")] = '\0'; // Remove trailing newline 
 
    printf("Enter the 2x2 key matrix (4 numbers, row-wise):\n");     
    for (int i = 0; i < 2; i++) {         
        for (int j = 0; j < 2; j++) {             
            scanf("%d", &key[i][j]); 
        } 
    } 
 
    // Validate key
    if (!is_valid_key(key)) {         
        printf("\nInvalid key! Determinant must be coprime with 26.\n");         
        return 1; 
    } 
 
    // Encrypt the text
    hill_cipher(text, key, encrypted); 
 
    // Compute the inverse key
    get_inverse_key(key, inv_key); 
 
    // Decrypt the text
    hill_cipher(encrypted, inv_key, decrypted); 
 
    printf("\nOriginal Text: %s", text);     
    printf("\nEncrypted Text: %s", encrypted);     
    printf("\nDecrypted Text: %s\n", decrypted); 
 
    return 0; 
}
