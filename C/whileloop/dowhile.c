/*
Do while loop is a variant of loop
Code block will always be executed at least once regardless of the condition is false
This is whats different from while loop
Then it will check the condition
Then continue the loop if condition is true
*/

#include <stdio.h>

int main() {
    int i = 3;

    do {
        printf("%i\n", i);
        i++;
    }
    while(i < 5);
    //Return 6 although the condition was not met
return 0;
}