extern int kingUnderAttack(int player, int board[][8]);

extern void completemove(int pos[], int b[][8]);

int knight(int pos[], int player, int board[][8]) {
    /* pos is the input player is the color of player*/
    int tempBoard[8][8];
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    if (pos[3] == pos[1] + 1 && pos[2] == pos[0] + 2) {
        /*move 1 south 2 east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] + 2 && pos[2] == pos[0] + 1) {
        /*move 2 south 1 east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] + 2 && pos[2] == pos[0] - 1) {
        /*move 2 south 1 west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] + 1 && pos[2] == pos[0] - 2) {
        /*move 1 south 2 west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0] - 2) {
        /*move 1 north 2 west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 2 && pos[2] == pos[0] - 1) {
        /*move 2 north 1 west*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 2 && pos[2] == pos[0] + 1) {
        /*move 2 north 1 east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else if (pos[3] == pos[1] - 1 && pos[2] == pos[0] + 2) {
        /*move 1 north 2 east*/
        completemove(pos, tempBoard);
        if (kingUnderAttack(player, tempBoard)) {
            return 0;
        }
        return 1;
    } else {
        /*invalid move*/
        return 0;
    }
}
