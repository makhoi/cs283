#include <stdio.h>

int main() {
    float f1 = 3.5;

    printf("%f\n",f1); //return 6 decimals at DEFAULT
    printf("%.1f\n",f1); //return 1 decimal
    printf("%.2f\n",f1); //return 2 decimals
    printf("%.3f\n",f1); //return 3 decimals
    printf("%.4f\n",f1); //return 4 decimals

    return 0;
}