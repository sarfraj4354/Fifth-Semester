#include <stdio.h>

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long mod_pow(long long b, long long e, long long m) {
    long long r = 1;
    b %= m;

    while (e) {
        if (e & 1)
            r = (r * b) % m;

        b = (b * b) % m;
        e /= 2;
    }

    return r;
}

int is_prime(long long n) {
    if (n == 2)
        return 1;

    if (n < 2 || n % 2 == 0)
        return 0;

    for (long long i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;

    return 1;
}

int primitive_root(long long g, long long p) {
    if (!is_prime(p) || gcd(g, p) != 1)
        return 0;

    for (long long i = 1; i < p - 1; i++)
        if (mod_pow(g, i, p) == 1)
            return 0;

    return mod_pow(g, p - 1, p) == 1;
}

void mitm(long long p, long long g, long long a, long long b, long long e1, long long e2) {
    if (!is_prime(p) || !primitive_root(g, p)) {
        printf("Invalid input\n");
        return;
    }

    long long A = mod_pow(g, a, p);
    long long B = mod_pow(g, b, p);
    long long E1 = mod_pow(g, e1, p);
    long long E2 = mod_pow(g, e2, p);

    long long S1 = mod_pow(E2, a, p);
    long long S2 = mod_pow(E1, b, p);

    long long SEA = mod_pow(A, e2, p);
    long long SEB = mod_pow(B, e1, p);

    printf("Alice Public Key = %lld\n", A);
    printf("Bob Public Key = %lld\n", B);
    printf("E1 = %lld\n", E1);
    printf("E2 = %lld\n", E2);

    printf("Alice Secret = %lld\n", S1);
    printf("Bob Secret = %lld\n", S2);

    printf("Eve-Alice Secret = %lld\n", SEA);
    printf("Eve-Bob Secret = %lld\n", SEB);
}

int main() {
    long long p, g, a, b, e1, e2;

    printf("Enter p g a b e1 e2: ");
    scanf("%lld%lld%lld%lld%lld%lld", &p, &g, &a, &b, &e1, &e2);

    mitm(p, g, a, b, e1, e2);

    return 0;
}
