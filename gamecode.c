#include <stdio.h>
#include <ctype.h>

char board[3][3];

void initBoard(void) {
    char c = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = c++;
}

void printBoard(void) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("     |     |     \n");
        printf("  %c  |  %c  |  %c  \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2)
            printf("_____|_____|_____\n");
        else
            printf("     |     |     \n");
    }
    printf("\n");
}

/* Returns 'X' or 'O' if someone has won, 'D' for draw, ' ' if game continues */
char checkWinner(void) {
    // Rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    // Check for draw (no digits left)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (isdigit((unsigned char)board[i][j]))
                return ' ';
    return 'D';
}

int makeMove(char player) {
    int choice;
    printf("Player %c, enter a position (1-9): ", player);

    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');   // clear invalid input
        printf("Invalid input! Please enter a number.\n");
        return 0;
    }
    if (choice < 1 || choice > 9) {
        printf("Number must be between 1 and 9.\n");
        return 0;
    }

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (!isdigit((unsigned char)board[row][col])) {
        printf("That spot is already taken. Try again.\n");
        return 0;
    }

    board[row][col] = player;
    return 1;
}

int main(void) {
    char again;

    do {
        char player = 'X';
        char result = ' ';

        initBoard();
        printf("=== TIC TAC TOE ===\n");
        printf("Player 1: X    Player 2: O\n");

        while (result == ' ') {
            printBoard();

            if (!makeMove(player))
                continue;               // invalid move, same player retries

            result = checkWinner();
            if (result == ' ')
                player = (player == 'X') ? 'O' : 'X';
        }

        printBoard();
        if (result == 'D')
            printf("It's a draw!\n");
        else
            printf("Player %c wins! Congratulations!\n", result);

        printf("\nPlay again? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y' || again == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}