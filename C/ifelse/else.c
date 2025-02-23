//else specify a block of code executed when the condition is FALSE 

#include <stdio.h>

int main() {
    float time = 19.5;
    if(time < 18) {
        printf("good day\n");
    } else printf("good evening\n");
     //code instruction under else is executed since condition is FALSE
    return 0;
}