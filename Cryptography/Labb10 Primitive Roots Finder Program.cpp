#include <stdio.h>

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

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
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

void primitive_roots(long long p) {
    if (!is_prime(p)) {
        printf("Input must be prime\n");
        return;
    }

    if (p == 2) {
        printf("1\n");
        return;
    }

    for (long long a = 1; a < p; a++) {
        int ok = 1;

        for (long long i = 1; i < p - 1; i++) {
            if (mod_pow(a, i, p) == 1) {
                ok = 0;
                break;
            }
        }

        if (ok && mod_pow(a, p - 1, p) == 1)
            printf("%lld ", a);
    }

    printf("\n");
}

int main() {
    long long p;

    printf("Enter prime number: ");
    scanf("%lld", &p);

    primitive_roots(p);

    return 0;
}
