#include <stdio.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int gcd(int a, int b) {
    while (b > 0) {
        a = a % b;
        a = a + b;
        b = a - b;
        a = a - b;
    }
    return a;
}

int is_prime(long long n) {
    if (n == 2) return 1;
    if (n < 2 || n % 2 == 0) return 0;
    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return 0;
    return 1;
}

long long discrete_log(long long a, long long b, long long p) {
    if (p <= 1 || !is_prime(p)) return -1;
    if (a <= 0 || b <= 0) return -1;

    for (long long i = 0; i < p; i++) {
        if (mod_pow(a, i, p) == b % p)
            return i;
    }
    return -1;
}

int main() {
    long long a, b, p;
    const char *result[3] = {
        "invalid: p must be prime, a and b must be positive",
        "invalid: a must be a primitive root of p",
        "computed discrete logarithm"
    };

    printf("==============================\n");
    printf("     Discrete Logarithm Calculator Program\n");
    printf("==============================\n");

    printf("Enter the base (a, a primitive root): ");
    scanf("%lld", &a);

    printf("Enter the number (b): ");
    scanf("%lld", &b);

    printf("Enter the prime modulus (p): ");
    scanf("%lld", &p);

    long long log_value = discrete_log(a, b, p);
    int index = 2;

    if (log_value == -1) index = 0;

    printf("\nResult for a = %lld, b = %lld, p = %lld: %s\n", a, b, p, result[index]);

    if (log_value >= 0) {
        printf("dlog_%lld,%lld(%lld) = %lld\n", a, p, b, log_value);
        printf("Verification: %lld^%lld mod %lld = %lld\n",
               a, log_value, p, mod_pow(a, log_value, p));
    }

    printf("Note: b = a^i mod p, where i is the discrete logarithm.\n");

    return 0;
}
