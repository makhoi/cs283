//legal voting age example
#include <stdio.h>
#include <stdbool.h>

int main() {
    int legalVotingAge = 21;
    int yourAge = 22;

    if(yourAge >= legalVotingAge) {
        printf("You can vote\n");
    } else printf("Go home kid\n");

    return 0;
}