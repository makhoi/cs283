/*
for loop
for(exp1; exp2; exp3){
    code block to be executed
    }
exp1: executed ONCE before the code the execution of the code
exp2: condition of the execution
exp3: executed EVERY TIME until the condition is met
*/
#include <stdio.h>

int main() {
    int i;

    for(i=0; i < 10; i++) {
        printf("%d\n", i);
    }
    return 0;
}