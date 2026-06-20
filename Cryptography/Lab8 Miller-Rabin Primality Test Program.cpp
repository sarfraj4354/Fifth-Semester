#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
// Function for modular exponentiation: computes (base^exp) % mod
long long mod_pow(long long base, long long exp, long long mod) {     
    long long result = 1;     
    base = base % mod;     

    while (exp > 0) {         
        if (exp % 2 == 1) {             
            result = (result * base) % mod; 
        }         
        base = (base * base) % mod;         
        exp = exp / 2; 
    }     

    return result; 
} 
 
// Function for Miller-Rabin primality test
int miller_rabin_test(long long n, int k) {     
    long long d = n - 1;     
    int s = 0; 
 
    // Handle edge cases     
    if (n == 2) return 1; // Prime     
    if (n < 2 || n % 2 == 0) return 0; // Composite 
 
    // Factor n - 1 into d * 2^s, where d is odd
    while (d % 2 == 0) {         
        d = d / 2;         
        s = s + 1; 
    } 
 
    // Perform k iterations of the test     
    for (int i = 0; i < k; i++) {         
        long long a = 2 + rand() % (n - 3);  // Random base a in [2, n-2]         
        long long x = mod_pow(a, d, n);      // Compute a^d % n 
 
        if (x == 1 || x == n - 1) continue; 
 
        int continueLoop = 0;         
        for (int r = 0; r < s - 1; r++) {             
            x = (x * x) % n;             
            if (x == n - 1) {                 
                continueLoop = 1;                 
                break; 
            }         
        }         

        if (continueLoop) continue; 
 
        return 0; // Composite 
    }     

    return 1; // Probably prime 
} 
 
int main() {     
    long long n;     
    int k;  

    printf("========================================\n");     
    printf("   Miller-Rabin Primality Test Program\n");     
    printf("========================================\n"); 
 
    printf("Enter the number to test for primality: ");     
    scanf("%lld", &n); 
 
    printf("Enter the number of iterations (e.g., 5 for good accuracy): ");     
    scanf("%d", &k); 
 
    // Seed the random number generator     
    srand(time(0)); 
 
    int is_prime = miller_rabin_test(n, k); 
 
    printf("\nNumber %lld is: %s\n", n, is_prime ? "prime" : "composite");     
    printf("Note: This is a probabilistic test; more iterations increase accuracy.\n"); 
 
    return 0; 
}
