#include <stdio.h>
#include <stdlib.h.>
#include <unistd.h>
#include <conio.h>
#include <ncurses/ncurses.h>
#include <windows.h>
#include <stdbool.h>
#include "appearance.c"

void setupTerminal();
void startIntro();
void refreshScreen(int rate);
int moveTank(bool moveRight, int tankPosition);
void screenTransition();
char *getUserData();
void instruction();
int play();
void moveAlien(int aliens[][10], bool *move);
void FlushStdin();
void moveRockets(int rocketsXY[][10], int *rocketVelocity);
void fireTank(int x, int y, int rocketsXY[][10]);
void rocketAcceleration(int rocketsXY[][10], int *rocketVelocity);
void checkCollisions(int rocketsXY[][10], int aliens[][10], int *aliensCounter, int *explosionsX, int *explosionsTime, int *explosionCounter, int *score, int alienProjectilesXY[][10], int tankPosition, int *hp);
void moveAlienProjectile(int alienProjectilesX[][10]);
void endGame();

int x_max;
int y_max;

const int RATEMENU = 250, RATEGAME = 25;

void setupTerminal()
{
    /*
    This function sets up the terminal: resize it, reposition it and set some properties of the terminal.
    */
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL)
    {
        HWND consoleWindow = GetConsoleWindow();
        ShowWindow(consoleWindow, SW_MAXIMIZE);
        SetConsoleMode(consoleWindow, ENABLE_WRAP_AT_EOL_OUTPUT);

        COORD coord;
        coord.X = 9900;
        coord.Y = 9900;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        SMALL_RECT rect;
        rect.Left = 0;
        rect.Top = 0;
        rect.Right = GetSystemMetrics(SM_CXSCREEN);
        rect.Bottom = GetSystemMetrics(SM_CYSCREEN);
        SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
    }

    initscr();
    cbreak();
    noecho();
    clear();
    // raw();
    start_color();
    curs_set(FALSE);

    x_max = getmaxx(stdscr), y_max = getmaxy(stdscr);
}

void startIntro()
{
    /*
    This function builds the intro graphics and animations.
    Loops the animation until a button is pressed.
    */
    bool tankMoveRight = true;
    bool spaceShipMovement = true;
    int tankPosition = 30;
    terrainMoon(x_max, y_max);

    while (true)
    {
        (tankPosition <= 15) ? (tankMoveRight = true) : (0);
        (tankPosition + 18 >= x_max - 15) ? (tankMoveRight = false) : (0);

        for (int frameCount = 1; frameCount <= 4; frameCount++)
        {
            space(x_max, y_max);
            spaceship(x_max, y_max, &spaceShipMovement, frameCount);
            saturn(x_max, y_max);
            surfaceMoon(x_max, y_max);
            tankPosition = moveTank(tankMoveRight, tankPosition);
            title(x_max, y_max);
            callAction(x_max, y_max, frameCount);
            refreshScreen(RATEMENU);
        }

        if (kbhit())
        {
            FlushStdin();
            break;
        }
    }
}

void refreshScreen(int rate)
{
    /*
    This function refresh the screen updating the terminal with the new graphics printed in the last frame
    and freeze the program for a certain amount of time (rate).
    */
    refresh();
    Sleep(rate);
}

int moveTank(bool moveRight, int tankPosition)
{
    /*
    Updating the tank position based on the direction in which is moving.
    */
    if (moveRight == true)
    {
        if (tankPosition < x_max - 23)
        {
            tankPosition += 2;
        }
        tank(tankPosition, y_max);
    }
    else
    {
        if (tankPosition > 5)
        {
            tankPosition -= 2;
        }
        tank(tankPosition, y_max);
    }
    return tankPosition;
}

char *getUserData()
{
    /*
    Requests the player username with some graphic and returns it.
    Shows what the players is typing in real time.
    */
    int y = y_max / 3;
    int x = (x_max - 141) / 2;
    char *input = malloc(100);
    int index = 0;
    int c;

    askForName(x_max, y_max);
    refresh();

    do
    {
        c = getchar();
        if (c == '\b' && index > 0)
        {
            mvprintw(y + 3, x + 71 + index, " ");
            refresh();
            index--;
        }
        else
        {
            input[index] = c;
            mvprintw(y + 3, x + 71 + 1 + index, "%c", c);
            refresh();
            index++;
        }

    } while (c != '\n' && c != '\r');

    input[index] = '\0';

    return input;
}

void screenTransition()
{
    /*
    Creates a transition effect from right to left.
    */
    for (int i = x_max; i >= 0; i--)
    {
        for (int j = 0; j <= y_max; j++)
        {
            mvprintw(j, i, " ");
        }
        refreshScreen(10);
    }
}

void instruction()
{
    /*
    Prints on screen the instructions of the game.
    */
    bool flag = false;
    commands(x_max, y_max, 2);
    refresh();
    while (flag == false)
    {
        commands(x_max, y_max, 1);
        refreshScreen(1000);
        commands(x_max, y_max, 0);
        refreshScreen(500);
        if (kbhit())
        {
            flag = true;
        }
    }
}

void FlushStdin(void)
{
    fflush(stdin);
    // FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

int play()
{
    int tankPosition = y_max / 2;
    int playerInput;
    int fireDelay = 0;
    int alienDelay = 0;
    int wave = 0;
    int hp = 3;
    int score = 0;
    int random;

    // First row keeps track of aliens' X-position,  second row keeps track of the type of alien
    int aliens[2][10] = {
        {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
    bool alienDirection = false;
    int alienCounter = 0;
    // First row keeps track of the projectiles' X-position, second row keeps track of the Y-position
    int alienProjectilesXY[2][10] = {
        {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100},
        {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100}};
    // First row keeps track of the tank-rockets' X-position, second row keeps track of the Y-position
    int rocketsXY[2][10] = {
        {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100},
        {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100}};
    int rocketsVelocity[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    int explosionsX[10] = {-100, -100, -100, -100, -100, -100, -100, -100, -100, -100};
    int explosionsTime[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int explosionsCounter = 0;

    while (true)
    {
        srand(time(NULL));
        // Manage the delay between two consecutive tank shots
        if (fireDelay > 0)
        {
            fireDelay--;
        }

        // This function makes randomly shoot aliens
        for (int i = 0; i < 10; i++)
        {
            random = rand() % 5;
            if ((aliens[0][i] != -100) && (alienProjectilesXY[1][i] == -100) && (random == 0))
            {
                alienProjectilesXY[0][i] = aliens[0][i] + 3;
                alienProjectilesXY[1][i] = 7;
            }
        }

        // This function spawns aliens if there are no more aliens on screen and if there are no more alien explosion
        if (alienCounter == 0 && explosionsCounter == 0)
        {
            wave++;
            for (int i = 0; i < wave; i++)
            {
                random = rand() % 5;
                aliens[0][i] = (x_max / (wave + 1)) * (i + 1);
                aliens[1][i] = random;
                alienCounter++;
            }
        }
        // Move every frame the aliens' bombs
        moveAlienProjectile(alienProjectilesXY);
        // Move alien ships and accelerate tank's rockets every 4 frame
        alienDelay++;
        if (alienDelay == 4)
        {
            moveAlien(aliens, &alienDirection);
            rocketAcceleration(rocketsXY, rocketsVelocity);
            alienDelay = 0;
        }
        moveRockets(rocketsXY, rocketsVelocity);

        checkCollisions(rocketsXY, aliens, &alienCounter, explosionsX, explosionsTime,
                        &explosionsCounter, &score, alienProjectilesXY, tankPosition, &hp);

        // Get the player's input and recall the right function
        if (kbhit())
        {
            playerInput = getchar();
            switch (playerInput)
            {
            case 'd':
                tankPosition = moveTank(true, tankPosition);
                break;
            case 'a':
                tankPosition = moveTank(false, tankPosition);
                break;
            case 'w':
                if (fireDelay == 0)
                {
                    fireTank(tankPosition, y_max - 15, rocketsXY);
                    fireDelay = 4;
                }
                break;
            }
        }
        
        // Render all the elements
        space(x_max, y_max);
        for (int i = 0; i < 10; i++)
        {
            if (aliens[0][i] != -100)
            {
                alienSpaceship(aliens[0][i], 5, aliens[1][i]);
            }
        }
        rocket(rocketsXY, y_max);
        tank(tankPosition, y_max);
        alienShot(alienProjectilesXY);
        terrainMoon(x_max, y_max);
        surfaceMoon(x_max, y_max);

        for (int index = 0; index < 10; index++)
        {
            if (explosionsTime[index] != 0)
            {
                explosion(explosionsX[index], 0);
                explosionsTime[index]--;
                if (explosionsTime[index] == 0)
                {
                    explosionsCounter--;
                }
            }
        }

        lifePoints(x_max, y_max, hp);
        printScore(0, y_max, score);
        refreshScreen(RATEGAME);
        FlushStdin();

        // If life points drops to zero this function displays an animation on screen and break from the game loop
        if (hp == 0)
        {
            for (int index = 0; index < 5; index++)
            {
                space(x_max, y_max);
                lifePoints(x_max, y_max, hp);
                printScore(x_max, y_max, score);
                tank(tankPosition, y_max);
                refreshScreen(RATEMENU);
                space(x_max, y_max);
                surfaceMoon(x_max, y_max);
                lifePoints(x_max, y_max, hp);
                printScore(x_max, y_max, score);
                refreshScreen(RATEMENU);
            }
            break;
        }
    }
    return score;
}

void moveAlien(int aliens[][10], bool *move)
{
// Manage the movement of the aliens' ships. 
// The argument move stores the direction of movement.
    int length = 10;
    int lastAlienPosition = 0;
    int firstAlienPosition = x_max;
    for (int i = 0; i < length; i++)
    {
        if (aliens[0][i] != -100 && *move == true)
        {
            lastAlienPosition = aliens[0][i];
            aliens[0][i] += 2;
        }
        if (aliens[0][i] != -100 && *move == false)
        {
            aliens[0][i] -= 2;
        }
        if (aliens[0][9 - i] != -100 && *move == false)
        {
            firstAlienPosition = aliens[0][9 - i];
        }
    }
    ((*move == true) && (lastAlienPosition >= x_max - 30)) ? (*move = false) : (0);
    ((*move == false) && (firstAlienPosition <= 15)) ? (*move = true) : (0);
}

void moveRockets(int rocketsXY[][10], int *rocketVelocity)
{
// Manage the movement of the aliens' ships. 
    for (int i = 0; i < 10; i++)
    {
        if (rocketsXY[1][i] + 5 < 0)
        {
            rocketsXY[1][i] = -100;
            rocketsXY[0][i] = -100;
            rocketVelocity[i] = 1;
        }
        if (rocketsXY[1][i] != -100)
        {
            rocketsXY[1][i] -= rocketVelocity[i];
        }
    }
}

void fireTank(int x, int y, int rocketsXY[][10])
{
// Spawns a rocket from the tank
    for (int i = 0; i < 10; i++)
    {
        if (rocketsXY[0][i] == -100)
        {
            rocketsXY[0][i] = x + 7;
            rocketsXY[1][i] = y;
            break;
        }
    }
}

void rocketAcceleration(int rocketsXY[][10], int *rocketVelocity)
{
// Increases rockets' velocity
    for (int i = 0; i < 10; i++)
    {
        if (rocketsXY[1][i] != -100)
        {
            rocketVelocity[i] += 1;
        }
    }
}

void checkCollisions(int rocketsXY[][10], int aliens[][10], int *aliensCounter, int *explosionsX, int *explosionsTime,
                     int *explosionCounter, int *score, int alienProjectilesXY[][10], int tankPosition, int *hp)
{
// This function checks for collision between tank's rockets and alien's ships, and also collision between aliens' bombs and the tank.
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if ((aliens[0][j] <= rocketsXY[0][i]) && (rocketsXY[0][i] <= (aliens[0][j] + aliens[1][j] * 2 + 8)) && (5 <= rocketsXY[1][i]) && (rocketsXY[1][i] <= 12))
            {
                aliens[0][j] = -100;
                *aliensCounter -= 1;
                *score += 10;
                for (int h = 0; h < 10; h++)
                {
                    if (explosionsTime[h] == 0)
                    {
                        explosionsTime[h] = 16;
                        explosionsX[h] = rocketsXY[0][i];
                        *explosionCounter += 1;
                        break;
                    }
                }
                rocketsXY[0][i] = -100;
                rocketsXY[1][i] = -100;
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (alienProjectilesXY[1][i] != -100 && alienProjectilesXY[1][i] == y_max - 12 && alienProjectilesXY[1][i] <= tankPosition + 18 && alienProjectilesXY[1][i] >= tankPosition - 3)
        {
            *hp -= 1;
            alienProjectilesXY[0][i] = -100;
            alienProjectilesXY[1][i] = -100;
        }
    }
}

void moveAlienProjectile(int alienProjectilesXY[][10])
{
// Manage aliens' bomb movement
    for (int index = 0; index < 10; index++)
    {
        if (alienProjectilesXY[1][index] != -100)
        {
            alienProjectilesXY[1][index] += 1;
        }
        if (alienProjectilesXY[1][index] > y_max - 8)
        {
            alienProjectilesXY[1][index] = -100;
            alienProjectilesXY[0][index] = -100;
        }
    }
}

void endGame(int score)
{
// Displays the final screen when the game is over.
    clear();
    gameOver(x_max, y_max);
    printFinalScore(x_max, y_max, score);
    refresh();
    while (true)
    {
    if (kbhit())
        {
            break;
        }
    }
}
