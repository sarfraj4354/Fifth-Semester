#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

int char_to_int(char c) {     
    return tolower(c) - 'a'; 
}  

void extend_key(const char* text, const char* key, char* extended_key) {     
    int key_len = strlen(key);     
    int key_index = 0; 
    int i;     

    for (i = 0; text[i] != '\0'; i++) {         
        if (isalpha(text[i])) {             
            extended_key[i] = key[key_index % key_len];             
            key_index++;         
        } else {             
            extended_key[i] = text[i]; 
        }     
    }     

    extended_key[strlen(text)] = '\0'; 
}  

void vigenere_encrypt(const char* text, const char* key, char* result) {     
    char extended_key[100];     
    extend_key(text, key, extended_key); 

    int i;     

    for (i = 0; text[i] != '\0'; i++) {         
        if (isalpha(text[i])) {             
            char base = isupper(text[i]) ? 'A' : 'a';             
            int p = text[i] - base;             
            int k = char_to_int(extended_key[i]);             
            result[i] = base + (p + k) % 26; 
        } else {             
            result[i] = text[i]; 
        }     
    }     

    result[strlen(text)] = '\0'; 
}  

void vigenere_decrypt(const char* text, const char* key, char* result) {     
    char extended_key[100];     
    extend_key(text, key, extended_key); 

    int i;     

    for (i = 0; text[i] != '\0'; i++) {         
        if (isalpha(text[i])) {             
            char base = isupper(text[i]) ? 'A' : 'a';             
            int c = text[i] - base;             
            int k = char_to_int(extended_key[i]);             
            result[i] = base + (c - k + 26) % 26; 
        } else {             
            result[i] = text[i]; 
        }     
    }     

    result[strlen(text)] = '\0'; 
} 
 
int main() {     
    char text[100], key[100], encrypted[100], decrypted[100]; 

    printf("==============================\n");     
    printf("     Polyalphabetic Cipher\n");     
    printf("==============================\n"); 

    printf("Enter the text: ");     
    getchar(); // Clear input buffer     
    fgets(text, sizeof(text), stdin);     
    text[strcspn(text, "\n")] = '\0'; // Remove trailing newline 

    printf("Enter the key (text): ");     
    scanf("%s", key); 

    vigenere_encrypt(text, key, encrypted);     
    printf("\nEncrypted Text: %s\n", encrypted); 

    vigenere_decrypt(encrypted, key, decrypted);     
    printf("Decrypted Text: %s\n", decrypted); 

    return 0; 
}
