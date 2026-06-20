#include <stdio.h> 
#include <math.h> 

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

int is_prime(long long n) {     
    if (n == 2) return 1;     
    if (n < 2 || n % 2 == 0) return 0;     

    for (long long i = 3; i * i <= n; i += 2) {         
        if (n % i == 0) return 0; 
    }     
    return 1; 
}  

int is_primitive_root(long long g, long long p) {     
    if (p <= 1 || !is_prime(p)) return 0;     
    if (gcd(g, p) != 1) return 0;     

    for (long long i = 1; i < p - 1; i++) {         
        if (mod_pow(g, i, p) == 1) return 0; 
    }     
    return mod_pow(g, p - 1, p) == 1; 
}  

void diffie_hellman_mitm(long long p, long long g, long long a, long long b, long long e1, long long e2) {     
    if (p <= 1 || !is_prime(p)) {         
        printf("Invalid: p must be prime\n");         
        return; 
    }     

    if (!is_primitive_root(g, p)) {         
        printf("Invalid: g must be a primitive root of p\n");         
        return; 
    }     

    if (a <= 0 || b <= 0 || e1 <= 0 || e2 <= 0) {         
        printf("Invalid: private keys a, b, e1, and e2 must be positive\n");         
        return; 
    }     

    long long A = mod_pow(g, a, p);     
    long long B = mod_pow(g, b, p);     
    long long E1 = mod_pow(g, e1, p);     
    long long E2 = mod_pow(g, e2, p);     
    long long S1 = mod_pow(E2, a, p);     
    long long S2 = mod_pow(E1, b, p);     
    long long S_eve_alice = mod_pow(A, e2, p);     
    long long S_eve_bob = mod_pow(B, e1, p); 

    printf("==================================================\n");     
    printf("     Diffie-Hellman Man-In-The-Middle Attack\n");     
    printf("==================================================\n");     

    printf("Public Prime (p): %lld\n", p);     
    printf("Public Primitive Root (g): %lld\n", g);     
    printf("Alice's Private Key (a): %lld\n", a);     
    printf("Bob's Private Key (b): %lld\n", b);     
    printf("Eve's Private Key for Bob (e1): %lld\n", e1);     
    printf("Eve's Private Key for Alice (e2): %lld\n", e2);     
    printf("Alice's Public Key (A): %lld\n", A);     
    printf("Bob's Public Key (B): %lld\n", B);     
    printf("Eve's Public Key for Bob (E1): %lld\n", E1);     
    printf("Eve's Public Key for Alice (E2): %lld\n", E2);     
    printf("Shared Secret (Alice with Eve): %lld\n", S1);     
    printf("Shared Secret (Bob with Eve): %lld\n", S2);     
    printf("Eve's Shared Secret with Alice: %lld\n", S_eve_alice);     
    printf("Eve's Shared Secret with Bob: %lld\n", S_eve_bob); 

    if (S1 == S_eve_alice && S2 == S_eve_bob) {         
        printf("Success: Eve has established shared secrets with both Alice and Bob\n"); 
    } else {         
        printf("Error: Shared secrets do not match\n"); 
    } 
}  

int main() {     
    long long p, g, a, b, e1, e2; 
 
    printf("==================================================\n");     
    printf("     Diffie-Hellman Man-In-The-Middle Program\n");     
    printf("==================================================\n"); 
 
    printf("Enter the prime number (p): ");     
    scanf("%lld", &p); 
 
    printf("Enter the primitive root (g): ");     
    scanf("%lld", &g); 
 
    printf("Enter Alice's private key (a): ");     
    scanf("%lld", &a); 
 
    printf("Enter Bob's private key (b): ");     
    scanf("%lld", &b); 
 
    printf("Enter Eve's private key for Bob (e1): ");     
    scanf("%lld", &e1); 
 
    printf("Enter Eve's private key for Alice (e2): ");     
    scanf("%lld", &e2); 
 
    diffie_hellman_mitm(p, g, a, b, e1, e2); 
 
    return 0; 
}
