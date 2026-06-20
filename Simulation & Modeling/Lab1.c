#include <stdio.h>

int main()
{
    float Y_1, Y, I, T, C[5];
    float G[5] = {20, 25, 30, 35, 40};
    int i;

    printf("Enter initial value of lagged variable Y_1: ");
    scanf("%f", &Y_1);

    printf("\nThe growth in consumption is given in the following table:\n");
    printf("\nYear\tConsumption\n");

    for(i = 0; i < 5; i++)
    {
        I = 2 + 0.1 * Y_1;
        Y = 45.45 + 2.27 * (I + G[i]);
        T = 0.2 * Y;
        C[i] = 20 + 0.7 * (Y - T);

        printf("%d\t%.2f\n", i + 1, C[i]);

        Y_1 = Y;
    }

    return 0;
}
