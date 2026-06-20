#include <stdio.h>

int main()
{
    float l, m;
    float p, e, et;

    printf("Enter Inter arrival time of customers per hour: ");
    scanf("%f", &l);

    printf("Enter the average service rate per hour: ");
    scanf("%f", &m);

    if (m <= l)
    {
        printf("\nSystem is unstable because service rate must be greater than arrival rate.\n");
        return 0;
    }

    p = 1 - (l / m);
    e = l / (m - l);
    et = 1 / (m - l);
    et = et * 60;   // Convert hours to minutes

    printf("\nThe probability that a customer won't have to wait at the counter: %.4f", p);
    printf("\nExpected number of customers: %.4f", e);
    printf("\nExpected time to be spent in the bank: %.4f minutes", et);

    return 0;
}
