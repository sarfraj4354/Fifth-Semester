#include <stdio.h> 
 
// Function to compute GCD of two numbers using Euclidean algorithm
int gcd(int a, int b) {     
    while (b > 0) {         
        a = a % b;         
        a = a + b;         
        b = a - b;         
        a = a - b; 
    }     
    return a; 
} 
 
// Function to compute Euler's totient function phi(n)
int euler_totient(int n) {     
    int result = n;     

    for (int i = 2; i * i <= n; i++) {         
        if (n % i == 0) {             
            while (n % i == 0) {                 
                n = n / i; 
            }             
            result = result - result / i; 
        }     
    }     

    if (n > 1) {         
        result = result - result / n; 
    }     

    return result; 
} 
 
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
 
// Function to demonstrate Euler's Theorem
long long euler_theorem(int a, int n) {     
    if (n <= 0) return -1;  // Invalid modulus     
    if (a <= 0) return -2;  // Invalid base     
    if (gcd(a, n) != 1) return -3;  // a and n not coprime 
 
    int phi = euler_totient(n);     
    return mod_pow(a, phi, n); 
}  

int main() {     
    int a, n;     
    const char* results[] = { 
        "Invalid: modulus must be positive", 
        "Invalid: base must be positive", 
        "Invalid: a and n must be coprime", 
        "1 (Euler's Theorem holds)" 
    };      

    printf("=============================================\n");     
    printf("     Euler's Theorem Demonstration Program\n");     
    printf("=============================================\n"); 
 
    printf("Enter the base (a): ");     
    scanf("%d", &a); 

    printf("Enter the modulus (n): ");     
    scanf("%d", &n); 
 
    long long computation = euler_theorem(a, n);     
    int index = 3;  // Default: theorem holds     

    if (computation == -1) index = 0;     
    else if (computation == -2) index = 1;     
    else if (computation == -3) index = 2; 
 
    printf("\nResult for a = %d, n = %d: %s\n", a, n, results[index]);     

    if (computation >= 0) {         
        printf("Computed value: %d^phi(%d) mod %d = %lld\n", a, n, n, computation); 
    }     

    printf("Note: Euler's Theorem applies only if a and n are coprime.\n"); 
 
    return 0; 
}
