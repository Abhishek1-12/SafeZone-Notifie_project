#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0)); // Seed the random number generator

    int randomNumber = (rand() % 100) + 1; // Random number between 1 and 100
    int no_of_guesses = 0;
    int guessed;

    do {
        printf("Guess the number: ");
        scanf("%d", &guessed); // Corrected scanf format
        
        if (guessed > randomNumber) {
            printf("Lower number please!\n");
        } else if (guessed < randomNumber) {
            printf("Higher number please!\n");
        }
        no_of_guesses++;
    } while (guessed != randomNumber); // Fixed typo

    printf("You guessed the number in %d guesses!\n", no_of_guesses); // Fixed parentheses

    return 0;
}