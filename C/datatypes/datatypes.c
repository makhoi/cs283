// data type / size / function / format specifiers
// int / 2-4 bytes / store whole number such as 22 / %d , %i
// float / 4 bytes / store floating number up to 6 - 7 decimal numbers such as 22.734856 / %f , %F
// double / 8 bytes / store doubling number up to 15 decimal numbers such as 22.812973879623 / %lf
// char / 1 byte / store 1 character such as 'a' / %c
// string (text) / %s

#include <stdio.h>

int main() {
    // int data type (2 - 4 bytes)
    int wholeNum = 22;
    int anotherWholeNum = 21;

    // float data type (4 bytes - store up to 6-7 decimal digits)
    float floatNum = 22.12;
    float anotherFloatNum = 22.15;

    // double data type (8 bytes - store up to 15 decimal digits)
    double fractionalNum = 22.12345678901234;
    
    // char data type (1 byte)
    char myLetter = 'A';

    printf("int type for storing whole number: %d\n", wholeNum);
    printf("format specifier for int type could be i or d: %i\n", anotherWholeNum);
    printf("float type for storing floating number: %f\n", floatNum);
    printf("format specifier for float could be f or F: %F\n", anotherFloatNum);
    printf("double type for storing fractional number with up to 15 digits: %lf\n", fractionalNum);
    printf("char for storing 1 character: %c\n", myLetter);

    return 0;
}