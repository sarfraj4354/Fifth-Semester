#include <stdio.h>
#include <stdlib.h>

int extended_euclidean(int a, int b, int *x, int *y) {
    int original_a = a;
    a = abs(a);
    b = abs(b);

    if (b == 0) {
        *x = (original_a < 0) ? -1 : 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extended_euclidean(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int num1, num2, x, y;

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    int gcd = extended_euclidean(num1, num2, &x, &y);

    printf("\nGCD of %d and %d is: %d\n", num1, num2, gcd);
    printf("Coefficients (x, y) for Bezout's identity (%d * x + %d * y = gcd):\n", num1, num2);
    printf("x = %d, y = %d\n", x, y);

    printf("Verification: %d * %d + %d * %d = %d\n",
           num1, x, num2, y, num1 * x + num2 * y);

    return 0;
}
