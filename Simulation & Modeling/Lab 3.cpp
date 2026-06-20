#include <stdio.h>

int main()
{
    float lambda, serviceTime, mu;
    float expectedTime, reachSeat, totalTime;

    lambda = 1.0;          // customers per minute
    serviceTime = 20.0;    // seconds

    mu = 60.0 / serviceTime;   // customers per minute

    expectedTime = 1.0 / (mu - lambda);

    reachSeat = 1.5;       // minutes

    totalTime = expectedTime + reachSeat;

    printf("Arrival Rate (lambda) = %.2f customer/minute\n", lambda);
    printf("Service Rate (mu) = %.2f customer/minute\n", mu);
    printf("Expected Time in System = %.2f minutes\n", expectedTime);
    printf("Time to Reach Seat = %.2f minutes\n", reachSeat);
    printf("Total Time Spent = %.2f minutes\n", totalTime);

    if(totalTime <= 2.0)
        printf("\nFan can expect to be seated for the kick-off.\n");
    else
        printf("\nFan may miss the kick-off.\n");

    return 0;
}
