#include <stdio.h>

int main() {
    // \n for creating a new line
    printf("Hello!\n"); // 1st type: \n at each printf 
    printf("I just created a new line.\n"); 
    printf("Hello\nI just creat a new line.\n");//2nd type: multiple \n at each printf to avoid writing many printf
    printf("What if a do 2 dash n \n\n"); 
    printf("Use 2 consecutive \\n to create double blank space\n\n"); // 3rd type: multiple consective \n to create multiple consecutive blank space
    
    // \t for creating a horizontal tab
    printf("Using \\t to create a horizontal tab?\t");

    // \\\ for inserting a backlash character
    printf("Using double backlash to insert a backlash \\ as a text.\n");

    // \" for inserting a double quote character
    printf("Inserting a double quote character = back lash + double quote: \"\n");
    
    return 0;
}