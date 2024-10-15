
#include <stdio.h>

void drawBoard(char board[3][3])
{
	printf("-------------------\n");
	for (int i = 0; i < 3; i++) {
		printf("| ");
		for (int j = 0; j < 3; j++) {
			printf(" %c  | ",board[i][j] );
		}
		printf("\n-------------------\n");
	}
}

//ai

int checkWin(char board[3][3], char player)
{
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == player && board[i][1] == player
			&& board[i][2] == player)
			return 1;
		if (board[0][i] == player && board[1][i] == player
			&& board[2][i] == player)
			return 1;
	}
	if (board[0][0] == player && board[1][1] == player
		&& board[2][2] == player)
		return 1;
	if (board[0][2] == player && board[1][1] == player
		&& board[2][0] == player)
		return 1;
	return 0;
}

int main()
{
    char board[3][3] = { { ' ', ' ', ' ' },
						{ ' ', ' ', ' ' },
						{ ' ', ' ', ' ' } };
	char player = 'X';
	int row, col;
	int turn;

    printf("Welcome to Tic-Tac-Toe!\n");

    for (turn = 0; turn < 9; turn++) {
		
		drawBoard(board);
 
		while (1) {
			 printf("Player %c enter row (0-2) and column (0-2): ",player);
			scanf("%d %d",&row,&col);

			if (board[row][col] != ' ' || row < 0 || row > 2|| col < 0 || col > 2) {
				printf("Invalid move. Try again.\n");
			}
			else {
				break; 
            }
		}

		board[row][col] = player;
		
		if (checkWin(board, player)) {
			drawBoard(board);
			printf("Player %c wins!\n",player);
			break;
		}

		if (player == 'X') {
            player = 'O';   
        }

        else {
            player = 'X';
        }
	}
    
    if (turn == 9 && !checkWin(board, 'X')&& !checkWin(board, 'O')) {
		printf("It's a draw!\n");
	}

	return 0;
}