#include <stdio.h>
#include <ncurses/ncurses.h>
#include <time.h>

void title(int x_max, int y_max);
void callAction(int x_max, int y_max, int frameCount);
void surfaceMoon(int x_max, int y_max);
void terrainMoon(int x_max, int y_max);
void space(int x_max, int y_max);
void saturn(int x_max, int y_max);
void spaceship(int x_max, int y_max, bool *move, int frameCount);
void tank(int x_position, int y_max);
void getaskForNameName(int x_max, int y_max);
void commands(int x_max, int y_max, int which);
void rocket(int rocketsXY[][10], int y_max);
void explosion(int x_explosion, int y_explosion);
void lifePoints(int x_max, int y_max, int hp);
void printScore(int x_max, int y_max, int score);
void alienShot(int alienProjectilesXY[][10]);
void gameOver(int x_max, int y_max);
void printFinalScore(int x_max, int y_max, int score);

/*
This file contains all the graphics of the game and the functions to print them on screen.
*/

void title(int x_max, int y_max)
{
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    int y = y_max / 3;
    int x = (x_max - 141) / 2;
    mvprintw(y, x, "  _______  ___      ___   _______  __    _   ");
    mvprintw(y + 1, x, " |   _   ||   |    |   | |       ||  |  | |  ");
    mvprintw(y + 2, x, " |  |_|  ||   |    |   | |    ___||   |_| |  ");
    mvprintw(y + 3, x, " |       ||   |    |   | |   |___ |       |  ");
    mvprintw(y + 4, x, " |       ||   |___ |   | |    ___||  _    |  ");
    mvprintw(y + 5, x, " |   _   ||       ||   | |   |___ | | |   |  ");
    mvprintw(y + 6, x, " |__| |__||_______||___| |_______||_|  |__|  ");
    mvprintw(y, x + 57, "  ______   _______  _______  _______  ______    _______  __   __  _______  ______    ");
    mvprintw(y + 1, x + 57, " |      | |       ||       ||       ||    _ |  |       ||  | |  ||       ||    _ |   ");
    mvprintw(y + 2, x + 57, " |  _    ||    ___||  _____||_     _||   | ||  |   _   ||  |_|  ||    ___||   | ||   ");
    mvprintw(y + 3, x + 57, " | | |   ||   |___ | |_____   |   |  |   |_||_ |  | |  ||       ||   |___ |   |_||_  ");
    mvprintw(y + 4, x + 57, " | |_|   ||    ___||_____  |  |   |  |    __  ||  |_|  ||_     _||    ___||    __  | ");
    mvprintw(y + 5, x + 57, " |       ||   |___  _____| |  |   |  |   |  | ||       |  |   |  |   |___ |   |  | | ");
    mvprintw(y + 6, x + 57, " |______| |_______||_______|  |___|  |___|  |_||_______|  |___|  |_______||___|  |_| ");
    attron(COLOR_PAIR(1));
}

void callAction(int x_max, int y_max, int frameCount)
{
    int y = y_max / 3;
    int x = (x_max - 25) / 2;

    if (frameCount % 4 == 0)
    {
        mvprintw(y + 12, x, "                           ");
        mvprintw(y + 13, x, "                           ");
        mvprintw(y + 14, x, "                           ");
    }
    else
    {
        mvprintw(y + 12, x, "                           ");
        mvprintw(y + 13, x, "  Press a button to play!  ");
        mvprintw(y + 14, x, "                           ");
    }
}

void surfaceMoon(int x_max, int y_max)
{
    int i;
    for (i = 1; i <= x_max - 75; i += 75)
    {
        mvprintw(y_max - 5, i, "____^/\\___^--__________O______________/\\/\\---/\\___________---_____^--___/\\_");
    }
    for (; i <= x_max; i += 3)
    {
        mvprintw(y_max - 5, i, "___");
    }
}

void terrainMoon(int x_max, int y_max)
{
    int i;
    for (i = 1; i <= x_max - 75; i += 75)
    {
        mvprintw(y_max - 4, i, "   /\\^   ^  ^    ^                  ^^ ^  '\\ ^          ^       ---        ");
        mvprintw(y_max - 3, i, "         --           -            --  -      -         ---  __       ^    ");
        mvprintw(y_max - 2, i, "   --  __                      ___--  ^  ^                         --  __  ");
    }
    for (; i <= x_max; i += 3)
    {
        mvprintw(y_max - 4, i, "  _");
        mvprintw(y_max - 3, i, "   ");
        mvprintw(y_max - 2, i, ".  ");
    }
}

void space(int x_max, int y_max)
{
    srand(42);
    char characters[5] = {' ', '.', '*', 'o', ','};
    int r;
    for (int i = 1; i <= y_max - 6; i++)
    {
        for (int j = 1; j <= x_max; j++)
        {
            r = rand() % 155;
            if (r <= 150)
            {
                mvprintw(i, j, "%c", characters[0]);
            }
            else
            {
                mvprintw(i, j, "%c", characters[r - 150]);
            }
        }
    }
}

void saturn(int x_max, int y_max)
{
    mvprintw(8, x_max - 30, ".-.,=\"``\"=. ");
    mvprintw(9, x_max - 30, "'=/_       \\ ");
    mvprintw(10, x_max - 30, " |  '=._    | ");
    mvprintw(11, x_max - 30, "  \\     `=./`, ");
    mvprintw(12, x_max - 30, "   '=.__.=' `=' ");
}

void spaceship(int x_max, int y_max, bool *move, int frameCount)
{
    int x = x_max / 7, y = y_max / 5;
    if (*move == 1)
    {
        mvprintw(y + 7, x - 9, "__");
        mvprintw(y + 8, x - 9, "| \\");
        mvprintw(y + 9, x - 18, "..-==-.==[_|H)--._____");
        mvprintw(y + 10, x - 21, ".-+++==--.==[+--,-------'");
        mvprintw(y + 11, x - 9, "[|_/"
                                "");
        if (frameCount == 4)
        {
            *move = 0;
        }
    }
    else
    {
        mvprintw(y + 5, x - 7, "__");
        mvprintw(y + 6, x - 7, "| \\ ");
        mvprintw(y + 7, x - 16, "..-==-.==[_|H)--._____");
        mvprintw(y + 8, x - 19, ".-+++==--.==[+--,-------'");
        mvprintw(y + 9, x - 7, "[|_/"
                               "");
        if (frameCount == 4)
        {
            *move = 1;
        }
    }
}

void tank(int x_position, int y_max)
{
    /*
    movement: 0 = no movement, 1 = right movement
    */
    mvprintw(y_max - 15, x_position + 6, "....");
    mvprintw(y_max - 14, x_position + 6, "||||");
    mvprintw(y_max - 13, x_position + 7, "..");
    mvprintw(y_max - 12, x_position + 7, "..");
    mvprintw(y_max - 11, x_position + 7, "..");
    mvprintw(y_max - 10, x_position + 5, "-+=++=");
    mvprintw(y_max - 9, x_position + 3, ":.:..-=+ .=");
    mvprintw(y_max - 8, x_position + 1, ".-:::::::-------");
    mvprintw(y_max - 7, x_position, "=************####=");
    mvprintw(y_max - 6, x_position, ".*++*+*=**++**++*=");
    mvprintw(y_max - 5, x_position + 2, "*++++++++++++*");
}

void askForName(int x_max, int y_max)
{
    int y = y_max / 3;
    int x = (x_max - 141) / 2;
    mvprintw(y + 0, x, "                                                                                                                                             ");
    mvprintw(y + 1, x, "                                                                                                                                             ");
    mvprintw(y + 2, x, "                     ==================================================================================================                      ");
    mvprintw(y + 3, x, "                     ||      Insert player name and press enter twice:                                               ||                      ");
    mvprintw(y + 4, x, "                     ==================================================================================================                      ");
    mvprintw(y + 5, x, "                                                                                                                                             ");
    mvprintw(y + 6, x, "                                                                                                                                             ");
}

void commands(int x_max, int y_max, int which)
{
    if (which == 0)
    {
        int y = (y_max / 4);
        int x = (x_max - 27) / 2;
        mvprintw(y, x, "                           ");
        mvprintw(y + 1, x, "                           ");
    }
    else if (which == 1)
    {
        int y = (y_max / 4);
        int x = (x_max - 27) / 2;
        mvprintw(y, x, "Hold on as long as you can!");
        mvprintw(y + 1, x, "  Press enter to start!    ");
    }
    else
    {
        int y = (y_max / 2);
        int x = (x_max - 16) / 2;

        mvprintw(y + 0, x, "     Fire!      ");
        mvprintw(y + 3, x, " /$$  /$$  /$$");
        mvprintw(y + 4, x, "| $$ | $$ | $$");
        mvprintw(y + 5, x, "| $$ | $$ | $$");
        mvprintw(y + 6, x, "| $$ | $$ | $$");
        mvprintw(y + 7, x, "|  $$$$$/$$$$/");
        mvprintw(y + 8, x, " \\_____/\\___/");

        x = (x_max - 38) / 2;
        mvprintw(y + 13, x - 13, "Move left");
        mvprintw(y + 11, x, "  /$$$$$$ ");
        mvprintw(y + 12, x, " |____  $$");
        mvprintw(y + 13, x, "  /$$$$$$$");
        mvprintw(y + 14, x, " /$$__  $$");
        mvprintw(y + 15, x, "|  $$$$$$$");
        mvprintw(y + 16, x, " \\_______/");
        x = (x_max + 12) / 2;
        mvprintw(y + 13, x + 15, "Move right");
        mvprintw(y + 9, x, "       __");
        mvprintw(y + 10, x, "      | $$");
        mvprintw(y + 11, x, "  /$$$$$$$");
        mvprintw(y + 12, x, " /$$__  $$");
        mvprintw(y + 13, x, "| $$  | $$");
        mvprintw(y + 14, x, "| $$  | $$");
        mvprintw(y + 15, x, "|  $$$$$$$");
        mvprintw(y + 16, x, " \\_______/");
    }
}

void alienSpaceship(int x, int y, int which)
{
    switch (which)
    {
    case 0:
        mvprintw(y + 0, x + 1, "-:%%%%:");
        mvprintw(y + 1, x, "*%%%%==##+");
        mvprintw(y + 2, x + 1, ".*@#=");
        mvprintw(y + 3, x + 3, ":.");
        mvprintw(y + 4, x + 3, "=:");
        mvprintw(y + 5, x, "--*%%%%=-:");
        mvprintw(y + 6, x + 2, ":**.");
        mvprintw(y + 7, x + 3, "+=");
        break;
    case 1:
        mvprintw(y + 0, x + 4, "##");
        mvprintw(y + 1, x + 3, "#%%#+");
        mvprintw(y + 2, x + 2, "%%#%%#=");
        mvprintw(y + 3, x, "*#@**#@+*:");
        mvprintw(y + 4, x, "=###*##**.");
        mvprintw(y + 5, x, " #%%*-=#=*");
        mvprintw(y + 6, x + 1, "*-*@#+ +");
        mvprintw(y + 7, x + 3, "###=");
        mvprintw(y + 8, x + 3, ":*+");
        break;
    case 2:
        mvprintw(y + 0, x + 5, ".");
        mvprintw(y + 1, x + 5, "*#");
        mvprintw(y + 2, x + 4, "*###");
        mvprintw(y + 3, x + 4, "#@@%%");
        mvprintw(y + 4, x + 2, "#######.");
        mvprintw(y + 5, x + 0, ":##%%=*@**##=");
        mvprintw(y + 6, x + 1, "-**+##**#=");
        mvprintw(y + 7, x + 1, "-=  -=  =-");
        mvprintw(y + 8, x + 1, ".*      *:");
        break;
    case 3:
        mvprintw(y + 0, x + 6, "#");
        mvprintw(y + 1, x + 5, "+#=");
        mvprintw(y + 2, x + 2, "-%%*##@#%%*#-");
        mvprintw(y + 3, x + 0, "%%+##*+*#+*##+=");
        mvprintw(y + 4, x + 0, "=#**#*%%**#*##:");
        mvprintw(y + 5, x + 1, "%%@###+%%+#@=+");
        mvprintw(y + 6, x + 1, "=*#*=+:##*:");
        mvprintw(y + 7, x + 2, "*#=   ##=");
        mvprintw(y + 8, x + 3, "+    :=");
        break;
    case 4:
        mvprintw(y + 0, x + 4, ".= %%@+ :");
        mvprintw(y + 1, x + 2, ".. -%%%%#*#@%%");
        mvprintw(y + 2, x + 1, "***###***##+ *:");
        mvprintw(y + 3, x + 1, "@@#**++**%%#+=%%#");
        mvprintw(y + 4, x + 0, "=#*#***=#+***##*");
        mvprintw(y + 5, x + 1, "-%%*##@%%*=#####");
        mvprintw(y + 6, x + 0, ":##*#@##=%%*=#**+");
        mvprintw(y + 7, x + 0, "-==-===-===--==:");
        mvprintw(y + 8, x + 1, "#  - - = =  *-:");
        mvprintw(y + 9, x + 1, "%%           %%*");
        break;
    }
}

void rocket(int rocketsXY[][10], int y_max)
{
    for (int i = 0; i < 10; i++)
    {
        if (rocketsXY[0][i] != 0)
        {
            (rocketsXY[1][i] < y_max - 16 && rocketsXY[1][i] + 1 > 0) ? (mvprintw(rocketsXY[1][i] + 1, rocketsXY[0][i], "##")) : (0);
            (rocketsXY[1][i] < y_max - 17 && rocketsXY[1][i] + 2 > 0) ? (mvprintw(rocketsXY[1][i] + 2, rocketsXY[0][i], "##")) : (0);
            (rocketsXY[1][i] < y_max - 18 && rocketsXY[1][i] + 3 > 0) ? (mvprintw(rocketsXY[1][i] + 3, rocketsXY[0][i] - 2, "=%%##%%=")) : (0);
            (rocketsXY[1][i] < y_max - 19 && rocketsXY[1][i] + 4 > 0) ? (mvprintw(rocketsXY[1][i] + 4, rocketsXY[0][i] - 1, "::::")) : (0);
            (rocketsXY[1][i] < y_max - 20 && rocketsXY[1][i] + 5 > 0) ? (mvprintw(rocketsXY[1][i] + 5, rocketsXY[0][i], "..")) : (0);
        }
    }
}

void explosion(int x_explosion, int y_explosion)
{
    mvprintw(y_explosion + 2, x_explosion - 10, "...     ..:.  ....   ..");
    mvprintw(y_explosion + 3, x_explosion - 11, "...       .-..  ..   ....");
    mvprintw(y_explosion + 4, x_explosion - 14, ".....:.......:-::..    .");
    mvprintw(y_explosion + 5, x_explosion - 13, ".. .::--.:::-::--:.. .:.");
    mvprintw(y_explosion + 6, x_explosion - 9, ".:--:-==-+=--::::..");
    mvprintw(y_explosion + 7, x_explosion - 6, "..--:=*++###+=+-:::..      :--=");
    mvprintw(y_explosion + 8, x_explosion - 13, "...::::-+*%%%%%%%%%%#**=---::..  :+-=-+");
    mvprintw(y_explosion + 9, x_explosion - 14, ".:--:--+###%%%%@@%%%%%%**+-:-::..  .:+:");
    mvprintw(y_explosion + 10, x_explosion - 11, "..:=++##%%%%%%#%%###==-:..");
    mvprintw(y_explosion + 11, x_explosion - 11, "..::---=++*#***-+-::..    ..");
    mvprintw(y_explosion + 12, x_explosion - 9, "..::---:-===+-::...::. ....");
    mvprintw(y_explosion + 13, x_explosion - 14, "...  ...:..::-::--:..   .....");
    mvprintw(y_explosion + 14, x_explosion - 14, "........     ..::.     .. ...");
    mvprintw(y_explosion + 15, x_explosion - 12, ".... .      .:..    .:.");
}

void lifePoints(int x_max, int y_max, int hp)
{
    init_pair(3, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(3));
    for (int index = 0; index < hp; index++)
    {
        mvprintw(y_max - 5, x_max - 9 * (3 - index), " @%% %%@ ");
        mvprintw(y_max - 4, x_max - 9 * (3 - index), "@##@##@");
        mvprintw(y_max - 3, x_max - 9 * (3 - index), " @###@ ");
        mvprintw(y_max - 2, x_max - 9 * (3 - index), "   @   ");
    }
    for (int index = 2; index >= hp; index--)
    {
        mvprintw(y_max - 5, x_max - 9 * (3 - index), " @%% %%@ ");
        mvprintw(y_max - 4, x_max - 9 * (3 - index), "@     @");
        mvprintw(y_max - 3, x_max - 9 * (3 - index), " @   @ ");
        mvprintw(y_max - 2, x_max - 9 * (3 - index), "   @   ");
    }
    attron(COLOR_PAIR(1));
}

void printScore(int x, int y_max, int score)
{
    char stringScore[3];

    attron(COLOR_PAIR(2));
    itoa(score, stringScore, 10);
    for (int i = 0; i < sizeof(stringScore) / sizeof(stringScore[0]); i++)
    {
        switch (stringScore[i])
        {
        case '1':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  _    ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " / |   ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " | |   ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " |_|   ");
            break;

        case '2':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  ___  ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " |_  ) ");
            mvprintw(y_max - 3, x + 6 * (i + 1), "  / /  ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " /___| ");
            break;

        case '3':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  ___   ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " |__ /  ");
            mvprintw(y_max - 3, x + 6 * (i + 1), "  |_ \\ ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " |___/  ");
            break;

        case '4':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  _     ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " | |__  ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " |_  _| ");
            mvprintw(y_max - 2, x + 6 * (i + 1), "   |_|  ");
            break;

        case '5':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  ___  ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " | __| ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " |__ \\ ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " |___/ ");
            break;

        case '6':
            mvprintw(y_max - 5, x + 6 * (i + 1), "   _    ");
            mvprintw(y_max - 4, x + 6 * (i + 1), "  / /   ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " / _ \\ ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " \\___/ ");
            break;

        case '7':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  ___  ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " |__ / ");
            mvprintw(y_max - 3, x + 6 * (i + 1), "  / /  ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " /_/   ");
            break;

        case '8':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  ___  ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " ( _ ) ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " / _ \\ ");
            mvprintw(y_max - 2, x + 6 * (i + 1), " \\___/ ");
            break;

        case '9':
            mvprintw(y_max - 5, x + 6 * (i + 1), "  ___   ");
            mvprintw(y_max - 4, x + 6 * (i + 1), " / __\\ ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " \\_, / ");
            mvprintw(y_max - 2, x + 6 * (i + 1), "  /_/   ");
            break;

        case '0':
            mvprintw(y_max - 5, x + 6 * (i + 1), "   __   ");
            mvprintw(y_max - 4, x + 6 * (i + 1), "  /  \\ ");
            mvprintw(y_max - 3, x + 6 * (i + 1), " | () | ");
            mvprintw(y_max - 2, x + 6 * (i + 1), "  \\__/ ");
            break;
        }
    }
    attron(COLOR_PAIR(1));
}

void alienShot(int alienProjectilesXY[][10])
{
    for (int index = 0; index < 10; index++)
    {
        if (alienProjectilesXY[1][index] != -100)
        {
            mvprintw(alienProjectilesXY[1][index],     alienProjectilesXY[0][index] + 1, ".**.");
            mvprintw(alienProjectilesXY[1][index] + 1, alienProjectilesXY[0][index],     "**##**");
            mvprintw(alienProjectilesXY[1][index] + 2, alienProjectilesXY[0][index] + 1, "'**'");
        }
    }
}

void gameOver(int x_max, int y_max)
{
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    int y = y_max / 3;
    int x = (x_max - 80) / 2;
    mvprintw(y, x, " _______  _______  __   __  _______         _______  __   __  _______  ______   ");
    mvprintw(y + 1, x, "|       ||   _   ||  |_|  ||       |       |       ||  | |  ||       ||    _ |  ");
    mvprintw(y + 2, x, "|    ___||  |_|  ||       ||    ___|       |   _   ||  |_|  ||    ___||   | ||  ");
    mvprintw(y + 3, x, "|   | __ |       ||       ||   |___        |  | |  ||       ||   |___ |   |_||_ ");
    mvprintw(y + 4, x, "|   ||  ||       ||       ||    ___|       |  |_|  ||       ||    ___||    __  |");
    mvprintw(y + 5, x, "|   |_| ||   _   || ||_|| ||   |___        |       | |     | |   |___ |   |  | |");
    mvprintw(y + 6, x, "|_______||__| |__||_|   |_||_______|       |_______|  |___|  |_______||___|  |_|");
}


void printFinalScore(int x_max, int y_max, int score){
    int y = y_max/3 + 15;
    int x = (x_max - 40) / 2;
    mvprintw(y, x, "Final score: ");
    printScore(x+13, y+3, score);
}