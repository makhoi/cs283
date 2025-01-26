#include <stdio.h>

int main() {

    // assign new value to existing var -> OVERWRITE its value
    int myNumb = 10;
    myNumb = 15;
    printf("New value of myNumb: %d\n", myNumb);

    // assign value of one var to the other
    int myNum = 20;
    int myOtherNum = 300;
    myNum = myOtherNum;
    printf("Value of myOtherNum has now been assigned to variable myNum: %d\n", myNum);

    // copy value into empty var
    int myNotEmptyVar = 100;
    int myEmptyVar;

    myEmptyVar = myNotEmptyVar;
    printf("Value of myNotEmptyVar has been copied to value of myEmptyVar: %d\n", myEmptyVar);

    // add var together
    int a = 25;
    int b = 35;
    int sum = a + b;
    printf("Adding a and b: %d\n", sum);

    return 0;
}