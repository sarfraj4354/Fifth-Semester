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

bool is_primitive_root(long long g, long long p) {     
    if (p <= 1 || !is_prime(p)) return false;     
    if (gcd(g, p) != 1) return false;     

    for (long long i = 1; i < p - 1; i++) {         
        if (mod_pow(g, i, p) == 1) return false; 
    }     
    return mod_pow(g, p - 1, p) == 1; 
}  

void diffie_hellman(long long p, long long g, long long a, long long b) {     
    if (p <= 1 || !is_prime(p)) {         
        printf("Invalid: p must be prime\n"); 
        return;     
    }     

    if (!is_primitive_root(g, p)) {         
        printf("Invalid: g must be a primitive root of p\n");         
        return;     
    }     

    if (a <= 0 || b <= 0) {         
        printf("Invalid: private keys a and b must be positive\n");         
        return; 
    }     

    long long A = mod_pow(g, a, p);     
    long long B = mod_pow(g, b, p);     
    long long S_alice = mod_pow(B, a, p);     
    long long S_bob = mod_pow(A, b, p); 
 
    printf("========================================\n");     
    printf("     Diffie-Hellman Key Exchange\n");     
    printf("========================================\n");     

    printf("Public Prime (p): %lld\n", p);     
    printf("Public Primitive Root (g): %lld\n", g);     
    printf("Alice's Private Key (a): %lld\n", a);     
    printf("Bob's Private Key (b): %lld\n", b);     
    printf("Alice's Public Key (A = g^a mod p): %lld\n", A);     
    printf("Bob's Public Key (B = g^b mod p): %lld\n", B);     
    printf("Shared Secret (Alice, B^a mod p): %lld\n", S_alice);     
    printf("Shared Secret (Bob, A^b mod p): %lld\n", S_bob); 
 
    if (S_alice == S_bob) {         
        printf("Success: Shared secret key is %lld\n", S_alice); 
    } else {         
        printf("Error: Shared secrets do not match\n"); 
    } 
}  

int main() {     
    long long p, g, a, b; 
 
    printf("=========================================\n");     
    printf("     Diffie-Hellman Key Exchange Program\n");     
    printf("=========================================\n"); 
 
    printf("Enter the prime number (p): ");     
    scanf("%lld", &p); 
 
    printf("Enter the primitive root (g): ");     
    scanf("%lld", &g); 
 
    printf("Enter Alice's private key (a): ");     
    scanf("%lld", &a); 
 
    printf("Enter Bob's private key (b): ");     
    scanf("%lld", &b); 
 
    diffie_hellman(p, g, a, b); 
 
    return 0; 
}
