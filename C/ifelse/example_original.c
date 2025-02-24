#include <stdio.h>

int main() {
    //check door code
    int doorCode = 8888;
    int inputCode = 8888;

    (doorCode == inputCode) ? printf("Correct code.\nWelcome!\n") : printf("Wrong code.\nPlease try again.\n");
    
    //check positive number
    int myNum = -4;

    (myNum > 0) ? printf("Positive number\n") : 
    (myNum < 0) ? printf("Negative number\n") :
    printf("0\n");

    //check voting age
    int myAge = 22;
    int votingAge = 21;

    (votingAge >= myAge) ? printf("Go vote!\n") : printf("Go home kiddo!\n");

    //check even/odd number
    int num = 10;

    (num % 2 == 0) ? printf("even\n") : printf("odd\n");

    return 0;
}