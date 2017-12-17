extern int squareUnderAttack(int colPos, int rowPos, int player, int board[][8]);

extern int kingUnderAttack(int player, int board[][8]);

extern void completemove(int pos[], int b[][8]);

int king(int pos[], int player, int board[][8]) {
    /*[col][row][col][row]*/
    /*pos[] contains current positions and new positions [0][1]=current [2][3] = new*/
    int tempBoard[8][8];
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }
    
    if (pos[3] == pos[1] + 1 && pos[2] == pos[0]) {
        /*move south*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] && pos[2] == pos[0] - 1) {
        /*move west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0]) {
        /*move north*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] && pos[2] == pos[0] + 1) {
        /*move east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] + 1 && pos[2] == pos[0] + 1) {
        /*move south east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] + 1 && pos[2] == pos[0] - 1) {
        /*move south west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0] - 1) {
        /*move north west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0] + 1) {
        /*move north east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else {
        /*illegal move*/
        return 0;
    }

}
