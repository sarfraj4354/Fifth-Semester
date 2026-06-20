#include <stdio.h>
#include <math.h>

int main()
{
    float l, pr, a;
    int x, i;

    printf("Enter arrival rate (lambda): ");
    scanf("%f", &l);

    printf("\nPoisson Distribution Probabilities:\n");

    for (x = 0; x < 16; x++)
    {
        a = 1;

        for (i = 1; i <= x; i++)
        {
            a *= i;
        }

        pr = (exp(-l) * pow(l, x)) / a;

        printf("P(X=%d) = %.6f\n", x, pr);
    }

    return 0;
}
