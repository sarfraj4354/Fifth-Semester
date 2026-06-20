#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
 
void generate_matrix(const char *key, char matrix[5][5]) { 
    int used[26] = {0}; 
    char key_clean[26]; 
    int k = 0, index = 0; 
 
    for (int i = 0; key[i] != '\0'; i++) { 
        char c = tolower(key[i]); 
        if (c == 'j') c = 'i'; 
        if (isalpha(c) && !used[c - 'a']) { 
            key_clean[k++] = c; 
            used[c - 'a'] = 1; 
        } 
    }  
 
    for (char c = 'a'; c <= 'z'; c++) { 
        if (c == 'j') continue; 
        if (!used[c - 'a']) { 
            key_clean[k++] = c; 
            used[c - 'a'] = 1; 
        } 
    } 
 
    for (int i = 0; i < 5; i++) { 
        for (int j = 0; j < 5; j++) { 
            matrix[i][j] = key_clean[index++]; 
        } 
    } 
}  
 
void find_position(char c, char matrix[5][5], int *row, int *col) { 
    if (c == 'j') c = 'i'; 
    c = tolower(c); 
 
    for (int i = 0; i < 5; i++) { 
        for (int j = 0; j < 5; j++) { 
            if (matrix[i][j] == c) { 
                *row = i; 
                *col = j; 
                return; 
            } 
        } 
    } 
}  
 
void process_digraphs(const char *text, char matrix[5][5], int encrypt, char *result) { 
    char alpha_text[100] = ""; 
    int is_upper[100] = {0}; 
    int text_len = strlen(text), k = 0; 
 
    for (int i = 0; i < text_len; i++) { 
        if (isalpha(text[i])) { 
            alpha_text[k] = tolower(text[i]); 
            is_upper[k] = isupper(text[i]); 
            k++; 
        } 
    }  
 
    char digraphs[100] = ""; 
    int digraph_len = 0; 
 
    for (int i = 0; i < k; i++) { 
        digraphs[digraph_len++] = alpha_text[i]; 
 
        if (i + 1 < k && alpha_text[i] == alpha_text[i + 1]) { 
            digraphs[digraph_len++] = 'x'; 
        } else if (i + 1 == k) { 
            digraphs[digraph_len++] = 'x'; 
        } else { 
            digraphs[digraph_len++] = alpha_text[++i]; 
        } 
    }  
 
    int result_len = 0; 
 
    for (int i = 0; i < digraph_len; i += 2) { 
        char a = digraphs[i], b = digraphs[i + 1]; 
        int r1, c1, r2, c2; 
 
        find_position(a, matrix, &r1, &c1); 
        find_position(b, matrix, &r2, &c2); 
 
        if (r1 == r2) { 
            int shift = encrypt ? 1 : -1; 
            result[result_len++] = matrix[r1][(c1 + shift + 5) % 5]; 
            result[result_len++] = matrix[r2][(c2 + shift + 5) % 5]; 
        } else if (c1 == c2) { 
            int shift = encrypt ? 1 : -1; 
            result[result_len++] = matrix[(r1 + shift + 5) % 5][c1]; 
            result[result_len++] = matrix[(r2 + shift + 5) % 5][c2]; 
        } else { 
            result[result_len++] = matrix[r1][c2]; 
            result[result_len++] = matrix[r2][c1]; 
        } 
    }  
 
    result[result_len] = '\0'; 
}  
 
void playfair_cipher(const char *text, const char *key, int encrypt, char *output) { 
    char matrix[5][5]; 
    generate_matrix(key, matrix); 
    process_digraphs(text, matrix, encrypt, output); 
}  
 
int main() { 
    char text[100], key[100], encrypted[100], decrypted[100]; 
 
    printf("=========================\n"); 
    printf("    Playfair Cipher\n"); 
    printf("=========================\n"); 
 
    printf("Enter the text: "); 
    fgets(text, sizeof(text), stdin); 
    text[strcspn(text, "\n")] = '\0'; 
 
    printf("Enter the key (text): "); 
    scanf("%s", key); 
 
    playfair_cipher(text, key, 1, encrypted); // Encrypt the text 
    playfair_cipher(encrypted, key, 0, decrypted); // Decrypt the text 
 
    printf("\nOriginal Text: %s", text); 
    printf("\nEncrypted Text: %s", encrypted); 
    printf("\nDecrypted Text: %s\n", decrypted); 
 
    return 0; 
}
