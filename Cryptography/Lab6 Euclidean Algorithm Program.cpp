#include <stdio.h> 
#include <stdlib.h> 

int euclidean_gcd(int a, int b) {     
    a = abs(a);     
    b = abs(b);     

    while (b != 0) {         
        int temp = b;         
        b = a % b;         
        a = temp;     
    }     

    return a; 
}  

int main() {     
    int num1, num2; 

    printf("====================================\n");     
    printf("   Euclidean Algorithm Program\n");     
    printf("====================================\n"); 

    printf("Enter the first number: ");     
    scanf("%d", &num1); 

    printf("Enter the second number: ");     
    scanf("%d", &num2); 

    int gcd = euclidean_gcd(num1, num2); 

    printf("\nGCD of %d and %d is: %d\n", num1, num2, gcd); 

    return 0; 
}
