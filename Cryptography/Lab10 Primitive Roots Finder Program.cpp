#include <stdio.h> 
#include <stdbool.h> 
 
int gcd(int a, int b) {     
    while (b > 0) {         
        a = a % b;         
        a = a + b;         
        b = a - b;         
        a = a - b; 
    }     
    return a; 
}  

long long mod_pow(long long base, long long exp, long long mod) {     
    long long result = 1;     
    base = base % mod;     

    while (exp > 0) {         
        if (exp % 2 == 1)             
            result = (result * base) % mod;         
        base = (base * base) % mod;         
        exp = exp / 2; 
    }     
    return result; 
}  

bool is_prime(long long n) {     
    if (n == 2) return true;     
    if (n < 2 || n % 2 == 0) return false;     

    for (long long i = 3; i * i <= n; i += 2) {         
        if (n % i == 0) return false; 
    }     
    return true; 
}  

void find_primitive_roots(long long p) {     
    if (p <= 1) {         
        printf("Input must be a positive integer greater than 1.\n");         
        return; 
    }     

    if (!is_prime(p)) { 
        printf("Input %lld is not prime. Primitive roots exist only for prime numbers.\n", p);         
        return; 
    }     

    if (p == 2) {         
        printf("Primitive root of 2: 1\n");         
        return; 
    }          
 
    int found = 0;     
    printf("Primitive roots of %lld:\n", p);     

    for (long long a = 1; a < p; a++) {         
        int is_primitive = 1;         

        for (long long i = 1; i < p - 1; i++) {             
            if (mod_pow(a, i, p) == 1) {                 
                is_primitive = 0;                 
                break; 
            } 
        } 

        if (is_primitive && mod_pow(a, p - 1, p) == 1) {             
            printf("%lld ", a);             
            found++; 
        }     
    }     

    if (found == 0) {         
        printf("None found (unexpected for a prime number).\n"); 
    } else {         
        printf("\nTotal primitive roots: %d\n", found); 
    } 
}  

int main() {     
    long long p; 
 
    printf("========================================\n");     
    printf("     Primitive Roots Finder Program\n");     
    printf("========================================\n"); 
 
    printf("Enter a prime number (p): ");     
    scanf("%lld", &p); 
 
    find_primitive_roots(p); 
 
    printf("Note: A number a is a primitive root of p if a^1, a^2, ..., a^(p-1) mod p are distinct.\n"); 
 
    return 0; 
}
