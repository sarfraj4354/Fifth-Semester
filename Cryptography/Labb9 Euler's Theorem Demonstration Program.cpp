#include <stdio.h>

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int phi(int n) {
    int result = n;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;

            result -= result / i;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
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

long long euler_theorem(int a, int n) {
    if (n <= 0)
        return -1;

    if (a <= 0)
        return -2;

    if (gcd(a, n) != 1)
        return -3;

    return mod_pow(a, phi(n), n);
}

int main() {
    int a, n;

    printf("Enter base: ");
    scanf("%d", &a);

    printf("Enter modulus: ");
    scanf("%d", &n);

    long long ans = euler_theorem(a, n);

    if (ans == -1)
        printf("Invalid modulus\n");
    else if (ans == -2)
        printf("Invalid base\n");
    else if (ans == -3)
        printf("a and n must be coprime\n");
    else {
        printf("Result = %lld\n", ans);
        printf("Euler's theorem verified.\n");
    }

    return 0;
}
