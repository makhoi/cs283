#include <stdio.h>

int main() {
    int number = 12345;

    int revNumber = 0;
    
    while(number) {
        revNumber = revNumber*10 + number%10;
        number/=10;
        printf("%d\n", revNumber);
    }
    return 0;
}