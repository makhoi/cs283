// character can be represented by number using ASCII table

#include <stdio.h>

int main() {
    //ASCII number to character
    char guessWhatCharacterDoes107Represent = 107;
    char guessWhatCharacterDoes104Represent = 104;
    char guessWhatCharacterDoes111Represent = 111;
    char guessWhatCharacterDoes105Represent = 105;

    printf("%c\n", guessWhatCharacterDoes107Represent);
    printf("%c\n", guessWhatCharacterDoes104Represent);
    printf("%c\n", guessWhatCharacterDoes111Represent);
    printf("%c\n", guessWhatCharacterDoes105Represent);

    // DONT use char type to store more than 1 character
    // // generate error
    // char myText = 'khoi';
    // printf("%c\n", myText);

    // use STRING to store multiple character - char type with %s format specifier
    char myText [] = "khoi"; // syntax: [] after var name , 
                            //wrapping around text must be double quote "" NOT single quote ''
    printf("%s\n", myText);

    return 0;
}