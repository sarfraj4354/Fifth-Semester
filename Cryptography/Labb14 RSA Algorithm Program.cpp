#include <stdio.h>
#include <stdbool.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;

    while (exp) {
        if (exp & 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

long long mod_inverse(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;

    while (new_r) {
        long long q = r / new_r;

        long long temp = t;
        t = new_t;
        new_t = temp - q * new_t;

        temp = r;
        r = new_r;
        new_r = temp - q * new_r;
    }

    if (r > 1)
        return -1;

    if (t < 0)
        t += phi;

    return t;
}

void rsa(long long p, long long q, long long e, long long m) {
    if (!is_prime(p) || !is_prime(q)) {
        printf("Invalid: p and q must be prime\n");
        return;
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    if (e <= 1 || e >= phi) {
        printf("Invalid: e must satisfy 1 < e < phi(n)\n");
        return;
    }

    if (gcd(e, phi) != 1) {
        printf("Invalid: e must be coprime with phi(n)\n");
        return;
    }

    if (m < 0 || m >= n) {
        printf("Invalid: message m must be in range [0,n)\n");
        return;
    }

    long long d = mod_inverse(e, phi);

    if (d == -1) {
        printf("Invalid: modular inverse does not exist\n");
        return;
    }

    long long c = mod_pow(m, e, n);
    long long dec = mod_pow(c, d, n);

    printf("Prime p: %lld\n", p);
    printf("Prime q: %lld\n", q);
    printf("Modulus n: %lld\n", n);
    printf("Totient phi(n): %lld\n", phi);
    printf("Public exponent e: %lld\n", e);
    printf("Private exponent d: %lld\n", d);
    printf("Original message m: %lld\n", m);
    printf("Encrypted ciphertext c: %lld\n", c);
    printf("Decrypted message: %lld\n", dec);

    if (m == dec)
        printf("Success: Decryption matches original\n");
    else
        printf("Error: Decryption failed\n");
}

int main() {
    long long p, q, e, m;

    printf("Enter first prime number (p): ");
    scanf("%lld", &p);

    printf("Enter second prime number (q): ");
    scanf("%lld", &q);

    printf("Enter public exponent (e): ");
    scanf("%lld", &e);

    printf("Enter message (m): ");
    scanf("%lld", &m);

    rsa(p, q, e, m);

    return 0;
}
