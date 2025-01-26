//type varName = value;
#include <stdio.h>

int main() {
    // int type - store whole number like 199 200
    int myWholeNumb = 15;

    // float type - store floating point number like 199.5 200.1
    float myFloatingNumb = 20.1;

    // char type - store a single character like 'a' or 'd'
    char myChar = 'a';

    // printf(myWholeNumb); 
    // printf(myFloatingNumb);
    // printf(myChar);
    // Above will print out error

    //Format Specifier - a place holder to tell compiler what type that var is holding

    // "%d" - int
    printf("Printing whole number: %d\n",myWholeNumb);

    // "%f" - float
    printf("Printing floating number: %.1f\n", myFloatingNumb);

    // "%c" - char
    printf("Printing a character: %c\n", myChar);

    //printing multiple types of variable within one printf
    printf("My whole number is %d and my character is %c.\n", myWholeNumb, myChar);

    return 0;
}
