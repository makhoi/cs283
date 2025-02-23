#include <stdio.h>

int main() {
    int possibleScore = 120;
    int studentScore = 80;

    float percentage = (float)studentScore/possibleScore*100;
    //use double % to print % symbol
    printf("%.2f%%\n",percentage);

    return 0;
}