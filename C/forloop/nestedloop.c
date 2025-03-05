#include <stdio.h>

int main() {
    int i,j;
    //outer loop
    for(i = 0; i < 2; i++) {
        printf("outer loop: %i\n", i); //executed 2 times

        for(j = 0; j < 3; j++) {
            printf("inner loop: %i\n", j); //executed 3*2=6 times
        }
    }
    
    return 0;
}