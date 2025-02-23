#include <stdio.h>

int main() {
    int myNum = 1000;
    float myFloatNum = 50.5;
    double myDoubleNum = 12.55;
    //Scientific numbers
    //e = power of 10
    float f1 = 35e7;
    double d1 = 10E12;

    printf("%i\n", myNum);
    printf("%.1f\n", myFloatNum);
    printf("%.2lf\n", myDoubleNum);
    printf("%f\n", f1);
    printf("%lf\n",d1);

    return 0;
}