#include <stdio.h>

int win(int grid[9]) {
    int wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    for (int i = 0; i < 8; i++) {
        if (grid[wins[i][0]] != 0 && grid[wins[i][0]] == grid[wins[i][1]] && grid[wins[i][1]] == grid[wins[i][2]])
        {
            return grid[wins[i][2]];
        }
    }

    return 0;
}

char gridChar(int c) {
    switch (c)
    {
    case 0:
        return ' ';

    case 1:
        return 'O';

    case -1:
        return 'X';
    }
}

void displayGrid(int g[9]) {
    printf(" %c | %c | %c\n", gridChar(g[0]), gridChar(g[1]), gridChar(g[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gridChar(g[3]), gridChar(g[4]), gridChar(g[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gridChar(g[6]), gridChar(g[7]), gridChar(g[8]));
}

int minmax(int grid[9], int player)
{
    int winner = win(grid);
    if (winner != 0)
        return winner * player;

    int score = -2;
    int move = -1;

    for (int i = 0; i < 9; i++) {
        if (grid[i] == 0) {
            grid[i] = player;

            int thisScore = -minmax(grid, player * -1);

            if (thisScore > score) {
                score = thisScore;
                move = i;
            }
            grid[i] = 0;
        }
    }

    if (move == -1)
        return 0;

    return score;
}

void computerMove(int grid[9]) {
    int score = -2;
    int move = -1;

    for (int i = 0; i < 9; i++) { 
        if (grid[i] == 0) {
            grid[i] = 1;
            
            int currentScore = -minmax(grid, -1);

            grid[i] = 0;

            if (currentScore > score) {
                score = currentScore;
                move = i;
            }
        }
    }

    printf("Computer chose %d. \n", move + 1);

    grid[move] = 1;
    printf("\n");
}

void userMove(int grid[9]) {
    printf("\n");
    int move = 0;

    while (1) {
        printf("Enter a move (from 1 to 9) \n");
        scanf("%d", &move);
        move--;

        if (move < 9 && move >= 0 && grid[move] == 0) {
            break;
        }

        printf("\nInvalid cell number cell or already occupied! Try again. \n");
    }

    grid[move] = -1;

    displayGrid(grid);
    printf("\n");
}

int main() {
    int grid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int player = 0;

    printf("Do you want to play 1st or 2nd? \n");
    scanf("%d", &player);

    while (player != 1 && player != 2) {
        printf("Invalid input! Enter 1 or 2. \n");
        scanf("%d", &player);
    }

    for (int i = 0; i < 9 && win(grid) == 0; i++) {
        if ((player + i) % 2 == 0) {
            computerMove(grid);
        }
        else {
            displayGrid(grid);
            userMove(grid);
        }
    }

    switch (win(grid)) {
        case 0:
            displayGrid(grid);
            printf("\nYou both drew!\n");
            break;

        case 1:
            displayGrid(grid);
            printf("\nComputer won!\n");
            break;

        case -1:
            displayGrid(grid);
            printf("\nUser won! \n");
            break;
    }
}