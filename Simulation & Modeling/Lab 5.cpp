#include <stdio.h>
int main() {
    float transMat[2][2] = {{0.9, 0.1}, {0.5, 0.5}};
    float vect[1][2] = {{1.0, 0.0}}; 
    float result[1][2] = {0.0, 0.0};
    int i, j, k;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                result[i][j] += vect[i][k] * transMat[k][j];
            }
        }
    }
    printf("\nWeather of next day using Markov chain:\n");
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            printf("%f\t", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}

