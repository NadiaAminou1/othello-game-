
/* Created by Nadia Aminou
 * Student Number - 20312373
 * The othello/reversi game */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8 /* Board Size */

char Board[SIZE][SIZE]; //the board

struct playersStr { // players structures
    char player1[50];
    char player2[50];
    int player1Score;
    int player2Score;
    int turn;
}players;

int gameEnd = 0, row1, col1;
int diagonal = 0;


void welcome(void);
void Display(void);
void movePlayer(char place[], char color);
int validateMove(char place[], char color);
void score(void);
int isGameEnd(void);
int isMovePass(char color);
int checkValidMove(int row, int col, char color);
void gameOver(void);
void writeInFile(void);

void Display(void)
{
    score();
    printf("\nScore: %s (Black) %d:%d %s (White)\n", players.player1, players.player1Score, players.player2Score, players.player2);
    for (int i = 0; i<SIZE; i++)
    {
        printf("    ---+---+---+---+---+---+---+--- \n ");
        printf("%d | %c | %c | %c | %c | %c | %c | %c | %c |\n", i + 1, Board[i][0], Board[i][1], Board[i][2], Board[i][3], Board[i][4], Board[i][5], Board[i][6], Board[i][7]);
    }

    printf("    ---+---+---+---+---+---+---+--- \n ");
    printf("    a   b   c   d   e   f   g   h \n");
}

void alignBoard(void) /* function to Blank all the board squares */
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Board[i][j] = ' ';
        }
    }

    Board[3][4] = 'B';
    Board[3][3] = 'W';
    Board[4][3] = 'B';
    Board[4][4] = 'W';

    players.player1Score = 2;
    players.player2Score = 2;
}

void movePlayer(char place[], char color) {
    int row = atoi(&place[1]) - 1;

    int col = place[0] - 'a';

    if (diagonal == 1) {
        // insert code here for diagonal
        if (row > row1) {
            if (col > col1) {
                int d = 0;
                while ((col - d) >= col1 && (row - d) >= row1) {
                    Board[row - d][col - d] = color;
                    d++;
                }
            }
            else if (col < col1) {
                int d = 0;
                while ((col + d) <= col1 && (row - d) >= row1) {
                    Board[row - d][col + d] = color;
                    d++;
                }
            }
        }
        else if (row < row1) {
            if (col > col1) {
                int d = 0;
                while ((col - d) >= col1 && (row + d) <= row1) {
                    Board[row + d][col - d] = color;
                    d++;
                }
            }
            else if (col < col1) {
                int d = 0;
                while ((col + d) <= col1 && (row + d) <= row1) {
                    Board[row + d][col + d] = color;
                    d++;
                }
            }
        }
    }
    else if (row == row1) {
        if (col < col1) {
            for (int i = col; i <= col1; i++)
                Board[row][i] = color;
        }
        else if (col > col1) {
            for (int i = col1; i <= col; i++)
                Board[row][i] = color;
        }
    }
    else if (col == col1) {
        if (row < row1) {
            for (int i = row; i <= row1; i++)
                Board[i][col] = color;
        }
        else if (row > row1) {
            for (int i = row1; i <= row; i++)
                Board[i][col] = color;
        }
    }

    if (isGameEnd() == 1)
        gameEnd = 1;
}

void welcome(void) {
    printf("\t\t***  Welcome to Othello!  ***\n");

    printf("Enter name of Player 1 (Black): ");
    scanf("%s", players.player1);

    printf("Enter name of Player 2 (White): ");
    scanf("%s", players.player2);

    players.player1Score = 0;
    players.player2Score = 0;
    players.turn = 1;
}

int validateMove(char place[], char color) {
    diagonal = 0;
    int valid = 0;
    int i, j;
    char oppColor;

    int row = atoi(&place[1]) - 1;
    int col = place[0] - 'a';

    if (Board[row][col] != ' ')
        return 0;

    if(Board[row-1][col-1] == ' ' && Board[row - 1][col] == ' ' &&  Board[row - 1][col + 1] == ' ' && Board[row][col - 1] == ' ' && Board[row][col + 1] == ' ' && Board[row + 1][col - 1] == ' ' && Board[row + 1][col] == ' ' && Board[row + 1][col + 1] == ' ')
        return 0;

    if (color == 'W') oppColor = 'B'; else oppColor = 'W';


    if (Board[row][col - 1] == oppColor) {
        i = col - 1;
        while (Board[row][i] == oppColor) {i--;}
        row1 = row;
        col1 = i;
        if (color == Board[row1][col1]) {
            valid = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row][col + 1] == oppColor) {
        i = col + 1;
        while (Board[row][i] == oppColor) { i++; }
        row1 = row;
        col1 = i;
        if (color == Board[row1][col1]) {
            valid = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row + 1][col] == oppColor) {
        i = row + 1;
        while (Board[i][col] == oppColor) { i++; }
        row1 = i;
        col1 = col;
        if (color == Board[row1][col1]) {
            valid = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row - 1][col] == oppColor ) {
        i = row - 1;
        while (Board[i][col] == oppColor) { i--; }
        row1 = i;
        col1 = col;
        if (color == Board[row1][col1]) {
            valid = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row - 1][col + 1] == oppColor) {
        i = row - 1;
        j = col + 1;
        while (Board[i][j] == oppColor) { i--; j++; }
        row1 = i;
        col1 = j;
        if (color == Board[row1][col1]) {
            valid = 1;
            diagonal = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row - 1][col - 1] == oppColor ) {
        i = row - 1;
        j = col - 1;
        while (Board[i][j] == oppColor) { i--; j--; }
        row1 = i;
        col1 = j;
        if (color == Board[row1][col1]) {
            valid = 1;
            diagonal = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row + 1][col + 1] == oppColor) {
        i = row + 1;
        j = col + 1;
        while (Board[i][j] == oppColor) { i++; j++; }
        row1 = i;
        col1 = j;
        if (color == Board[row1][col1]) {
            valid = 1;
            diagonal = 1;
            movePlayer(place, color);
        }
    }

    if (Board[row + 1][col - 1] == oppColor) {
        i = row + 1;
        j = col - 1;
        while (Board[i][j] == oppColor) { i++; j--; }
        row1 = i;
        col1 = j;
        if (color == Board[row1][col1]) {
            valid = 1;
            diagonal = 1;
            movePlayer(place, color);
        }
    }

    if (valid == 0) return 0;

    return 1;
}

void score(void) {
    players.player1Score = 0;
    players.player2Score = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Board[i][j] == 'B') players.player1Score++;
            else if(Board[i][j] == 'W') players.player2Score++;
        }
    }
}

int isGameEnd(void) {
    // Game is end, if
    // no valid move for Black
    // no valid move for White
    // or Board is filled.


    int found = 0;
    // check if White is present
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Board[i][j] == 'W') {
                found = 1;
                break;
            }
        }
    }

    if (found == 0)
        return 1;


    found = 0;
    // check if White is present
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Board[i][j] == 'B') {
                found = 1;
                break;
            }
        }
    }

    if (found == 0)
        return 1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Board[i][j] == ' ') {
                return 0;  // game is not end,
            }
        }
    }


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (checkValidMove(i, j, Board[i][j]) == 1) {
                return 0;  // game is end, 0 means game is not end
            }
        }
    }

    return 1;	//	 game is end
}

int isMovePass(char color) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (Board[i][j] == color) {
                if (checkValidMove(i, j, color) == 1) // 1 means there is a valid move
                    return 0;  // So pass is not allowed
            }
        }
    }
    return 1; // pass is allowed.
}

int checkValidMove(int row, int col, char color) {

    char oppColor = ' ';
    if (color == 'W') oppColor = 'B'; else oppColor = 'W';
    int i, j;


    // same row, left side of index
    if (col - 1 > 0) {
        if (Board[row][col - 1] != ' ' && Board[row][col - 1] != color) {
            j = col - 1;
            while (Board[row][j] == oppColor) j--;
            j++;
            if (Board[row][j] == ' ' && j != col - 1) return 1; // valid move is present
        }
    }


    // same row, right side of index
    if (col + 1 < 7) {
        if (Board[row][col + 1] != ' ' && Board[row][col + 1] != color) {
            j = col + 1;
            while (Board[row][j] == oppColor) j++;
            j--;
            if (Board[row][j] == ' ' && j != col + 1) return 1; // valid move is present

        }
    }


    // same col, up side of index
    if (row - 1 > 0) {
        if (Board[row - 1][col] != ' ' && Board[row - 1][col] != color) {
            i = row - 1;
            while (Board[i][col] == oppColor) i--;
            i++;
            if (Board[i][col] == ' ' && i != row - 1) return 1; // valid move is present
        }
    }

    // same col, down side of index
    if (row + 1 < 7) {
        if (Board[row + 1][col] != ' ' && Board[row + 1][col] != color) {
            i = row + 1;
            while (Board[i][col] == oppColor) i++;
            i--;
            if (Board[i][col] == ' ' && i != row + 1) return 1; // valid move is present
        }
    }

    // upper left diagonal
    if (row - 1 > 0 && col - 1 > 0) {
        if (Board[row - 1][col - 1] != ' ' && Board[row - 1][col - 1] != color) {
            i = row - 1;
            j = col - 1;
            while (Board[i][j] == oppColor) { i--; j--; }
            i++; j++;
            if (Board[i][j] == ' ' && i != row - 1  && j != col - 1) return 1; // valid move is present
        }
    }


    // upper right diagonal
    if (row - 1 > 0 && col + 1 < 7) {
        if (Board[row - 1][col + 1] != ' ' && Board[row - 1][col + 1] != color) {
            i = row - 1;
            j = col + 1;
            while (Board[i][j] == oppColor) { i--; j++; }
            i++; j--;
            if (Board[i][j] == ' ' && i != row - 1 && j != col + 1) return 1; // valid move is present
        }
    }



    // lower left diagonal
    if (row + 1 < 7 && col - 1 > 0) {
        if (Board[row + 1][col - 1] != ' ' && Board[row + 1][col - 1] != color) {
            i = row + 1;
            j = col - 1;
            while (Board[i][j] == oppColor) { i++; j--; }
            i--; j++;
            if (Board[i][j] == ' ' && i != row + 1 && j != col - 1) return 1; // valid move is present
        }
    }


    // lower right diagonal
    if (row + 1 < 7 && col + 1 < 7) {
        if (Board[row + 1][col + 1] != ' ' && Board[row + 1][col + 1] != color) {
            i = row + 1;
            j = col + 1;
            while (Board[i][j] == oppColor) { i++; j++; }
            i--; j--;
            if (Board[i][j] == ' ' && i != row + 1 && j != col + 1) return 1; // valid move is present
        }
    }


    return 0;	// no valide move is present.
}

void gameOver(void) {
    if (players.player1Score > players.player2Score)
        printf("Player %s (Black) WON the game!!!\nThe score is: %d\n\n", players.player1, players.player1Score);
    else
        printf("Player %s (White) WON the game!!!\nThe score is: %d\n\n", players.player2, players.player2Score);
}

void writeInFile(void) {
    FILE *fp;
    fp = fopen("othello-results.txt", "a");

    fprintf(fp, "\nScore: %s (Black) %d:%d %s (White)\n", players.player1, players.player1Score, players.player2Score, players.player2);
    for (int i = 0; i<SIZE; i++)
    {
        fprintf(fp, "    ---+---+---+---+---+---+---+--- \n ");
        fprintf(fp, "%d | %c | %c | %c | %c | %c | %c | %c | %c |\n", i + 1, Board[i][0], Board[i][1], Board[i][2], Board[i][3], Board[i][4], Board[i][5], Board[i][6], Board[i][7]);
    }

    fprintf(fp, "    ---+---+---+---+---+---+---+--- \n ");
    fprintf(fp, "    a   b   c   d   e   f   g   h \n");


    if (players.player1Score > players.player2Score)
        fprintf(fp, "Player %s (Black) WON the game!!!\nThe score is: %d", players.player1, players.player1Score);
    else
        fprintf(fp, "Player %s (White) WON the game!!!\nThe score is: %d", players.player2, players.player2Score);


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp, "\nDate and Time: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(fp, "=======================================================\n ");
    fclose(fp);
}


int main(void) {
    welcome();
    alignBoard();
    Display();
    char move[3];
    char color = ' ';
    int valid = 0;


    while (!gameEnd) {
        if (players.turn % 2 == 1) {
            printf("Please enter a move for black: ");
            color = 'B';
        }
        else {
            printf("Please enter a move for white: ");
            color = 'W';
        }
        scanf("%s", move);

        if (move[0] == 'p') {
            if (isMovePass(color) == 0) {
                valid = 0;
                printf("Pass is not allowed, Valid move is available in the Board.\n");
            }
            else {
                valid = 1;
            }
        }
        else {
            valid = validateMove(move, color);
        }
        while (valid != 1) {
            if (players.turn % 2 == 1) {
                printf("Please enter a valid move for black: ");
            }
            else {
                printf("Please enter a valid move for white: ");
            }
            scanf("%s", move);
            if (move[0] == 'p') {
                if (isMovePass(color) == 0) {
                    valid = 0;
                    printf("Pass is not allowed, Valid move is available in the Board.\n");
                }
                else {
                    valid = 1;
                }
            }
            else {
                valid = validateMove(move, color);
            }
        }

        Display();
        players.turn++;
    }

    gameOver();
    writeInFile();


    system("pause");
    return 0;
}
