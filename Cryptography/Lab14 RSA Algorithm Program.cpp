#include <stdio.h>
#include <stdbool.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;

    return true;
}

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

long long mod_inverse(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;

    while (new_r != 0) {
        long long q = r / new_r;

        long long temp_t = t;
        t = new_t;
        new_t = temp_t - q * new_t;

        long long temp_r = r;
        r = new_r;
        new_r = temp_r - q * new_r;
    }

    if (r > 1) return -1;
    if (t < 0) t += phi;

    return t;
}

void rsa(long long p, long long q, long long e, long long m) {
    if (!is_prime(p) || !is_prime(q)) {
        printf("Invalid: p and q must be prime\n");
        return;
    }

    if (p <= 1 || q <= 1) {
        printf("Invalid: p and q must be greater than 1\n");
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
        printf("Invalid: message m must be in range [0, n)\n");
        return;
    }

    long long d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Invalid: modular inverse does not exist\n");
        return;
    }

    long long c = mod_pow(m, e, n);
    long long decrypted = mod_pow(c, d, n);

    printf("==============================\n");
    printf("     RSA Encryption and Decryption\n");
    printf("==============================\n");
    printf("Prime p: %lld\n", p);
    printf("Prime q: %lld\n", q);
    printf("Modulus n: %lld\n", n);
    printf("Totient phi(n): %lld\n", phi);
    printf("Public exponent e: %lld\n", e);
    printf("Private exponent d: %lld\n", d);
    printf("Original message m: %lld\n", m);
    printf("Encrypted ciphertext c: %lld\n", c);
    printf("Decrypted message: %lld\n", decrypted);

    if (m == decrypted)
        printf("Success: Decrypted message matches original\n");
    else
        printf("Error: Decryption failed\n");
}

int main() {
    long long p, q, e, m;

    printf("==============================\n");
    printf("     RSA Algorithm Program\n");
    printf("==============================\n");

    printf("Enter first prime number (p): ");
    scanf("%lld", &p);

    printf("Enter second prime number (q): ");
    scanf("%lld", &q);

    printf("Enter public exponent (e): ");
    scanf("%lld", &e);

    printf("Enter message to encrypt (m): ");
    scanf("%lld", &m);

    rsa(p, q, e, m);

    return 0;
}
