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

void diffie(long long p, long long g, long long a, long long b) {
    if (!is_prime(p)) {
        printf("Invalid p\n");
        return;
    }

    if (!primitive_root(g, p)) {
        printf("Invalid g\n");
        return;
    }

    long long A = mod_pow(g, a, p);
    long long B = mod_pow(g, b, p);

    long long SA = mod_pow(B, a, p);
    long long SB = mod_pow(A, b, p);

    printf("Alice Public Key = %lld\n", A);
    printf("Bob Public Key = %lld\n", B);
    printf("Shared Secret (Alice) = %lld\n", SA);
    printf("Shared Secret (Bob) = %lld\n", SB);
}

int main() {
    long long p, g, a, b;

    printf("Enter p g a b: ");
    scanf("%lld%lld%lld%lld", &p, &g, &a, &b);

    diffie(p, g, a, b);

    return 0;
}
