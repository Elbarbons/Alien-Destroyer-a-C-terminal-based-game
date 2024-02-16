#include <stdio.h>
#include <stdlib.h.>
#include <string.h.>
#include "game.c"

int main(int argc, char *argv[])
{
// Checking number of arguments and passed arguments
    if (argc > 2)
    {
        printf("\nError: Number Of Arguments Passed: %d - this program accept only 1 argument", argc - 1);
        printf("\nPossible arguments: devmode");
        return -1;
    }
    // Running core game with full parts
    if (argc == 1)
    {
        int score;
        char *user;
        setupTerminal();
        startIntro();
        user = getUserData();
        screenTransition();
        instruction();
        score = play();
        endGame(score);
    }
    // Devmode to test quickly some parts. Just comment function you wish to skip in devmode
    else if (strcmp(argv[1], "devmode") == 0)
    {
        int score;
        char *user;
        setupTerminal();
        /*
        startIntro();
        user = getUserData();
        screenTransition();
        instruction();
        */
        score = play();
        endGame(score);
    }
    else
    {
        printf("\nInvalid argument.");
        printf("\nPossible arguments: devmode");
        return -1;
    }
    return 0;
}
