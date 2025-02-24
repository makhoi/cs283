#include <stdio.h>

int main() {
    //example 1: reverse number
    printf("REVERSE NUMBER\n");
    int number = 12345;

    int revNumber = 0;
    
    while(number) {
        revNumber = revNumber*10 + number%10;
        number/=10;
        printf("%d\n", revNumber);
    }

    //example 2: count down
    printf("COUNT DOWN\n");
    int countdownNumber = 3;

    while(countdownNumber > 0){
        printf("%d\n", countdownNumber);
        countdownNumber--;
    }
    printf("Happy New Year!\n");

    //example 3: print even number from 0 to 10
    printf("EVEN NUMBER FROM 0 TO 10\n");
    int i = 0;

    while(i <= 10) {
        printf("%d\n", i);
        i += 2;
    }

    //example 4: print Yatzy if the 
    printf("YATZY!\n");
    int diceNumber = 1;

    while(diceNumber <= 6) {
        (diceNumber < 6) ? printf("No Yatzy\n") : printf("Yatzy!\n");
        diceNumber ++;
    }

    return 0;
}