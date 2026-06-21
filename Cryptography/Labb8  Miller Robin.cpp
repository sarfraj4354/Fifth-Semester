#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int miller_rabin(long long n, int k) {
    if (n == 2)
        return 1;

    if (n < 2 || n % 2 == 0)
        return 0;

    long long d = n - 1;
    int s = 0;

    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 3);
        long long x = mod_pow(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        int flag = 0;

        for (int r = 0; r < s - 1; r++) {
            x = (x * x) % n;

            if (x == n - 1) {
                flag = 1;
                break;
            }
        }

        if (!flag)
            return 0;
    }

    return 1;
}

int main() {
    long long n;
    int k;

    printf("Enter number: ");
    scanf("%lld", &n);

    printf("Enter iterations: ");
    scanf("%d", &k);

    srand(time(NULL));

    printf("%lld is %s\n",
           n,
           miller_rabin(n, k) ? "prime" : "composite");

    return 0;
}
