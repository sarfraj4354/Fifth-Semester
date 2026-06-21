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

bool is_primitive_root(long long g, long long p) {
    if (!is_prime(p) || gcd(g, p) != 1)
        return false;

    for (long long i = 1; i < p - 1; i++)
        if (mod_pow(g, i, p) == 1)
            return false;

    return mod_pow(g, p - 1, p) == 1;
}

long long mod_inverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        long long q = a / m;

        long long t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

void elgamal(long long p, long long g, long long a, long long m, long long k) {
    if (!is_prime(p)) {
        printf("Invalid: p must be prime\n");
        return;
    }

    if (!is_primitive_root(g, p)) {
        printf("Invalid: g must be a primitive root of p\n");
        return;
    }

    if (a < 1 || a > p - 2) {
        printf("Invalid: private key a must be in range [1, p-2]\n");
        return;
    }

    if (m < 0 || m >= p) {
        printf("Invalid: message m must be in range [0, p)\n");
        return;
    }

    if (k < 1 || k > p - 2) {
        printf("Invalid: random k must be in range [1, p-2]\n");
        return;
    }

    long long h = mod_pow(g, a, p);
    long long c1 = mod_pow(g, k, p);
    long long c2 = (m * mod_pow(h, k, p)) % p;

    long long s = mod_pow(c1, a, p);
    long long dec = (c2 * mod_inverse(s, p)) % p;

    printf("Prime p: %lld\n", p);
    printf("Primitive root g: %lld\n", g);
    printf("Private key a: %lld\n", a);
    printf("Public key h: %lld\n", h);
    printf("Random k: %lld\n", k);
    printf("Original message m: %lld\n", m);
    printf("Ciphertext (c1, c2): (%lld, %lld)\n", c1, c2);
    printf("Decrypted message: %lld\n", dec);

    if (dec == m)
        printf("Success: Decryption matches original\n");
    else
        printf("Error: Decryption failed\n");
}

int main() {
    long long p, g, a, m, k;

    printf("Enter prime number (p): ");
    scanf("%lld", &p);

    printf("Enter primitive root (g): ");
    scanf("%lld", &g);

    printf("Enter private key (a): ");
    scanf("%lld", &a);

    printf("Enter message (m): ");
    scanf("%lld", &m);

    printf("Enter random integer (k): ");
    scanf("%lld", &k);

    elgamal(p, g, a, m, k);

    return 0;
}
