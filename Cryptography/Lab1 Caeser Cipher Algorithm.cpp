#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 

void caesar_encrypt(char* text, int shift, char* result) {     
    int i = 0;     
    while (text[i] != '\0') {         
        if (isalpha(text[i])) {             
            char base = isupper(text[i]) ? 'A' : 'a';             
            result[i] = (base + (text[i] - base + shift) % 26); 
        } else {             
            result[i] = text[i]; 
        }         
        i++;     
    }     
    result[i] = '\0'; 
}  

void caesar_decrypt(char* text, int shift, char* result) {     
    int i = 0;     
    while (text[i] != '\0') {         
        if (isalpha(text[i])) {             
            char base = isupper(text[i]) ? 'A' : 'a';             
            result[i] = (base + (text[i] - base - shift + 26) % 26); 
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

    printf("==============================\n");     
    printf("     Caesar Cipher Program\n");     
    printf("==============================\n"); 

    printf("Enter the text: ");     
    scanf("%s", text); 

    printf("Enter the shift value (numeric key): ");     
    scanf("%d", &shift); 

    caesar_encrypt(text, shift, encrypted);     
    printf("\nEncrypted Text: %s\n", encrypted); 

    caesar_decrypt(encrypted, shift, decrypted);     
    printf("Decrypted Text: %s\n", decrypted); 

    return 0; 
}
