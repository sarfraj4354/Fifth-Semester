#include <stdio.h>
#define SIZE 100

int main()
{
    int x[SIZE];
    int m = 100, a = 5, c = 13;
    int i;

    x[0] = 11;

    for(i = 0; i < SIZE - 1; i++)
    {
        x[i + 1] = (a * x[i] + c) % m;
    }

    printf("Linear Congruential Method Random Numbers:\n\n");

    for(i = 0; i < SIZE; i++)
    {
        printf("%d\t", x[i]);

        // print new line after every 10 numbers
        if((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }

    return 0;
}
