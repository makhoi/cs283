#include <stdio.h>

int main() {
    int i = 10;
    float f = 4.5;
    double d = 5.5;
    char c = 'a';

    //sizeof() = unary operator  
    //format specifier is %lu
    printf("%lu\n",sizeof(i));
    printf("%lu\n",sizeof(f));
    printf("%lu\n",sizeof(d));
    printf("%lu\n",sizeof(c));

    return 0;
}