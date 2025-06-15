#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char board[3][3];
char player = 'X';
char computer = 'O';
int gameMode = 0; // 1 = PvP, 2 = PvE

void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i != 2) printf("\n---|---|---\n");
    }
    printf("\n\n");
}

int isWinner(char s) {
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == s && board[i][1] == s && board[i][2] == s) ||
            (board[0][i] == s && board[1][i] == s && board[2][i] == s))
            return 1;
    if ((board[0][0] == s && board[1][1] == s && board[2][2] == s) ||
        (board[0][2] == s && board[1][1] == s && board[2][0] == s))
        return 1;
    return 0;
}

int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void playerMove(char symbol) {
    int x, y;
    while (1) {
        printf("Гравець '%c', введіть координати (1-3 рядок і стовпець): ", symbol);
        scanf("%d %d", &x, &y);
        x--; y--;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
            board[x][y] = symbol;
            break;
        }
        else {
            printf("Невірно. Спробуйте ще раз.\n");
        }
    }
}

// Мінімакс для розумного комп'ютера
int minimax(int depth, int isMaximizing) {
    if (isWinner(computer)) return 10 - depth;
    if (isWinner(player)) return depth - 10;
    if (isDraw()) return 0;

    int bestScore = isMaximizing ? -1000 : 1000;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = isMaximizing ? computer : player;
                int score = minimax(depth + 1, !isMaximizing);
                board[i][j] = ' ';
                if (isMaximizing)
                    bestScore = score > bestScore ? score : bestScore;
                else
                    bestScore = score < bestScore ? score : bestScore;
            }

    return bestScore;
}

void computerMove() {
    int bestScore = -1000;
    int moveX = -1, moveY = -1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                int score = minimax(0, 0);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    moveX = i;
                    moveY = j;
                }
            }

    board[moveX][moveY] = computer;
    printf("Комп'ютер зробив хід (%d, %d)\n", moveX + 1, moveY + 1);
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");
    printf("=== Гра Хрестики-Нолики ===\n");
    printf("1 - Гравець проти Гравця\n");
    printf("2 - Гравець проти Комп'ютера\n");
    printf("Виберіть режим: ");
    scanf("%d", &gameMode);

    initializeBoard();
    printBoard();

    while (1) {
        playerMove(player);
        printBoard();
        if (isWinner(player)) {
            printf("Гравець '%c' переміг!\n", player);
            break;
        }
        if (isDraw()) {
            printf("Нічия!\n");
            break;
        }

        if (gameMode == 1) {
            playerMove(computer);
        }
        else {
            computerMove();
        }

        printBoard();
        if (isWinner(computer)) {
            printf("Гравець '%c' переміг!\n", computer);
            break;
        }
        if (isDraw()) {
            printf("Нічия!\n");
            break;
        }
    }

    return 0;
}
