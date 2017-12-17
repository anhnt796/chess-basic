#include <stdlib.h>

extern int checkPosition(int row, int col, int b[][8]);

extern int kingUnderAttack(int player, int board[][8]);

extern void completemove(int pos[], int b[][8]);

int bishop(int pos[], int player, int board[][8]) {
    /*[col][row][col][row]*/
    /*pos[] contains current positions and new positions [0][1]=current [2][3] = new*/
    int tempBoard[8][8];
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }
    
    if (pos[3] > pos[1] && pos[2] > pos[0]) {
        /*move south east*/
        /*if move is not horizontal, return 0*/
        /*change in x-axis must equal change in y-axis*/
        if (!(abs(pos[0] - pos[2]) == abs(pos[1] - pos[3]))) {
            return 0;
        }
        i = pos[1];
        for (j = pos[0] + 1; j < pos[2]; j++) {
            i++;
            if (checkPosition(i, j, board)) {
                /*if piece at intermediate position move is illegal*/
                return 0;
            }
        }
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        /*reached new position*/
        return 1;
    } else if (pos[3] > pos[1] && pos[2] < pos[0]) {
        /*move south west*/
        /*if move is not horizontal, return 0*/
        /*change in x-axis must equal change in y-axis*/
        if (!(abs(pos[0] - pos[2]) == abs(pos[1] - pos[3]))) {
            return 0;
        }
        i = pos[1];
        for (j = pos[0] - 1; j > pos[2]; j--) {
            i++;
            if (checkPosition(i, j, board)) {
                /*if piece at intermediate position move is illegal*/
                return 0;
            }
        }
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        /*reached new position*/
        return 1;
    } else if (pos[3] < pos[1] && pos[2] < pos[0]) {
        /*move north west*/
        /*if move is not horizontal, return 0*/
        /*change in x-axis must equal change in y-axis*/
        if (!(abs(pos[0] - pos[2]) == abs(pos[1] - pos[3]))) {
            return 0;
        }
        i = pos[1];
        for (j = pos[0] - 1; j > pos[2]; j--) {
            --i;
            if (checkPosition(i, j, board)) {
                /*if piece at intermediate position move is illegal*/
                return 0;
            }
        }
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        /*reached new position*/
        return 1;
    } else if (pos[3] < pos[1] && pos[2] > pos[0]) {
        /*move north east*/
        /*if move is not horizontal, return 0*/
        /*change in x-axis must equal change in y-axis*/
        if (!(abs(pos[0] - pos[2]) == abs(pos[1] - pos[3]))) {
            return 0;
        }
        i = pos[1];
        for (j = pos[0] + 1; j < pos[2]; j++) {
            --i;
            if (checkPosition(i, j, board)) {
                /*if piece at intermediate position move is illegal*/
                return 0;
            }
        }
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        /*reached new position*/
        return 1;
    } else {
        /*illegal move*/
        return 0;
    }
}
