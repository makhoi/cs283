#include <stdio.h>
#include <math.h>

int main() {
    //assignment1: program counts to 100 by every 10
    //example: 0, 10, 20, ..., 100
    printf("ASSIGNMENT 1: PROGRAM COUNT TO 100 BY EVERY 10\n");
    for(int i = 0; i <= 100; i+=10) {
        printf("%i\n", i);
    }

    //assignment2: program print even number between 0 and 10
    printf("ASSIGNMENT 2: PROGRAM PRINTS EVEN NUMBER BETWEEN 0 AND 10\n");
    for(int i = 0; i <= 10; i+=2) {
        printf("%d\n", i);
    }

    //assignment 3: program print odd number between 0 and 10;
    printf("ASSIGNMENT 3: PROGRAM PRINTS ODD NUMBER BETWEEN 0 AND 10\n");
    for(int i = 1; i <= 10; i+=2) {
        printf("%d\n", i);
    }

    //assignment 4: print power of 2 up to 512:
    printf("ASSIGNMENT 4: PRINT POWER OF 2 UP TO 512\n");
    for(int i = 2; i <= 512; i *= 2) {
        printf("%d\n", i);
    }

    //assignment 5: multiplication table:
    printf("ASSIGNMENT 5: MULTIPLICATION TABLE\n");
    int number = 2;
    for(int i = 0; i <= 10; i++) {
        printf("%dx%d=%d\n", number, i, number*i);
    }

    return 0;
}