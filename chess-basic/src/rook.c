extern int checkPosition(int row, int col, int b[][8]);

extern int kingUnderAttack(int player, int board[][8]);

extern void completemove(int pos[], int b[][8]);

int rook(int pos[], int player, int board[][8]) {
    /*[col][row][col][row]*/
    /*pos[] contains current positions and new positions [0][1]=current [2][3] = new*/
    int tempBoard[8][8];
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    if (pos[3] > pos[1] && pos[2] == pos[0]) {
        /*move south*/
        for (i = pos[1] + 1; i < pos[3]; ++i) {
            if (checkPosition(i, pos[0], board)) {
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
    } else if (pos[3] == pos[1] && pos[2] < pos[0]) {
        /*move west*/
        for (i = pos[0] - 1; i > pos[2]; --i) {
            if (checkPosition(pos[1], i, board)) {
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
    } else if (pos[3] < pos[1] && pos[2] == pos[0]) {
        /*move north*/
        for (i = pos[1] - 1; i > pos[3]; --i) {
            if (checkPosition(i, pos[0], board)) {
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
    } else if (pos[3] == pos[1] && pos[2] > pos[0]) {
        /*move east*/
        for (i = pos[0] + 1; i < pos[2]; ++i) {
            if (checkPosition(pos[1], i, board)) {
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
